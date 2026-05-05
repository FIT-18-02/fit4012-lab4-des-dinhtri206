#!/usr/bin/env bash
set -euo pipefail

# Đường dẫn tới file thực thi DES
DES_EXE="./des"

# 1. Chuẩn bị dữ liệu: Plaintext dài 75 bit (không chia hết cho 64)
PLAINTEXT="010101010111000111000111000111000111000111000111000111000111000111100001111"
KEY="0001001100110100010101110111100110011011101111001101111111110001"

# 2. Thực hiện mã hóa (Mode 1)
# Kết quả CIPHERTEXT sẽ có độ dài là bội số của 64 (trong trường hợp này là 128 bit)
CIPHERTEXT=$(echo -e "1\n$PLAINTEXT\n$KEY" | $DES_EXE)

# 3. Thực hiện giải mã (Mode 2)
DECRYPTED=$(echo -e "2\n$CIPHERTEXT\n$KEY" | $DES_EXE)

# 4. Giả lập Zero Padding thủ công để so sánh kết quả
PADDED="$PLAINTEXT"
while [ $((${#PADDED} % 64)) -ne 0 ]; do
    PADDED="${PADDED}0"
done

echo "--- Kết quả Test Multi-block Padding ---"
echo "Plaintext gốc:    $PLAINTEXT"
echo "Plaintext padded: $PADDED"
echo "Dữ liệu giải mã:  $DECRYPTED"

# 5. Kiểm tra tính đúng đắn
if [ "$DECRYPTED" != "$PADDED" ]; then
    echo "❌ Multi-block padding FAILED (Dữ liệu giải mã không khớp với bản gốc đã pad)"
    exit 1
fi

echo "✅ Multi-block padding PASSED"
exit 0
