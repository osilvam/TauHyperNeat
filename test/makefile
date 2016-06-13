CC = g++ -O3 -std=c++11
LDFLAGS = -lpthread -L. -ltauhyperneat -lneat

all:
	$(CC) test.cpp -o TEST $(LDFLAGS)

run:
	./TEST

clean:
	rm -f TEST
	rm -f -R ./functions_files
	rm -f *.txt