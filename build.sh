BUILD=build

ASSEMBLER=$(find ./assembler -type f -name "*.cpp")
EMULATOR=$(find ./emulator -type f -name "*.cpp")

assemble() {
	mkdir -p $BUILD/assembler

	g++ $ASSEMBLER -o $BUILD/assembler/main
	./$BUILD/assembler/main
}

emulate() {
	mkdir -p $BUILD/emulator

	g++ $EMULATOR -o $BUILD/emulator/main
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
