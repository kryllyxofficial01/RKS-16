BUILD=build

ASSEMBLER=$(find ./assembler -type f -name "*.cpp")

assemble() {
	mkdir -p $BUILD
	mkdir -p $BUILD/rks

	g++ $ASSEMBLER -o $BUILD/rks/main
	./$BUILD/rks/main
}

set -e
assemble
