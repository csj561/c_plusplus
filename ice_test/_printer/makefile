.PHONY: clean #不论依赖是否比目标新，规则都要执行
CPPFLAGS += -I./ -I/home/xyd/github/ice/cpp/include
LDFLAGS += -L/home/xyd/github/ice/cpp/lib/i386-linux-gnu/ -lIce -lpthread -lIceUtil
obj =  \
      priSrv.o
target =  priSrv priClnt
all: $(target)

%.o:%.cpp
	g++ -c $^ -o $@  $(CPPFLAGS)

priSrv: priSrv.o printer.o
	g++ -o $@ $^ $(LDFLAGS)
priClnt: priClnt.o printer.o
	g++ -o $@ $^ $(LDFLAGS)
clean:
	-rm *.o *.elf $(target) >/dev/null 2>&1
