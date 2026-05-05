# Trình biên dịch và các cờ biên dịch
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
TARGET := des
SRC := des.cpp

# Các mục tiêu ảo (không tạo ra tệp)
.PHONY: all clean run test

# Mục tiêu mặc định khi gõ 'make'
all: $(TARGET)

# Quy tắc biên dịch (Sửa lỗi thiếu dấu đóng ngoặc ở $(TARGET))
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Quy tắc chạy chương trình
run: $(TARGET)
	./$(TARGET)

# Quy tắc chạy toàn bộ các bài test trong thư mục tests/
test: $(TARGET)
	@chmod +x tests/*.sh
	@for file in tests/*.sh; do \
		echo "Running $$file..."; \
		bash $$file; \
	done

# Quy tắc dọn dẹp các tệp tạm và tệp thực thi
clean:
	rm -f $(TARGET)
	rm -rf build logs
