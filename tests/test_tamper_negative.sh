#!/usr/bin/env bash
set -euo pipefail

# Đảm bảo đường dẫn tới file thực thi đúng (thường là ./des ở thư mục gốc)
DES_EXE="./des"

PLAINTEXT="0101010101110001110001110001110001110001110001110001110001110001"
KEY="0001001100110100010101110111100110011011101111001101111111110001"

# 1. Mã hóa bản tin gốc
CIPHERTEXT=$(echo -e "1\n$PLAINTEXT\n$KEY" | $DES_EXE)

# 2. Làm giả dữ liệu (Tamper): Đảo bit đầu tiên của bản mã
FIRST_BIT=${CIPHERTEXT:0:1}
if [ "$FIRST_BIT" == "0" ]; then
    FLIPPED="1"
else
    FLIPPED="0"
fi
TAMPERED="${FLIPPED}${CIPHERTEXT:1}"

# 3. Giải mã bản mã đã bị thay đổi
DECRYPTED=$(echo -e "2\n$TAMPERED\n$KEY" | $DES_EXE)

echo "--- Kết quả Test Tamper ---"
echo "Original plaintext:  $PLAINTEXT"
echo "Decrypted tampered:  $DECRYPTED"

# 4. Kiểm tra: Giải mã dữ liệu bị lỗi KHÔNG ĐƯỢC ra bản gốc
if [ "$DECRYPTED" == "$PLAINTEXT" ]; then
    echo "❌ Tamper test FAILED (Dữ liệu bị thay đổi nhưng giải mã vẫn ra đúng - Sai logic DES)"
    exit 1
fi

echo "✅ Tamper test PASSED"
exit 0
