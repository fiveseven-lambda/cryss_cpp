CXX=clang++
CXXFLAGS=-std=c++20 -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
LDFLAGS=-lLLVM-12
SOURCES=$(wildcard source/*.cpp)
OBJS=$(SOURCES:source/%.cpp=obj/%.o)

cryss:$(OBJS)
	$(CXX) $(LDFLAGS) -ocryss $(OBJS)
obj/%.o: source/%.cpp
	$(CXX) $(CXXFLAGS) -c -o$@ $<
all:source/*
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -Weverything -Wno-shadow-field-in-constructor -Wno-padded -Wno-c++98-compat -ocryss $(SOURCES)
