cmake_minimum_required(VERSION 3.10)

project(OCR_Project)

# Підключаємо OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Підключаємо Tesseract
find_package(Tesseract REQUIRED)
include_directories(${Tesseract_INCLUDE_DIRS})

add_executable(ocr main.cpp)

target_link_libraries(ocr ${OpenCV_LIBS} ${Tesseract_LIBRARIES})
