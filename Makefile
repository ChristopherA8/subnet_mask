all:
	@clang++ src/main.cpp -o dist/main
	@clear
	@./dist/main