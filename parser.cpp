#include "parser.h"
#include <iostream>


void parser::parse(string filename){
    my_scanner.openSource(filename);

    StringTable t;
    token Start; 
    Start.tokId = NT_PROGRAM;
    token x;
    string next;
    
    my_token_stack.push(Start);

    x = my_scanner.getNextToken(t);
    while (!my_scanner.getErr() && !my_scanner.getEOF() && !my_token_stack.empty()){
	//Dr. Joiner requested specific output for debugging/grading
	//first print a blank line
	std::cout << std::endl;
    
	//next print the current input token from the scanner
	std::cout << "PARSE: inTok=" << x.tokId << " ";
	printToken(x);
	std::cout << std::endl;

	//then print the stack
	my_token_stack.print();
	

	x = my_scanner.getNextToken(t);		

    }


    

}
