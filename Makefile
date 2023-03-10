.SILENT:
all: clean compile separate run

compile:
	set -e && cd rks && python main.py

run:
	-cd rks-16 && g++ -std=c++17 -o "./build/main" main.cpp && ./build/main && cd ..

clean:
	find rks-16/build/ -mindepth 1 -delete

separate:
	echo -e "\n===========================================\n"