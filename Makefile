.SILENT:
all: compile separate main clean

compile:
	set -e && cd rks && python main.py

main:
	-cd rks-16 && g++ -std=c++17 -o "main" main.cpp && ./main && cd ..

clean:
	rm -f rks-16/main

separate:
	echo -e "\n===========================================\n"