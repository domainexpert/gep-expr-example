CXXFLAGS=-D_GLIBCXX_USE_CXX11_ABI=0

all: example.ll
	clang++ -o GEPExample GEPExample.cpp ${CXXFLAGS} `llvm-config --cxxflags` `llvm-config --ldflags` `llvm-config --libs` -lpthread -lncurses -ldl
	./GEPExample example.ll

clean:
	rm -f *.ll *~ GEPExample

.SUFFIXES: .ll

.c.ll:
	clang -c -emit-llvm -S -g $<
