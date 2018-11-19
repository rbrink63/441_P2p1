#include "parser.h"
#include <iostream>


void parser::parse(string filename){
    my_scanner.openSource(filename);

    StringTable t;
    token x;
    string next;
    
    x = my_scanner.getNextToken(t);
    my_token_stack.push(x);

    while (!my_scanner.getErr() && !my_scanner.getEOF() && !my_token_stack.empty()){
	//Dr. Joiner requested specific output for debugging/grading
	//first print a blank line
	std::cout << std::endl;
    
	//next print the current input token from the scanner
	if (x.sref == nullptr) next = my_scanner.getUpperLex();
	else next = x.sref->data;

	std::cout << "PARSE: inTok=" << x.tokId << " " << next << std::endl;	

	//then print the stack
	my_token_stack.print();
	

	x = my_scanner.getNextToken(t);		

    }


    

}
