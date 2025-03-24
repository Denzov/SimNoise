build:
	g++ *.cpp src/*.cpp -o main.exe

run_raw:
	main.exe

run: build
	main.exe