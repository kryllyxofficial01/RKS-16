BUILD=build

ASM_SOURCES=$(find . -type f -name "*.cpp")

assemble() {
	mkdir -p $BUILD
	mkdir -p $BUILD/rks

	g++ $ASM_SOURCES -o $BUILD/rks/main
	./$BUILD/rks/main
}

set -e
assemble
