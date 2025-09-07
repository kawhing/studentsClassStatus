# yolo_inference.py
import json
import sys
import os
import cv2
import torch
from ultralytics import YOLO

def run_inference(model_path, image_path):
    print('pytorch 版本:', torch.__version__)
    try:
    # 执行推理
        model = YOLO(model_path)
        results = model(image_path, conf=0.25, verbose=False)
        result = results[0]
    # 固定保存到项目根目录的 result.jpg
        output_image_path = "result.jpg"
        annotated_image = result.plot()
        cv2.imwrite(output_image_path, annotated_image)
    # 收集检测信息
        detections = []
        for box in result.boxes:
            detection = {
                'class_id': int(box.cls),
                'class_name': result.names[int(box.cls)],
                'confidence': float(box.conf),
                'bbox': box.xyxy[0].tolist()
            }
            detections.append(detection)
    # 返回JSON数据（不包含图片路径，因为固定）
        result_data = {
            'success': True,
            'detections': detections,
            'message': '推理完成，图片已保存到 result.jpg'
        }
        return result_data
    except Exception as e:
        return {
            'success': False,
            'message': f'推理错误: {str(e)}'
        }
if __name__ == "__main__":
    if len(sys.argv) != 3:
        result = {'success': False, 'message': '参数错误'}
        print(json.dumps(result))
        sys.exit(1)
    model_path = sys.argv[1]
    image_path = sys.argv[2]
    result = run_inference(model_path, image_path)
    print(json.dumps(result))
