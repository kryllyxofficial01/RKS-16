BUILD=build

ASSEMBLER=$(find ./assembler -type f -name "*.cpp")

assemble() {
	mkdir -p $BUILD/assembler

	g++ $ASSEMBLER -o $BUILD/assembler/main
	./$BUILD/assembler/main
}

clean() {
	rm -rf $BUILD/*
}

set -e
mkdir -p $BUILD

clean
assemble
