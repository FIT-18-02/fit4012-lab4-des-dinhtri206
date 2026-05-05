  [![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/B72A5Yyp)
# FIT4012 - Lab 4: DES / TripleDES Starter Repository

Repo này là **starter repo** cho Lab 4 của FIT4012.  

## 1. Cấu trúc repo

```text
.
├── .github/
│   ├── scripts/
│   │   └── check_submission.sh
│   └── workflows/
│       └── ci.yml
├── logs/
│   ├── .gitkeep
│   └── README.md
├── scripts/
│   └── run_sample.sh
├── tests/
│   ├── test_des_sample.sh
│   ├── test_encrypt_decrypt_roundtrip.sh
│   ├── test_multiblock_padding.sh
│   ├── test_tamper_negative.sh
│   └── test_wrong_key_negative.sh
├── .gitignore
├── CMakeLists.txt
├── Makefile
├── README.md
├── des.cpp
└── report-1page.md
```

## 2. Cách chạy chương trình (How to run)

### Cách 1: Dùng Makefile

```bash
make
./des
```

### Cách 2: Biên dịch trực tiếp

```bash
g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
./des
```

### Cách 3: Dùng CMake

```bash
cmake -S . -B build
cmake --build build
./build/des
```

### Chạy test local

```bash
make test
```

Hoặc chạy script mẫu:

```bash
bash scripts/run_sample.sh
```

## 3. Input / Đầu vào

Chương trình nhận dữ liệu đầu vào trực tiếp từ bàn phím (stdin) theo thứ tự:
- **Mode:** Chọn 1 (DES Encrypt), 2 (DES Decrypt), 3 (3DES Encrypt), hoặc 4 (3DES Decrypt).
- **Dữ liệu (Plaintext/Ciphertext):** Nhập dưới dạng chuỗi nhị phân (0 và 1). Chương trình hỗ trợ nhập chuỗi có độ dài bất kỳ (nhiều block).
- **Khóa (Key):** Nhập chuỗi nhị phân 64-bit cho DES. Đối với TripleDES, nhập lần lượt 3 khóa K1, K2, K3 (mỗi khóa 64-bit).

## 4. Output / Đầu ra

Kết quả được hiển thị trên màn hình (stdout):
- **Ciphertext/Plaintext cuối cùng:** Hiển thị dưới dạng chuỗi nhị phân liên tục.
- **Chi tiết các bước:** Chương trình in ra các Round Keys (khóa vòng) cho mỗi block để phục vụ việc kiểm tra và theo dõi quá trình mã hóa/giải mã.
- **TripleDES:** Thực hiện đúng quy trình E-D-E (Encrypt-Decrypt-Encrypt).

## 5. Padding đang dùng

Chương trình sử dụng cơ chế **Zero Padding**:
- **Cơ chế:** Nếu độ dài plaintext không phải là bội số của 64, các bit `0` sẽ được thêm vào cuối block cuối cùng cho đến khi đủ 64 bit.
- **Xử lý đa block:** Plaintext dài được chia thành các cụm 64 bit độc lập để xử lý lần lượt.
- **Hạn chế:** Zero padding có thể gây nhầm lẫn nếu dữ liệu gốc vốn dĩ kết thúc bằng các bit 0 (không phân biệt được đâu là dữ liệu thật, đâu là padding).
- **Lưu ý:** Đây là cách tiếp cận cơ bản trong học thuật. Trong thực tế, các chuẩn như PKCS#7 thường được ưu tiên sử dụng để đảm bảo tính toàn vẹn dữ liệu khi giải mã.

## 6. Tests bắt buộc

Repo này đã tạo sẵn **5 tên file test mẫu** để sinh viên điền nội dung:

- `tests/test_des_sample.sh`
- `tests/test_encrypt_decrypt_roundtrip.sh`
- `tests/test_multiblock_padding.sh`
- `tests/test_tamper_negative.sh`
- `tests/test_wrong_key_negative.sh`

Sinh viên phải tự hoàn thiện test và bổ sung minh chứng chạy.

## 7. Logs / Minh chứng

Thư mục `logs/` dùng để nộp minh chứng, ví dụ:
- ảnh chụp màn hình khi chạy chương trình
- output của test
- log thử đúng / sai key / tamper
- log cho mã hóa nhiều block

## 8. Ethics & Safe use

- Chỉ chạy và kiểm thử trên dữ liệu học tập hoặc dữ liệu giả lập.
- Không dùng repo này để tấn công hay can thiệp hệ thống thật.
- Không trình bày đây là công cụ bảo mật sẵn sàng cho môi trường sản xuất.
- Nếu tham khảo mã, tài liệu, công cụ hoặc AI, phải ghi nguồn rõ ràng.
- Khi cộng tác nhóm, cần trung thực học thuật và mô tả đúng phần việc của mình.
- Việc kiểm thử chỉ phục vụ học DES / TripleDES ở mức nhập môn.

## 9. Checklist nộp bài

Trước khi nộp, cần có:
- `des.cpp`
- `README.md` hoàn chỉnh
- `report-1page.md` hoàn chỉnh
- `tests/` với ít nhất 5 test
- có negative test cho `tamper` và `wrong key`
- `logs/` có ít nhất 1 file minh chứng thật
- không còn dòng placeholder dạng đánh dấu chưa hoàn thiện

## 10. Lưu ý về CI

CI sẽ **không chỉ kiểm tra file có tồn tại** mà còn kiểm tra:
- các mục bắt buộc trong README
- các mục bắt buộc trong report
- sự hiện diện của negative tests
- có minh chứng trong `logs/`
- repo **không còn placeholder dạng đánh dấu chưa hoàn thiện**

Vì vậy repo starter này sẽ **chưa pass CI** cho tới khi sinh viên hoàn thiện nội dung.


## 11. Submission contract để auto-check Q2 và Q4

Để GitHub Actions kiểm tra được **Q2** và **Q4**, repo này dùng **một contract nhập/xuất thống nhất**.
Sinh viên cần sửa `des.cpp` để chương trình nhận dữ liệu từ **stdin** theo đúng thứ tự sau:

```text
Chọn mode:
1 = DES encrypt
2 = DES decrypt
3 = TripleDES encrypt
4 = TripleDES decrypt
```

### Mode 1: DES encrypt 
Nhập lần lượt:
1. `1`
2. plaintext nhị phân
3. key 64-bit

Yêu cầu:
- nếu plaintext dài hơn 64 bit: chia block 64 bit và mã hóa tuần tự
- nếu block cuối thiếu bit: zero padding
- in ra **ciphertext cuối cùng** dưới dạng chuỗi nhị phân

### Mode 2: DES decrypt
Nhập lần lượt:
1. `2`
2. ciphertext nhị phân
3. key 64-bit
Yêu cầu:
- giải mã DES theo round keys đảo ngược
- in ra plaintext cuối cùng

### Mode 3: TripleDES encrypt 
Nhập lần lượt:
1. `3`
2. plaintext 64-bit
3. `K1`
4. `K2`
5. `K3`

Yêu cầu:
- thực hiện đúng chuỗi **E(K3, D(K2, E(K1, P)))**
- in ra ciphertext cuối cùng

### Mode 4: TripleDES decrypt 
Nhập lần lượt:
1. `4`
2. ciphertext 64-bit
3. `K1`
4. `K2`
5. `K3`

Yêu cầu:
- thực hiện giải mã TripleDES ngược lại
- in ra plaintext cuối cùng

### Lưu ý về output
- Có thể in prompt tiếng Việt hoặc tiếng Anh.
- Có thể in thêm round keys hay thông báo trung gian.
- Nhưng **kết quả cuối cùng phải xuất hiện dưới dạng một chuỗi nhị phân dài hợp lệ** để CI tách và đối chiếu.

## 14. CI hiện kiểm tra được gì

Ngoài checklist nộp bài, CI hiện còn kiểm tra tự động:
- chương trình thực sự nhận plaintext/key từ bàn phím và mã hóa multi-block với zero padding đúng.
- chương trình thực sự mã hóa và giải mã TripleDES đúng theo vector kiểm thử.

Nói cách khác, nếu sinh viên chỉ sửa README/tests cho đủ hình thức mà **không làm Q2 hoặc Q4**, CI sẽ vẫn fail.
