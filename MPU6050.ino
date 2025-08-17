#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az; // Accelerometer values
int16_t gx, gy, gz; // Gyroscope values

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.backlight();

  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    lcd.print("MPU6050 Error");
    while (1);
  }

  lcd.clear();
  lcd.print("MPU6050 Test");
  delay(2000);
  lcd.clear();
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  lcd.setCursor(0, 0);
  lcd.print("Acc: ");
  lcd.print(ax);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("Gyro: ");
  lcd.print(gx);
  lcd.print("   ");

  delay(500); // Adjust the delay as needed
}
