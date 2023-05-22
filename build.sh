GXX=g++
GXX_FLAGS=-std=c++17 # Won't compile without this for some reason

BUILD=build

ASSEMBLER=$(find ./assembler -type f -name "*.cpp")
EMULATOR=$(find ./emulator -type f -name "*.cpp")
UTILS=$(find ./common -type f -name "*.cpp")

assemble() {
	mkdir -p $BUILD/assembler

	$GXX $GXX_FLAGS $UTILS $ASSEMBLER -o $BUILD/assembler/main
	./$BUILD/assembler/main
}

emulate() {
	mkdir -p $BUILD/emulator

	$GXX $GXX_FLAGS $UTILS $EMULATOR -o $BUILD/emulator/main
	./$BUILD/emulator/main
}

clean() {
	rm -rf $BUILD/*
}

set -e
mkdir -p $BUILD

clean
assemble
emulate
