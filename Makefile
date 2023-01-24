.SILENT:
all: compile separate main clean

main:
	-cd rks-16 && g++ -std=c++17 main.cpp && ./a.out && cd ..

compile:
	set -e && cd rks && python main.py

clean:
	rm -f rks-16/a.out

separate:
	echo -e "\n===========================================\n"