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
![image](https://github.com/user-attachments/assets/b5765551-bf43-4603-85ea-0bec4e41a892)

2. Hiển thị thông tin tổng quát của các packet:
![image](https://github.com/user-attachments/assets/573ed18e-f892-4daa-9c37-c365f24c5c5e)

3. Lấy thông tin chi tiết dựa trên ID:
![image](https://github.com/user-attachments/assets/d3ecea02-adea-4f20-b406-ffe83831c2bd)

![image](https://github.com/user-attachments/assets/6bffe59b-7739-4c3a-90f9-1c3f0e6ecaa6)


