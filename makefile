main: main.o Speaker.o DE1SoCfpga.o
	g++ main.o Speaker.o DE1SoCfpga.o -o main

main.o: main.cpp Speaker.h
	g++ -g -Wall -c main.cpp
	
Speaker.o: Speaker.cpp Speaker.h
	g++ -g -Wall -c Speaker.cpp
		
DE1SoCfpga.o: DE1SoCfpga.cpp DE1SoCfpga.h
	g++ -g -Wall -c DE1SoCfpga.cpp
		
clean:
	rm main.o Speaker.o DE1SoCfpga.o main
