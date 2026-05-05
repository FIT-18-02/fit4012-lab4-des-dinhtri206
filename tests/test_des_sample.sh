#!/usr/bin/env bash
set -euo pipefail

# 1. Đường dẫn tới file thực thi DES (giả định nằm ở thư mục gốc sau khi build)
DES_EXE="./des"

# 2. Input mẫu 64-bit chuẩn (Mode 1 - Encrypt)
# Dòng 1: Mode (1)
# Dòng 2: Data (64-bit)
# Dòng 3: Key (64-bit)
INPUT="1
0000000100100011010001010110011110001001101010111100110111101111
0001001100110100010101110111100110011011101111001101111111110001"

# 3. Output mong đợi (DES chuẩn tương ứng với input trên)
EXPECTED="1000010111101000000100110101010000001111000010101011010000000101"

# 4. Chạy chương trình và lấy kết quả
# Sử dụng echo -e để truyền nhiều dòng vào stdin
OUTPUT=$(echo -e "$INPUT" | $DES_EXE)

echo "--- DES Sample Test ---"
echo "Output nhận được: $OUTPUT"
echo "Output kỳ vọng:  $EXPECTED"

# 5. Kiểm tra kết quả
if [ "$OUTPUT" != "$EXPECTED" ]; then
    echo "❌ Test mẫu THẤT BẠI (Kết quả không khớp DES chuẩn)"
    exit 1
fi

echo "✅ Test mẫu ĐẠT"
exit 0
