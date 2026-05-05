# FIT4012 - Lab 4: DES / TripleDES Starter Repository

## Thông tin sinh viên
- **Họ và tên:** Nguyễn Đình Trí
- **Mã sinh viên:** 1871020580
- **Trường:** Đại học Đại Nam

---

## 1. Cách chạy chương trình (How to run)

Biên dịch bằng g++ với chuẩn C++17:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
./des
```

## 2. Input / Đầu vào

Chương trình đọc dữ liệu từ `stdin` theo thứ tự:

1. Chọn mode: 1 = DES Encrypt, 2 = DES Decrypt, 3 = TripleDES Encrypt, 4 = TripleDES Decrypt
2. Dữ liệu nhị phân: Plaintext (khi mã hóa) hoặc Ciphertext (khi giải mã), hỗ trợ nhiều block và tự động chia thành block 64-bit
3. Khóa (Key): DES sử dụng 1 khóa 64-bit, TripleDES nhập lần lượt 3 khóa 64-bit

## 3. Output / Đầu ra

Kết quả là một chuỗi nhị phân duy nhất, không chứa ký tự thừa (khoảng trắng, xuống dòng hoặc log debug), đảm bảo tương thích với hệ thống kiểm thử tự động (CI).

## 4. Padding

Sử dụng cơ chế Zero Padding:

* Nếu dữ liệu đầu vào không đủ 64 bit, chương trình tự động thêm các bit 0 vào cuối block
* Phương pháp này đơn giản, phù hợp cho mục đích học tập và minh họa nguyên lý mã hóa khối

## 5. Ethics & Safe Use

* Chương trình được xây dựng cho mục đích học tập và nghiên cứu DES/TripleDES
* Không sử dụng trong môi trường thực tế hoặc cho mục đích tấn công
* DES và TripleDES không còn đảm bảo an toàn cho các hệ thống bảo mật hiện đại
