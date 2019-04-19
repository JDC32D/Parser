/*
<program>  ->     <vars> <block>
<block>    ->     void <vars> <stats> end
<vars>     ->     empty | var Identifier : Integer <vars> 
<expr>     ->     <A> + <expr> | <A> - <expr> | <A>
<A>        ->     <N> / <A> | <N>
<N>        ->     <M> * <N> | <M>
<M>        ->     % <M> |  <R>
<R>        ->     ( <expr> ) | Identifier | Integer
<stats>    ->     <stat> ; <mStat>
<mStat>    ->     empty |  <stat>  ;  <mStat>
<stat>     ->     <in> | <out> | <block> | <if> | <loop> | <assign>
<in>       ->     scan  Identifier 
<out>      ->     print <expr>
<if>       ->     cond [ <expr> <RO> <expr> ] <stat>
<loop>     ->     iter [ <expr> <RO> <expr> ] <stat>
<assign>   ->     Identifier  = <expr>  
<RO>       ->     < | = <  | >  | = > | < >   |   =            
*/

/*
#include "ScannerTester.h"
#include "Scanner.h"

void TestScanner(std::FILE* file) {

        Token::Token token;
        //std::printf("[L#] [Instance] | Identifier\n----------------------------\n");
        std::printf("{ token, ""instance"", line# }\n");
        Scanner scanner(file);
        while(1){
                token = scanner.getToken();
                // printf("[%2d] [%8s] | %s \n",
                //      token.line, token.instance.c_str(),
                //      Token::Idname[token.id].c_str() );
                printf("{ %s , ""%s"", %2d }\n",
                        Token::Idname[token.id].c_str(),
                        token.instance.c_str(),
                        token.line);
                 switch(token.id){
                        case Token::eofTk:
                        case Token::errTk:
                                return;
                        default:
                                break;
                 }
        }
}
*/
#include "Scanner.h"

Token::Token tk;
Scanner scanner(file);

const bool DEBUG = 1;

void error(std::string msg){
	std::printf("%s\n", msg.c_str());
	return;
}

/*
<vars> -> empty | var Identifier : Integer <vars>
*/
void vars(Token::Token tk){

	if(tk.id == Token::varTk) { 
		tk = scanner.getToken();

		if(tk.id == Token::identifierTk) {
			tk = scanner.getToken();

			if(tk.id == Token::colonTk) {
				tk = scanner.getToken();

				if(tk.id == Token::intTk) {
					tk = scanner.getToken();
					vars(tk);
					return;
				}
				else {
					error("Vars: Expected intTk");
					return;
				}
			}
			else {
				error("Vars: Expected colonTk");
				return;
			}
		}
		else {
			error("Vars: Expected identifierTk");
			return;
		}
	}
	else {
		error("Vars: Expected varTk"); 
		return;
	}
}

/*
<in> -> scan Identifier
*/
void in(Token::Token tk) {

	if(tk.id == Token::scanTk){

		tk = scanner.getToken();

		if(tk.id == Token::identifierTk){
			tk = scanner.getToken();
			return;
		}

		else{
			error("In: Expected identifierTk");
			return;
		}

	}
	else{
		error("In: Expected scanTk");
		return;
	}
}

// <R>	->	( <expr> ) | Identifier | Integer
void R(Token::Token tk) {

	if(tk.id == Token::lparenTk) {

		tk = scanner.getToken();
		expr(tk);

		if(tk.id == Token::rparenTk) {
			tk = scanner.getToken();
			return;
		}

	}

	if(tk.id == Token::identifierTk) {
		tk = scanner.getToken();
		return;
	}

	if(tk.id == Token::intTk) {
		tk = scanner.getToken();
		return;
	}

}

// <M>	->	% <M> |  <R>
void M(Token::Token tk) {

	if(tk.id == Token::modTk) {
		tk = scanner.getToken();
		M(tk);
		return;
	}

	if(tk.id == Token::lparenTk) {
		R(tk);
		return;
	}

	else {
		error("M: Expected ( or %");
		return;
	}

}

// <N>	->	<M> * <N> | <M>
void N(Token::Token tk) {

	if(tk.id == Token::modTk) {

		M(tk);

		if(tk.id == Token::multTk) {
			tk = scanner.getToken();
			N(tk);
			return;
		}

		return;
	}

	else {
		error("N: Expected %");
		return;
	}
}

// <A>	->	<N> / <A> | <N>
void A(Token::Token tk) {

	if(tk.id == Token::modTk){

		N(tk);

		if(tk.id == Token::bslashTk) {
			tk = scanner.getToken();
			A(tk);
			return;
		}

		return;
	}

}
/*
<expr>	->	<A> + <expr> | <A> - <expr> | <A>
<A>		->	<N> / <A> | <N>
<N>		->	<M> * <N> | <M>
<M>		->	% <M> |  <R>
<R>		->	( <expr> ) | Identifier | Integer
*/
void expr(Token::Token tk) {

	if(tk.id == (Token::modTk | Token::lparenTk | Token::identifierTk | Token::intTk )) {
		
		A(tk);
		
		if(tk.id == (Token::plusTk | Token::minusTk)) {
			
			tk = scanner.getToken();
			expr(tk);
			return;
		
		}

		return;
	}

	else {
		error("Expr: Expected %,(,ident,int");
		return;
	}
}

