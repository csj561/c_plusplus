srcFile=$(shell ls *.cpp)
srcNoSuffix=$(basename $(srcFile))
obj=$(addsuffix .o,$(srcNoSuffix))
target=$(srcNoSuffix)
CXX=g++
$(target):$(obj)
	$(CXX) -o $@ $^

clean:
	-rm *.o $(target)