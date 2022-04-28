all:
	g++ -g *.cpp -o main
	./main
clean:
	rm main