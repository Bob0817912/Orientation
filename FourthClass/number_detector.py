import cv2
import numpy as np
import pytesseract



def extract_numbers_from_image(image_path):
    # 读取图像
    image = cv2.imread(image_path)

    # 转换为灰度图
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # 高斯模糊以降低噪声
    blurred_image = cv2.GaussianBlur(gray_image, (5, 5), 0)

    # 自适应阈值二值化图像
    _, binary_image = cv2.threshold(blurred_image, 128, 255, cv2.THRESH_BINARY_INV)

    # 寻找轮廓
    contours, _ = cv2.findContours(binary_image, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    recognized_numbers = []

    # 遍历轮廓
    for contour in contours:
        # 获取轮廓的边界框坐标
        x, y, w, h = cv2.boundingRect(contour)

        # 截取包含数字的区域（ROI）
        roi = binary_image[y:y + h, x:x + w]

        # 使用 Tesseract 对 ROI 进行 OCR 识别
        number_text = pytesseract.image_to_string(roi, config='--psm 6 --oem 3 -c tessedit_char_whitelist=0123456789')

        # 从识别的文本中提取数字
        numbers = [int(s) for s in number_text.split() if s.isdigit()]

        recognized_numbers.extend(numbers)

        # 在图像上绘制边界框
        cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 2)

    # 显示带有边界框的图像
    
    cv2.imshow('number-detector', image)
    cv2.waitKey(0)
    

    return recognized_numbers

if __name__ == "__main__":
    # 替换为实际图像文件的路径
    image_path=cv2.imread('image.jpg')
    # 读取图像
    image_origin = cv2.imread(image_path)
    cv2.imshow('origin', image_origin)
    # 从图像中提取数字
    recognized_numbers = extract_numbers_from_image(image_path)

    if recognized_numbers:
        print("Recognized Numbers:", recognized_numbers)
    else:
        print("No numbers found in the image.")