# 设置编译器
CXX = g++
# 设置 LaTeX 编译器
LATEX = pdflatex

# 默认目标
all: main report.pdf

# 编译 C++ 程序
main: main.cpp
	$(CXX) -o main main.cpp

# 编译 LaTeX 文档
report.pdf: report.tex
	$(LATEX) report.tex
	$(LATEX) report.tex # 可能需要多次编译以解决交叉引用

# 清理生成的文件
clean:
	rm -f main report.pdf report.aux report.log

.PHONY: all clean