FLAGS = -std=c++17 -o "./build/main" `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lm

.SILENT:
all: clean compile separate run

compile:
	set -e && cd rks && python main.py

run:
	-cd rks-16 && g++ $(FLAGS) main.cpp && ./build/main && cd ..

clean:
	find rks-16/build/ -mindepth 1 -delete

separate:
	echo -e "\n===========================================\n"
