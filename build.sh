BUILD=build

assemble() {
	mkdir -p $BUILD
	mkdir -p $BUILD/rks
	
	g++ rks/main.cpp rks/lexer.cpp -o $BUILD/rks/main
	./$BUILD/rks/main
}

assemble