// <out> ->  print <expr>
void out(Token::Token tk) {

	if(tk.id == printTk){
		tk = scanner.getToken();
		expr(tk);
		return;
	}
	else {
		error("Out: Expected printTk");
		return;
	}

}

//<RO>	->	< | = < | > | = > | < > | =  
void RO(Token::Token tk) {

	// < | < >
	if(tk.id == Token::lessTk){
		tk = scanner.getToken();
		if(tk.id == Token::greaterTk){
			tk = scanner.getToken();
			return;
		}
		return;
	}

	// = | =< | =>
	if(tk.id == Token::assignTk) {
		tk = scanner.getToken();
		if(tk.id == Token::lessTk) {
			tk = scanner.getToken();
			return;
		}
		else if(tk.id == Token::greaterTk) {
			tk = scanner.getToken();
			return;
		}
		else {
			return;
		}
	}

	if(tk.id == Token::greaterTk) {
		tk = scanner.getToken();
		return;
	}

	else {
		error("RO: Expected RO token");
		return;
	}
}

// <if>	->	cond [ <expr> <RO> <expr> ] <stat>
void ifCond(Token::Token tk) {

	if(tk.id == Token::condTk) {

		tk = scanner.getToken();

		if(tk.id == Token::lbracketTk) {

			tk = scanner.getToken();
			expr(tk);
			RO(tk);
			expr(tk);

			if(tk.id == Token::rbracketTk) {

				tk = scanner.getToken();
				stat(tk);
				return;

			}

			else {
				error("If: Expected ]");
				return;
			}

		}

		else {
			error("If: Expected [");
			return;
		}
	}

	else {
		error("If: Expected cond");
		return;
	}

	return;
}

// <loop>	->	iter [ <expr> <RO> <expr> ] <stat>
void loop(Token::Token tk) {

	if(tk.id == Token::iterTK) {

		tk = scanner.getToken();

		if(tk.id == Token::lbracketTk) {

			tk = scanner.getToken();
			expr(tk);
			RO(tk);
			expr(tk);

			if(tk.id == Token::rbracketTk) {

				tk = scanner.getToken();
				stat(tk);
				return;

			}
			else {
				error("Loop: Expected ]");
				return;
			}
		}
		else {
			error("Loop: Expected [");
			return;
		}
	}
	else {
		error("Loop: Expected iter");
		return;
	}

}

// <assign>	->	Identifier  = <expr>  
void assign(Token::Token tk) {

	if(tk.id == Token::identifierTk) {

		tk = scanner.getToken();

		if(tk.id == Token::assignTk) {

			tk = scanner.getToken();
			expr(tk);
			return;

		}
		else {
			error("Assign: Expected =");
			return;
		}
	}
	error("Assign: Expected Identifier");
	return;
}

// <stat>  ->  <in> | <out> | <block> | <if> | <loop> | <assign>
void stat(Token::Token tk) {
	switch(tk.id){
		case(Token::scanTk):
			in(tk);
			break;
		case(Token::printTk):
			out(tk);
			break;
		case(Token::voidTk):
			block(tk);
			break;
		case(Token::condTk):
			ifCond(tk);
			break;
		case(Token::iterTk):
			loop(tk);
			break;
		case(Token::identifierTk):
			assign(tk);
			break;
		default:
			error("Stat: No valid stat tokens");
			break;
	}
	return;
}

void stats(Token::Token tk) {
	//stat(tk);
	if(tk.id == Token::semicolonTk){
		tk = scanner.getToken();
		//mStats(tk);
		return;
	}
	else {
		error("Stats: Expected a semicolonTk");
		return;
	}
}

// <block>	->	void <vars> <stats> return
void block(Token::Token tk) {
	if(tk.id == Token::voidTk){
		tk = scanner.getToken();
		vars(tk);
		//stats(tk);
		if(tk.id == Token::returnTk){
			std::printf("exiting block");
			return;
		}
	}
	else{
		error("Block: Expected voidTk");
		return;
	}
}

// <program>	->	<vars> <block>
void program(Token::Token tk) {
	// if(tk.id == (Token::emptyTk || Token::varTk) ) {
	if( tk.id == Token::varTk ) {
		vars(tk);
		return;
	}
	else if( tk.id == Token::voidTk ) {
		//block();
		return;
	}

	else{
		error("Program: Expected a varTk or voidTk");
		return;
	}
}

void Parser(std::FILE* file) {
	
	tk = scanner.getToken();

	program(tk);

	return;
}