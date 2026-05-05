# FIT4012 - Lab 4: DES / TripleDES Starter Repository

## Thông tin sinh viên
- **Họ và tên:** Nguyễn Đình Trí
- **Mã sinh viên:** 1871020580
- **Trường:** Đại học Đại Nam

---

## 1. Cách chạy chương trình (How to run)
Biên dịch bằng g++ (yêu cầu chuẩn C++17):
```bash
g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
./des
```

## 2. Input / Đầu vào
Chương trình nhận dữ liệu từ `stdin` theo đúng thứ tự sau:
1. **Chọn mode:** (1 = DES encrypt, 2 = DES decrypt, 3 = TripleDES encrypt, 4 = TripleDES decrypt).
2. **Dữ liệu nhị phân:** Bản rõ (plaintext) hoặc bản mã (ciphertext) hỗ trợ nhiều block.
3. **Khóa (key):** Chuỗi nhị phân 64-bit (hoặc nhập lần lượt 3 khóa cho TripleDES).

## 3. Output / Đầu ra
Kết quả là một chuỗi nhị phân duy nhất, phù hợp với yêu cầu kiểm thử tự động của hệ thống CI. Chương trình không in thêm các ký tự thừa để đảm bảo tính chính xác khi đối chiếu.

## 4. Padding đang dùng
Sử dụng cơ chế **Zero Padding**:
- Nếu dữ liệu đầu vào không đủ 64 bit, chương trình tự động thêm các bit `0` vào cuối khối để đủ kích thước block.
- Đây là cơ chế nhập môn phục vụ mục đích học tập, giúp nắm bắt nguyên lý mã hóa khối cơ bản.

## 5. Ethics & Safe use (An toàn)
- Sản phẩm được thực hiện hoàn toàn cho mục đích học tập và nghiên cứu thuật toán DES/TripleDES.
- Không sử dụng mã nguồn này cho mục đích tấn công hệ thống thật hoặc sử dụng trong các môi trường sản xuất thực tế.
