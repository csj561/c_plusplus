.PHONY: clean #不论依赖是否比目标新，规则都要执行
CPPFLAGS += -I./ -I/home/xyd/github/ice/cpp/include
LDFLAGS += -L/home/xyd/github/ice/cpp/lib/i386-linux-gnu/ -lIce -lpthread -lIceUtil
obj = server.o client.o testice.o \
      priSrv.o
target = server.elf client.elf priSrv priClnt
all: $(target)

%.o:%.cpp
	g++ -c $^ -o $@  $(CPPFLAGS)

server.elf: server.o testice.o
	g++ -o $@ $^ $(LDFLAGS)
client.elf: client.o testice.o
	g++ -o $@ $^ $(LDFLAGS)
priSrv: priSrv.o printer.o
	g++ -o $@ $^ $(LDFLAGS)
priClnt: priClnt.o printer.o
	g++ -o $@ $^ $(LDFLAGS)
clean:
	-rm *.o *.elf $(target) >/dev/null 2>&1
