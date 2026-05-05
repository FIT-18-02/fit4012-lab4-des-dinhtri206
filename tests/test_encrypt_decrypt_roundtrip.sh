#!/usr/bin/env bash
set -euo pipefail

# Đường dẫn tới file thực thi DES
DES_EXE="./des"

# 1. Chuẩn bị dữ liệu: Plaintext không chia hết cho 64 bit để test cả padding
PLAINTEXT="0101010101110001110001110001110001110001110001110001110001110001111"
KEY="0001001100110100010101110111100110011011101111001101111111110001"

# 2. Mã hóa (Mode 1)
CIPHERTEXT=$(echo -e "1\n$PLAINTEXT\n$KEY" | $DES_EXE)

# 3. Giải mã (Mode 2)
DECRYPTED=$(echo -e "2\n$CIPHERTEXT\n$KEY" | $DES_EXE)

# 4. Xử lý logic so sánh: 
# Vì hàm pad() trong des.cpp của bạn thêm số '0' vào cuối, 
# nên kết quả giải mã sẽ là bản gốc kèm theo các số 0 đã pad.
PADDED_EXPECTED="$PLAINTEXT"
while [ $((${#PADDED_EXPECTED} % 64)) -ne 0 ]; do
    PADDED_EXPECTED="${PADDED_EXPECTED}0"
done

echo "--- Kết quả Test Round-trip ---"
echo "Dữ liệu gốc:    $PLAINTEXT"
echo "Dữ liệu kỳ vọng: $PADDED_EXPECTED"
echo "Dữ liệu giải mã: $DECRYPTED"

# 5. Kiểm tra tính toàn vẹn
if [ "$DECRYPTED" != "$PADDED_EXPECTED" ]; then
    echo "❌ Round-trip FAILED (Dữ liệu không khớp)"
    exit 1
fi

echo "✅ Round-trip PASSED"
exit 0
