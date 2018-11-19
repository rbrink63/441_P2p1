all: parser 

parser: parser.cpp parser.h StringTable.cpp main.cpp scanner.cpp tokStack.cpp token.cpp StringTable.h StringTableEntry.h grammar.h scanner.h tokStack.h token.h 
	g++ -g -std=c++11 parser.cpp StringTable.cpp main.cpp scanner.cpp tokStack.cpp token.cpp 

.PHONY: clean

clean:
	rm -f a.out
