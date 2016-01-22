#target = libfool.so

CC = gcc
CXX = g++
.PHONY : all clean
all : scan_image.elf


%.o:%.c
	$(CC) -g -I${HOME}/include -fvisibility=hidden  $^ -c -o $@

%.o:%.cpp
	$(CXX) -g -I${HOME}/include -fvisibility=hidden -fvisibility-inlines-hidden $^ -c -o $@
%.cpp:%.h

%.elf:%.o
	$(CC) $^ -I./ -L${HOME}/lib -lzbar -lpng -lfool -lstdc++  -o $@

clean:
	-rm -f *.o *.so *.elf *.a
