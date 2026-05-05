#!/usr/bin/env bash
set -euo pipefail

# 1. Khởi tạo và biên dịch (nếu cần trong môi trường test)
# Nếu hệ thống đã biên dịch sẵn file des ở thư mục gốc, hãy điều chỉnh đường dẫn ./des
DES_EXE="./des"

# 2. Dữ liệu thử nghiệm (Hệ nhị phân 64-bit)
PLAINTEXT="0101010101110001110001110001110001110001110001110001110001110001"
KEY_CORRECT="0001001100110100010101110111100110011011101111001101111111110001"
KEY_WRONG="1111000011110000111100001111000011110000111100001111000011110000"

# 3. Thực hiện Encrypt với key đúng (Mode 1)
# Sử dụng echo để đưa dữ liệu vào stdin: mode, data, key
CIPHERTEXT=$(echo -e "1\n$PLAINTEXT\n$KEY_CORRECT" | $DES_EXE)

# 4. Thực hiện Decrypt với key sai (Mode 2)
DECRYPTED=$(echo -e "2\n$CIPHERTEXT\n$KEY_WRONG" | $DES_EXE)

echo "--- Kết quả Test Khóa Sai ---"
echo "Plaintext ban đầu: $PLAINTEXT"
echo "Bản giải mã (khóa sai): $DECRYPTED"

# 5. Kiểm tra: Kết quả giải mã bằng khóa sai PHẢI khác với Plaintext ban đầu
if [ "$DECRYPTED" == "$PLAINTEXT" ]; then
    echo "❌ LỖI: Giải mã bằng khóa sai nhưng vẫn ra plaintext đúng!"
    exit 1
fi

echo "✅ ĐẠT: Khóa sai không thể khôi phục dữ liệu ban đầu."
exit 0
