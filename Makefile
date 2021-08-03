cryss:src/*
	g++ -std=c++20 -ocryss -Isrc src/*.cpp
clang:
	clang++ -std=c++20 -Weverything -Wno-c++98-compat -Wno-shadow-field-in-constructor -Wno-padded src/*.cpp -ocryss
