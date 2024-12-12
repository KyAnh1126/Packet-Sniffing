# Packet-Sniffing

Chương trình bao gồm các chức năng chính là:
1. Hiển thị thông tin từng cổng mạng 
2. Hiển thị thông tin tổng quát các packet đang có ở thiết bị
3. Hiển thị thông tin chi tiết của packet dựa trên ID

Cấu trúc dự án:
- thư mục build chứa các file được CMake tạo ra cũng như file ouput của chương trình
- thư mục include chứa các file header
- thư mục src chứa các file triển khai của các file header cũng như file chính là main.cpp
- CMakeLists.txt của từng thư mục nhỏ cũng như top-level chứa các file cấu hình để tạo file output

Cách chạy chương trình:
1. cd build
2. cmake ..
3. make

Kết quả chương trình:

1. Hiển thị thông tin của từng cổng mạng hiện có:
![6](https://github.com/user-attachments/assets/299f62f8-422c-46b5-806c-4f63909220ff)

2. Hiển thị thông tin tổng quát của các packet:
![7](https://github.com/user-attachments/assets/8bbde439-a1b9-45fc-bc37-d1099e318a82)

3. Lấy thông tin chi tiết dựa trên ID:
![8](https://github.com/user-attachments/assets/00ec0984-36eb-496b-84b5-8b44bb32282d)

![9](https://github.com/user-attachments/assets/29ee12ba-fdca-4a99-86bb-67b83074a14e)
