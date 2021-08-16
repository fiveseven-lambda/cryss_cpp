cryss:src/*
	clang++ -std=c++20 -I/usr/include -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -L/usr/lib -lLLVM-12 -ocryss src/*.cpp
weverything:src/*
	clang++ -std=c++20 -Weverything -Wno-shadow-field-in-constructor -Wno-padded -Wno-c++98-compat -I/usr/include -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -L/usr/lib -lLLVM-12 -ocryss src/*.cpp
