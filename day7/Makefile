CC = clang++
CCFLAGS = -g -O0 -Wall -pedantic -Wlong-long -pthread `sdl2-config --cflags` #-fsanitize=address --fno-omit-frame-pointer
CCOPTS+= -D_LINUX -DDEBUGGING_ON

SRC = $(wildcard *.cpp)
HDR = $(wildcard *.h)
OBJ = $(SRC: .cpp=.o)

Day7: $(OBJ)
	$(CC) $(CCFLAGS) $(CCOPTS) $^ -o $@

clean:
	rm -f Day7