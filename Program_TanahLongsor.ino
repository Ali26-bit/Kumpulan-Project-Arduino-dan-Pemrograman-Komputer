//Blynk
#define BLYNK_TEMPLATE_ID "TMPL6XmCNxoEc"
#define BLYNK_TEMPLATE_NAME "Monitoring Longsor"
#define BLYNK_AUTH_TOKEN "6FBs9Nt1wJjIjkrf0bbfVKrkv1TrwwvR"

//Inisialisasi Library, Wifi, dan Blynk
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <Wire.h>
#include <Arduino.h>
#include <MPU6050.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp32.h>

//Pin ESP32
#define SOIL_MOISTURE_PIN 34
#define BUZZER_PIN 25
#define LED_MERAH 26
#define LED_HIJAU 27

//Soil Moisture
#define SOIL_DRY 2700
#define SOIL_WET 1100

// Koneksi Wi-Fi (ganti dengan kredensial Wi-Fi yang sesuai)
char auth[] = "6FBs9Nt1wJjIjkrf0bbfVKrkv1TrwwvR";
char ssid[] = "KONTRAKAN FISIKA";
char pass[] = "25julikitadisini";

BlynkTimer timer;

MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat LCD bisa 0x27 atau 0x3F


float last_ax = 0, last_ay = 0, last_az = 0;

// Variabel untuk kontrol tampilan bergiliran
unsigned long previousMillis = 0;
const long interval = 3000; // Ganti tampilan setiap 3 detik
int page = 0;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  Wire.begin();
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);

  lcd.init();
  lcd.backlight();


  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 Tidak Terdeteksi!");
    lcd.setCursor(0, 0);
    lcd.print("MPU6050 ERROR!");
    while (1);
  }
  Serial.println("MPU6050 Terhubung!");
  lcd.clear();
}

void loop() {
  // Membaca data sensor
  Blynk.run();
  timer.run();
  int soil_value = analogRead(SOIL_MOISTURE_PIN);
  int soil_percent = map(soil_value, SOIL_DRY, SOIL_WET, 0, 100);
  soil_percent = constrain(soil_percent, 0, 100);

  int16_t ax_raw, ay_raw, az_raw;
  mpu.getAcceleration(&ax_raw, &ay_raw, &az_raw);
  float ax = ax_raw / 16384.0;
  float ay = ay_raw / 16384.0;
  float az = az_raw / 16384.0;

  float Dax = abs(ax - last_ax);
  float Day = abs(ay - last_ay);
  float Daz = abs(az - last_az);

  last_ax = ax;
  last_ay = ay;
  last_az = az;

  bool tanah_bergerak = (Dax > 0.05 || Day > 0.05 || Daz > 0.05);

  String status = "AMAN";
  if (soil_percent < 30 && tanah_bergerak) {
    status = "AMAN";
  } else if (soil_percent >= 30 && soil_percent < 65 && tanah_bergerak) {
    status = "WASPADA";
  } else if (soil_percent >= 65 && tanah_bergerak) {
    status = "BAHAYA";
  }

  // Logika buzzer dan LED
  if (status == "AMAN") {
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_HIJAU, HIGH);
    noTone(BUZZER_PIN);
  } else if (status == "WASPADA") {
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW);
    noTone(BUZZER_PIN);
  } else {
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_HIJAU, LOW);
    tone(BUZZER_PIN, 1000);
  }

  // === TAMPILAN BERGANTIAN LCD ===
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    page++;
    if (page > 1) page = 0;
  }

  lcd.clear();
  switch (page) {
    case 0:
      lcd.setCursor(4, 0);
      lcd.print("Kelembaban:");
      lcd.setCursor(4, 4);
      lcd.print(soil_percent);
      lcd.print("%");
      delay (2000);
      lcd.clear();
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Dax:");
      lcd.print(Dax, 2);
      lcd.setCursor(8, 0);
      lcd.print("Day:");
      lcd.print(Day, 2);
      lcd.setCursor(0, 1);
      lcd.print("Daz:");
      lcd.print(Daz, 2);
      delay (2000);
      lcd.clear();
    case 2:
      lcd.setCursor(4, 0);
      lcd.print("Status:");
      lcd.setCursor(4, 4);
      lcd.print(status);
      delay (2000);
      lcd.clear();
    case 3:
      lcd.setCursor(4, 0);
      lcd.print("Waktu:");
      lcd.setCursor(4, 1);
      lcd.print(millis() / 1000);
      lcd.print(" detik");
      delay (2000);
      lcd.clear();
  }

  // Mengirim data ke Blynk
  Blynk.virtualWrite(V0, soil_percent); // Kelembaban tanah
  Blynk.virtualWrite(V1, Dax); // Delta ax
  Blynk.virtualWrite(V2, Day); // Delta ay
  Blynk.virtualWrite(V3, Daz); // Delta az
  Blynk.virtualWrite(V4, status.c_str()); // Status tanah
  Blynk.virtualWrite(V6, ax); // Akselerasi Y
  Blynk.virtualWrite(V7, ay); // Akselerasi Z
  Blynk.virtualWrite(V8, az); // Akselerasi Z
  Blynk.virtualWrite(V9, digitalRead(LED_MERAH)); // Status LED Merah (0 atau 1)
  Blynk.virtualWrite(V10, digitalRead(LED_HIJAU)); // Status LED Hijau (0 atau 1)


  // **Kirim Push Notification jika status tanah "BAHAYA"**
  // if (status == "BAHAYA") {
  //   Blynk.notify("⚠️ PERINGATAN: Risiko Tanah Longsor Terdeteksi! ⚠️");
  // }

  // Debug ke Serial Monitor
  Serial.println("=== Data Sensor ===");
  Serial.print("Kelembaban: "); Serial.print(soil_percent); Serial.println("%");
    Serial.print("Delta_aX="); Serial.print(Dax);
  Serial.print("Delta_aY="); Serial.print(Day);
  Serial.print("Delta_aZ="); Serial.println(Daz);
  Serial.print("Status Tanah: "); Serial.println(status);
  Serial.println("---------------------------");

  Blynk.run(); // Jalankan loop Blynk

  delay(100); // delay kecil untuk meringankan beban serial
}
