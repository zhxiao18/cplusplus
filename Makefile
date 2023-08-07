srcs:=$(wildcard *.cc)
exes:=$(srcs:%.cc=%)
all:$(exes)
%:%.cc
	g++ $^ -o $@ -g

