srcFile=$(shell ls *.cpp)
srcNoSuffix=$(basename $(srcFile))
obj=$(addsuffix .o,$(srcNoSuffix))
target=$(srcNoSuffix)
CXXFLAGS= -g
CXX=g++
$(target):$(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	-rm *.o $(target)
