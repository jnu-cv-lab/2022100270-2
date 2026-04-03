#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // ====================== 这里改成你的 WSL 真实路径 ======================
    std::string img_path = "/home/linxi/VS_CODE/test.jpg"; 
    // ======================================================================

    cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "图片读取失败: " << img_path << "\n";
        return -1;
    }

    // 2. 输出图像基本信息
    int h = img.rows;
    int w = img.cols;
    int c = img.channels();
    std::cout << "图像基本信息:\n";
    std::cout << "宽度: " << w << ", 高度: " << h << ", 通道数: " << c
              << ", 数据类型: " << img.type() << "\n";

    // 3. 显示原图
    cv::imshow("原图", img);
    cv::waitKey(1);

    // 4. 转灰度
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::imshow("灰度图", gray);
    cv::waitKey(1);

    // 5. 保存灰度图
    std::string gray_path = "/home/linxi/VS_CODE/test_gray.png";
    cv::imwrite(gray_path, gray);
    std::cout << "已保存灰度图: " << gray_path << "\n";

    // 6. 像素访问与裁剪
    cv::Vec3b px = img.at<cv::Vec3b>(0, 0);
    std::cout << "原图左上角像素 BGR: (" 
              << (int)px[0] << "," << (int)px[1] << "," << (int)px[2] << ")\n";
    uchar g00 = gray.at<uchar>(0, 0);
    std::cout << "灰度图左上角像素: " << (int)g00 << "\n";

    int crop_size = std::min(100, std::min(h, w));
    cv::Mat crop = gray(cv::Rect(0, 0, crop_size, crop_size)).clone();
    std::string crop_path = "/home/linxi/VS_CODE/test_gray_crop.png";
    cv::imwrite(crop_path, crop);
    std::cout << "已保存左上角 " << crop_size << "x" << crop_size << " 区域: " << crop_path << "\n";

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}