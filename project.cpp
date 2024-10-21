#include <iostream>
#include <opencv2/opencv.hpp> // Підключаємо OpenCV
#include <tesseract/baseapi.h> // Підключаємо Tesseract
#include <leptonica/allheaders.h> // Підключаємо Leptonica для роботи з зображеннями

// Функція для розпізнавання тексту з зображення
std::string recognizeText(const cv::Mat& image) {
    // Ініціалізація Tesseract OCR
    tesseract::TessBaseAPI ocr;
    
    // Встановлюємо мову для розпізнавання (eng для англійської або ukr для української)
    if (ocr.Init(NULL, "eng")) { 
        std::cerr << "Could not initialize tesseract.\n";
        return "";
    }

    // Конвертуємо зображення OpenCV в формат, зручний для Tesseract
    ocr.SetImage(image.data, image.cols, image.rows, 3, image.step);

    // Отримуємо розпізнаний текст
    std::string outText = ocr.GetUTF8Text();
    
    // Завершуємо роботу Tesseract
    ocr.End();
    return outText;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <image_file>\n";
        return 1;
    }

    // Читаємо зображення з файлу
    std::string imageFile = argv[1];
    cv::Mat image = cv::imread(imageFile, cv::IMREAD_COLOR);

    if (image.empty()) {
        std::cerr << "Could not open or find the image.\n";
        return -1;
    }

    // Відображаємо зображення для перевірки
    cv::imshow("Input Image", image);
    cv::waitKey(0);

    // Розпізнаємо текст з зображення
    std::string text = recognizeText(image);

    // Виводимо результат
    std::cout << "Recognized text:\n" << text << std::endl;

    // Зберігаємо текст у файл
    std::ofstream outFile("recognized_text.txt");
    outFile << text;
    outFile.close();

    std::cout << "Text has been saved to recognized_text.txt" << std::endl;

    return 0;
}
