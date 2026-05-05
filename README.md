## 1. How to run / Cách chạy

### Compile / Biên dịch

```bash
g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
```

### Run / Chạy chương trình

```bash
./des
```
---

## 2. Input / Đầu vào

Chương trình nhận dữ liệu từ bàn phím (stdin) theo mode:

```
1 = DES encrypt  
2 = DES decrypt  
3 = TripleDES encrypt  
4 = TripleDES decrypt  
```

### Mode 1 (DES encrypt)

* plaintext: chuỗi nhị phân (có thể dài > 64 bit)
* key: chuỗi nhị phân 64-bit

### Mode 2 (DES decrypt)

* ciphertext: chuỗi nhị phân
* key: chuỗi nhị phân 64-bit

### Mode 3 (TripleDES encrypt)

* plaintext: 64 bit
* K1, K2, K3: key 64-bit

### Mode 4 (TripleDES decrypt)

* ciphertext: 64 bit
* K1, K2, K3

---

## 3. Output / Đầu ra

* In ra kết quả cuối cùng dưới dạng chuỗi nhị phân
* Không chứa ký tự không hợp lệ
* Có thể có thông tin trung gian nhưng kết quả cuối phải rõ ràng

---

## 4. Padding

Chương trình sử dụng **zero padding**:

* Nếu plaintext không chia hết cho 64 bit
* Block cuối sẽ được thêm các bit `0` cho đủ 64 bit

Ví dụ:

```
10101 → 101010000000000... (đủ 64 bit)
```

### Hạn chế:

* Không phân biệt được dữ liệu thật và padding
* Không phù hợp cho hệ thống bảo mật thực tế

---

## 5. Cryptography Notes

### IV / Nonce

IV (Initialization Vector) hoặc nonce phải **unique (duy nhất)** cho mỗi lần mã hóa.
Nếu tái sử dụng, attacker có thể suy ra thông tin từ ciphertext.

### Padding

Padding cần thiết trong block cipher để đảm bảo dữ liệu chia hết block.
Sai padding có thể gây lỗi hoặc bị khai thác.

### CBC / CTR / GCM

* CBC: cần IV và padding
* CTR: không cần padding
* GCM: có authentication tag đảm bảo toàn vẹn dữ liệu

---

## 6. Tests

Thư mục `tests/` bao gồm:

* DES sample test
* encrypt/decrypt round-trip
* multi-block padding
* tamper test
* wrong key test

---

## 7. Logs

Thư mục `logs/` chứa:

* output chạy chương trình
* test case minh chứng
* kết quả đúng/sai

---

## 8. Ethics & Safe Use

* Chỉ sử dụng cho mục đích học tập
* Không dùng trong hệ thống thực tế
* Không sử dụng để tấn công
* Tuân thủ đạo đức và an toàn thông tin

---

## 9. Summary

* Implement DES và TripleDES
* Hỗ trợ encrypt/decrypt
* Hỗ trợ multi-block + zero padding
* Có test và logs minh chứng đầy đủ
