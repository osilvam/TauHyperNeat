EXECUTABLE = TauHyperNeat
VPATH = ./src ./headers ./objects
CC = g++ -O3
CFLAGS = -g -Wall -fPIC -I./headers 
LDFLAGS = -lpthread -L. -lneat
OBJS = ./objects/TauHyperNeat.o ./objects/Substrate.o ./objects/SpatialNode.o ./objects/CPPNInputs.o 

all: TauHyperNeat.o Substrate.o SpatialNode.o CPPNInputs.o   	
	
TauHyperNeat.o: TauHyperNeat.cpp
	@mkdir -p objects
	@echo "Compiling TauHyperNeat.cpp to TauHyperNeat.o"
	@$(CC) $(CFLAGS) -c ./src/TauHyperNeat.cpp  -o ./objects/TauHyperNeat.o

Substrate.o: Substrate.cpp
	@mkdir -p objects
	@echo "Compiling Substrate.cpp to Substrate.o"
	@$(CC) $(CFLAGS) -c ./src/Substrate.cpp  -o ./objects/Substrate.o

SpatialNode.o: SpatialNode.cpp
	@mkdir -p objects
	@echo "Compiling SpatialNode.cpp to SpatialNode.o"
	@$(CC) $(CFLAGS) -c ./src/SpatialNode.cpp  -o ./objects/SpatialNode.o

CPPNInputs.o: CPPNInputs.cpp 
	@mkdir -p objects
	@echo "Compiling CPPNInputs.cpp to CPPNInputs.o"
	@$(CC) $(CFLAGS) -c ./src/CPPNInputs.cpp  -o ./objects/CPPNInputs.o

clean:
	@rm -f -R ./objects
	@cd test; make clean

cleandocs:
	@rm -f -R ./doc

install:
	g++ -shared -Wl,-soname,libtauhyperneat.so.1 -o libtauhyperneat.so.1.0 $(OBJS) $(LDFLAGS)
	ln -sf libtauhyperneat.so.1.0 libtauhyperneat.so
	ln -sf libtauhyperneat.so.1.0 libtauhyperneat.so.1
	mv libtauhyperneat.so.1.0 libtauhyperneat.so libtauhyperneat.so.1 /usr/lib
	mkdir -p /usr/include/TAUHYPERNEAT_headers/
	cp ./headers/* /usr/include/TAUHYPERNEAT_headers/
	cp TAUHYPERNEAT /usr/include
	chmod go+r /usr/include/TAUHYPERNEAT_headers/*
	chmod go+r /usr/include/TAUHYPERNEAT

docs:
	@mkdir -p doc
	@doxygen TAUHYPERNEAT_doxyfile 

git:
	make clean
	make cleandocs
	git add --all
	git commit -m "$(commit)"
	git push