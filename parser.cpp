#include "parser.h"
#include <iostream>


void parser::parse(string filename){
    my_scanner.openSource(filename);

    StringTable t;
    token Start; 
    Start.tokId = NT_PROGRAM;
    token x, c;
    string next;
    
    my_token_stack.push(Start);

    c = my_scanner.getNextToken(t);
    while (!parser_err && !my_scanner.getEOF() && !my_token_stack.empty()){
	//Dr. Joiner requested specific output for debugging/grading
	//first print a blank line
	std::cout << std::endl;
    
	//next print the current input token from the scanner
	std::cout << "PARSE: inTok=" << c.tokId << " ";
	printToken(c);
	std::cout << std::endl;

	//then print the stack
	my_token_stack.print();
	

	//PDA algorithm
	x = my_token_stack.pop();

	if (x.tokId <= 70){
	    //x is a terminal
	    if (x.tokId == c.tokId){
		//consume c
		c = my_scanner.getNextToken(t);
	    }
	    else{
		//ERROR
		parser_err = true;
		std::cout << "Parse Error: input Token found, but Top Token expected" << std::endl;
		std::cout << "Top Token = " << getTokenString(x) << "\tInput Token = " << getTokenString(c) << std::endl;
	    }
	}

	else{
	    //x is a Non Terminal
	    int prod_index = chooseProd(x,c);

	    if (!foundLHS){
		//ERROR		     
		std::cout << "Parse Error: no productions for non-terminal" << std::endl;
		std::cout << "Top Token = " << getTokenString(x) << "\tInput Token = " << getTokenString(c) << std::endl;
	    }
	    else if(prod_index > -1){
		pushRHS(prod_index);
	    }

	    else{
		//ERROR		     
		std::cout << "Parse Error: no production selected for Top Token" << std::endl;
		std::cout << "Top Token = " << getTokenString(x) << "\tInput Token = " << getTokenString(c) << std::endl;
	    }

	}
	
	if (my_scanner.getErr()){
	    //ERROR
	    parser_err = true;
	    std::cout << "Parse Error: scan error reported" << std::endl;
	    std::cout << "Top Token = " << getTokenString(x) << "\tInput Token = " << getTokenString(c) << std::endl;
	}
    }

    if (my_scanner.getEOF() && !my_token_stack.empty()){
        //ERROR
        std::cout << "Parse Error: unexpected end of source" << std::endl;
        std::cout << "Top Token = " << getTokenString(x) << "\tInput Token = " << getTokenString(c) << std::endl;
    }
    else if (my_token_stack.empty() && !my_scanner.getEOF()){
        //ERROR
        std::cout << "Parse Error: unexpected tokens in source past end of program" << std::endl;
        std::cout << "Top Token = " << getTokenString(x) << "\tInput Token = " << getTokenString(c) << std::endl;
    }
    else if (!parser_err && my_scanner.getEOF() && my_token_stack.empty()) std::cout << "Parser: success!" << std::endl;
}

int parser::chooseProd(token topToken, token inputToken){
    bool prod_found = false;
    int i = -1;
    foundLHS = true; 

    while(!prod_found && i < GR_NUM_PRODS){
	i++;	
	if (GR_PROD[i][GR_LHS_NDX] == topToken.tokId){
	    //check first element of select set
	    if (GR_PROD[i][GR_SELECT_FNDX] == E) prod_found = true;

	    else{
		//search select set		    
	    	for (int j = GR_SELECT_FNDX; j <= GR_SELECT_LNDX; j++){
	    	        if (GR_PROD[i][j] == inputToken.tokId)
			    	prod_found = true; 
	    	}
	    }
	}
    }

    if(!prod_found){
	if (i == -1) foundLHS = false;
	i = -1;
    }
    return i;
}

void parser::pushRHS(int prod_index){
    token temp;

    for (int i = GR_RHS_LNDX; i >= GR_RHS_FNDX; i--){
	if (GR_PROD[prod_index][i] != E){
	    //push it on to the stack
	    temp.tokId = GR_PROD[prod_index][i];
	    my_token_stack.push(temp);
	}
    }
}
