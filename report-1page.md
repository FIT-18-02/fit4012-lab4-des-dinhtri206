# Báo cáo thực hành Lab 4


**1. Mục tiêu:**
* Phân tích quy trình hoạt động của thuật toán DES và TripleDES.
* Triển khai thành công cơ chế chia khối và Zero Padding cho dữ liệu thực tế.

**2. Cách làm:**
* Xây dựng chương trình dựa trên cấu trúc DES Feistel 16 vòng.
* Hoàn thiện hàm giải mã DES bằng cách đảo ngược thứ tự khóa vòng.
* Cài đặt TripleDES theo quy trình EDE: Encrypt(K3, Decrypt(K2, Encrypt(K1, P))).

**3. Kết quả:**
* Chương trình chạy đúng các chế độ mã hóa/giải mã theo yêu cầu của Submission Contract.
* Xử lý chính xác các trường hợp plaintext dài hơn 64-bit bằng cách chia block và padding.

**4. Kết luận:**
* Thuật toán DES và TripleDES đã được cài đặt đúng quy trình, đảm bảo tính toàn vẹn dữ liệu khi mã hóa và giải mã.
