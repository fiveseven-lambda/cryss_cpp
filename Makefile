CXX=clang++
CXXFLAGS=-std=c++2b \
	-DDEBUG \
	-D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STC_FORMAT_MACROS -D__STDC_LIMIT_MACROS \
	-Weverything -Wno-shadow-field-in-constructor -Wno-padded -Wno-c++98-compat -Wno-c++98-compat-pedantic
LDFLAGS=-lLLVM
SOURCES=$(wildcard source/*.cpp)
OBJS=$(SOURCES:source/%.cpp=obj/%.o)

cryss:$(OBJS)
	$(CXX) $(LDFLAGS) -ocryss $(OBJS)
obj/%.o: source/%.cpp
	[ -d obj ] || mkdir obj
	$(CXX) $(CXXFLAGS) -c -o$@ $<
all:source/*
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -ocryss $(SOURCES)

clean:
	[ ! -d obj ] || rm -r obj
	[ ! -f cryss ] || rm cryss