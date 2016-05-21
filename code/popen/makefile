srcFile=$(shell ls *.cpp)
srcNoSuffix=$(basename $(srcFile))
obj=$(addsuffix .o,$(srcNoSuffix))
target=$(srcNoSuffix)
CXXFLAGS+= -pg
LDFLAGS+= -pg
CXX=g++
$(target):$(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	-rm *.o $(target)
