cmake_minimum_required(VERSION 3.10)
project(fit4012_lab4_des LANGUAGES CXX)

# Cấu hình chuẩn C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Tạo file thực thi
add_executable(des des.cpp)

# Thêm các cờ biên dịch để kiểm soát chất lượng code
if(MSVC)
    target_compile_options(des PRIVATE /W4 /WX)
else()
    target_compile_options(des PRIVATE -Wall -Wextra -Wpedantic -Wsign-compare)
endif()

# (Tùy chọn) Để dễ dàng chạy các file .sh test, 
# có thể cấu hình để file 'des' luôn nằm ở thư mục build chính
set_target_properties(des PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
