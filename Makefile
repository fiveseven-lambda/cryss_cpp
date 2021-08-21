CXX=clang++
CXXFLAGS=-std=c++20 -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
LDFLAGS=-lLLVM-12
OBJS:=$(shell ls src/*.cpp)

cryss:$(OBJS:src/%.cpp=obj/%.o)
	$(CXX) $(LDFLAGS) -ocryss obj/*.o
obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o$@ $<
weverything:src/*
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -Weverything -Wno-shadow-field-in-constructor -Wno-padded -Wno-c++98-compat -ocryss src/*.cpp
