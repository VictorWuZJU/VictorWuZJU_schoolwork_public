# 定义编译器
CC=g++

# 定义编译选项
CFLAGS=-std=c++11 -Wall -Wextra -g

# 定义目标文件
TARGET=test

# 默认目标
all: $(TARGET)

# 链接对象文件生成可执行文件
$(TARGET): test.o
	$(CC) $(CFLAGS) -o $(TARGET) test.o

# 编译 test.cpp 文件生成 test.o 文件
test.o: test.cpp expression_evaluator.h
	$(CC) $(CFLAGS) -c test.cpp -o test.o

# 清理生成的文件
clean:
	rm -f test.o $(TARGET)

.PHONY: clean