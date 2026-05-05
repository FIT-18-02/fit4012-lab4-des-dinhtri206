#!/usr/bin/env bash
set -euo pipefail

# Biên dịch chương trình
g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des_test

# Dữ liệu mẫu (Mode 1: Encrypt)
# Input format: mode data key
PLAINTEXT="0123456789ABCDEF" # Giả sử data của bạn dạng hex hoặc bit tùy code
KEY="133457799BBCDFF1"
EXPECTED_PART="85E813540F0AB405" # Thay thế bằng kết quả đúng của bạn

# Chạy chương trình và lấy kết quả
OUTPUT=$(echo -e "1\n$PLAINTEXT\n$KEY" | ./des_test)

echo "Dữ liệu gốc: $PLAINTEXT"
echo "Kết quả thực tế: $OUTPUT"

# Kiểm tra kết quả (so sánh chuỗi)
if [[ "$OUTPUT" != *"$EXPECTED_PART"* ]]; then
  echo "[FAIL] Kết quả mã hóa không khớp với mong đợi"
  exit 1
fi

echo "[PASS] Chương trình DES tạo ra bản mã chính xác."
rm -f des_test
