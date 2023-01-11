.SILENT:
all: compile main clean

CXX = g++
override CXXFLAGS += -g -Wno-everything -std=c++17

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.cpp' -print | sed -e 's/ /\\ /g')
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

main: $(SRCS) $(HEADERS)
	-$(CXX) $(CXXFLAGS) $(SRCS) -o "$@" && echo "" && ./main

compile:
	set -e && cd ../rks && cargo run && cd ../rks-16 && echo "\n==========================================="

clean:
	rm -f main