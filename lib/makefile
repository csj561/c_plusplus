#target = libfool.so
target = libfool.a
release = libfool.so

obj = fool.o fool_scan.o
CC = gcc
CXX = g++
INC = fool.h
.PHONY : all clean
all : $(target) $(release) test 

$(target) : $(obj)
	ar cr  $@ $^

$(release) : $(obj)
#$(CC)   -shared -o $@ $^ 
	$(CC) -fPIC  -shared -o $@ $^ 

%.o:%.c
#$(CC) -g -I./  $^ -c -o $@
	$(CC) -g -I./ -I${HOME}/include   $^ -c -o $@
%.o:%.cpp
#$(CC) -g -I./  $^ -c -o $@
	$(CXX) -g -I./ -I${HOME}/include  $^ -c -o $@
#$(CXX) -g -I./ -I${HOME}/include -fvisibility=hidden -fvisibility-inlines-hidden $^ -c -o $@
%.cpp:%.h

test:test.cpp
	$(CXX) $^ -I./ -L./ -L${HOME}/lib  -lfool -lzbar -lpng -o $@.elf

install:$(target) $(release)
	install -t ~/lib $(target) 
#strip $(release)
	install -t ~/lib $(release)
	install -t ~/include $(INC) 

clean:
	-rm -f *.o *.so test.elf *.a
