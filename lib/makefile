#target = libfool.so
target = libfool.a
release = libfool.so

obj = fool.o
CC = g++
INC = fool.h
.PHONY : all clean
all : $(target) $(release) test 

$(target) : fool.o
	ar cr  $@ $^

$(release) : fool.o
	$(CC) -fPIC  -shared -o $@ $^ 

%.o:%.cpp
	$(CC) -g -I./ -fvisibility=hidden -fvisibility-inlines-hidden $^ -c -o $@
%.cpp:%.h

test:test.cpp
	$(CC) $^ -I./ -L./ -Wl,-Bstatic -lfool  -Wl,-Bdynamic -lm -lc -o $@.elf

install:$(target) $(release)
	install -t ~/lib $(target) 
	strip $(release)
	install -t ~/lib $(release)
	install -t ~/include $(INC) 

clean:
	-rm *.o *.so test.elf *.a
