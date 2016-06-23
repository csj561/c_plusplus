#target = libfool.so
target = libfool.a
release = libfool.so

obj = fool.o fool_scan.o fool_qrencode.o fool_time.o
CC = gcc
CXX = g++
INC = fool.h fool_internal.hpp
CFLAGS=-Dpng_set_gray_1_2_4_to_8=png_set_expand_gray_1_2_4_to_8
.PHONY : all clean
all : $(target) $(release) test 

$(target) : $(obj)
	ar cr  $@ $^

$(release) : $(obj)
#$(CC)   -shared -o $@ $^ 
	$(CXX) -fPIC  -shared -o $@ $^ 

%.o:%.c
#$(CC) -g -I./  $^ -c -o $@
	$(CC) -g -I./ -I${HOME}/include -fPIC ${CFLAGS}  $^ -c -o $@
%.o:%.cpp
#$(CC) -g -I./  $^ -c -o $@
	$(CXX) -g -I./ -I${HOME}/include -fPIC ${CFLAGS} $^ -c -o $@
#$(CXX) -g -I./ -I${HOME}/include -fvisibility=hidden -fvisibility-inlines-hidden $^ -c -o $@
%.cpp:%.h

test:test.cpp
	$(CXX) $^ -g -I./ -L./ -L${HOME}/lib  -lfool -lzbar -lqrencode -lpng -o $@.elf

install:$(target) $(release)
	install -t ~/lib $(target) 
#strip $(release)
	install -t ~/lib $(release)
	install -t ~/include $(INC) 

clean:
	-rm -f *.o *.so *.a
