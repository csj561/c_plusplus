#target = libfool.so
target = libfool.a

obj = fool.o
CC = g++
INC = fool.h
.PHONY : all clean
all : $(target) install test 

$(target) : fool.o
#$(CC)  -shared -o $@ $^ 
	ar cr  $@ $^
%.o:%.cpp
	$(CC) -g -I./ $^ -c -o $@
%.cpp:%.h

test:test.cpp
	touch $^;mk $^

install:$(target)
	install -t ~/lib $(target) 
	install -t ~/include $(INC) 

clean:
	-rm *.o *.so test
