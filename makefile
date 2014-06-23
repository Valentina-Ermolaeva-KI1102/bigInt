all: main.cpp bigInt.cpp operotors.cpp
	g++ main.cpp bigInt.cpp operotors.cpp -o bigint

windows: main.cpp bigInt.cpp operotors.cpp
	g++ main.cpp bigInt.cpp operotors.cpp -o bigint.exe
