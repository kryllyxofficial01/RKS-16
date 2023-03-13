FLAGS = -std=c++17 -o "./build/main" `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall

.SILENT:
all: clean compile separate run

compile:
	set -e && cd rks && python main.py

run:
	-cd rks-16 && g++ $(FLAGS) main.cpp && ./build/main

clean:
	if [ ! -d "rks-16/build" ]; then mkdir rks-16/build; fi
	find rks-16/build/ -mindepth 1 -delete

separate:
	echo -e "\n===========================================\n"
