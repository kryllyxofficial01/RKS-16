.SILENT:
all: compile main clean

main:
	-cd rks-16 && g++ -std=c++17 main.cpp && ./a.out && cd ..

compile:
	set -e && cd rks && python main.py && echo -e "\n==========================================="

clean:
	rm -f rks-16/a.out