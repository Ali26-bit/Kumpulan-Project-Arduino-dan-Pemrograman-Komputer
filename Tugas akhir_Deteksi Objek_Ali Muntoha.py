from imageai.Detection import ObjectDetection
import os

execution_path = os.getwcd()

detector = ObjectDetection()
detector.setMode1TypeAsRetinaNet()
detector.setMode1Path( os.path.join(execution_path ,"resnet50_coco_best_v2.1.0.h5"))
detector.loadMode()
detections = detector.detectObjectsFromImage(input_image=os.path.join(execution_path , "gambar.JPEG"), output_image_path=os.path.join(execution_path , "gambarbaru.JPEG"))

for eachObject in detections:
    print(eachObject["name"] , " : " , eachObject["percentage_probability"])
    print("----------------------------------")