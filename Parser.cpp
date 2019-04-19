// /*
// <program>  ->     <vars> <block>
// <block>    ->     void <vars> <stats> end
// <vars>     ->     empty | var Identifier : Integer <vars> 
// <expr>     ->     <A> + <expr> | <A> - <expr> | <A>
// <A>        ->     <N> / <A> | <N>
// <N>        ->     <M> * <N> | <M>
// <M>        ->     % <M> |  <R>
// <R>        ->     ( <expr> ) | Identifier | Integer
// <stats>    ->     <stat> ; <mStat>
// <mStat>    ->     empty |  <stat>  ;  <mStat>
// <stat>     ->     <in> | <out> | <block> | <if> | <loop> | <assign>
// <in>       ->     scan  Identifier 
// <out>      ->     print <expr>
// <if>       ->     cond [ <expr> <RO> <expr> ] <stat>
// <loop>     ->     iter [ <expr> <RO> <expr> ] <stat>
// <assign>   ->     Identifier  = <expr>  
// <RO>       ->     < | = <  | >  | = > | < >   |   =            
// */

// /*
// #include "ScannerTester.h"
// #include "Scanner.h"

// void TestScanner(std::FILE* file) {

//         Token::Token token;
//         //std::printf("[L#] [Instance] | Identifier\n----------------------------\n");
//         std::printf("{ token, ""instance"", line# }\n");
//         Scanner scanner(file);
//         while(1){
//                 token = scanner.getToken();
//                 // printf("[%2d] [%8s] | %s \n",
//                 //      token.line, token.instance.c_str(),
//                 //      Token::Idname[token.id].c_str() );
//                 printf("{ %s , ""%s"", %2d }\n",
//                         Token::Idname[token.id].c_str(),
//                         token.instance.c_str(),
//                         token.line);
//                  switch(token.id){
//                         case Token::eofTk:
//                         case Token::errTk:
//                                 return;
//                         default:
//                                 break;
//                  }
//         }
// }
// */
#include "Parser.h"

// Token::Token tk;
// Scanner scanner(file);

const bool DEBUG = 1;

void Parser::error(std::string msg){
	std::printf("%s\n", msg.c_str());
	return;
}

// /*
// <vars> -> empty | var Identifier : Integer <vars>
// */
// void Parser::Vars(Token::Token tk){

// 	if(tk.id == Token::varTk) { 
// 		tk = scanner.getToken();

// 		if(tk.id == Token::identifierTk) {
// 			tk = scanner.getToken();

// 			if(tk.id == Token::colonTk) {
// 				tk = scanner.getToken();

// 				if(tk.id == Token::intTk) {
// 					tk = scanner.getToken();
// 					Vars(tk);
// 					return;
// 				}
// 				else {
// 					error("Vars: Expected intTk");
// 					return;
// 				}
// 			}
// 			else {
// 				error("Vars: Expected colonTk");
// 				return;
// 			}
// 		}
// 		else {
// 			error("Vars: Expected identifierTk");
// 			return;
// 		}
// 	}
// 	else {
// 		error("Vars: Expected varTk"); 
// 		return;
// 	}
// }

// /*
// <in> -> scan Identifier
// */
// void Parser::In(Token::Token tk) {

// 	if(tk.id == Token::scanTk){

// 		tk = scanner.getToken();

// 		if(tk.id == Token::identifierTk){
// 			tk = scanner.getToken();
// 			return;
// 		}

// 		else{
// 			error("In: Expected identifierTk");
// 			return;
// 		}

// 	}
// 	else{
// 		error("In: Expected scanTk");
// 		return;
// 	}
// }

// // <R>	->	( <expr> ) | Identifier | Integer
// void Parser::R(Token::Token tk) {

// 	if(tk.id == Token::lparenTk) {

// 		tk = scanner.getToken();
// 		Expr(tk);

// 		if(tk.id == Token::rparenTk) {
// 			tk = scanner.getToken();
// 			return;
// 		}

// 	}

// 	if(tk.id == Token::identifierTk) {
// 		tk = scanner.getToken();
// 		return;
// 	}

// 	if(tk.id == Token::intTk) {
// 		tk = scanner.getToken();
// 		return;
// 	}

// }

// // <M>	->	% <M> |  <R>
// void Parser::M(Token::Token tk) {

// 	if(tk.id == Token::modTk) {
// 		tk = scanner.getToken();
// 		M(tk);
// 		return;
// 	}

// 	if(tk.id == Token::lparenTk) {
// 		R(tk);
// 		return;
// 	}

// 	else {
// 		error("M: Expected ( or %");
// 		return;
// 	}

// }

// // <N>	->	<M> * <N> | <M>
// void Parser::N(Token::Token tk) {

// 	if(tk.id == Token::modTk) {

// 		M(tk);

// 		if(tk.id == Token::multTk) {
// 			tk = scanner.getToken();
// 			N(tk);
// 			return;
// 		}

// 		return;
// 	}

// 	else {
// 		error("N: Expected %");
// 		return;
// 	}
// }

// // <A>	->	<N> / <A> | <N>
// void Parser::A(Token::Token tk) {

// 	if(tk.id == Token::modTk){

// 		N(tk);

// 		if(tk.id == Token::bslashTk) {
// 			tk = scanner.getToken();
// 			A(tk);
// 			return;
// 		}

// 		return;
// 	}

// }

// <expr>	->	<A> + <expr> | <A> - <expr> | <A>
// <A>		->	<N> / <A> | <N>
// <N>		->	<M> * <N> | <M>
// <M>		->	% <M> |  <R>
// <R>		->	( <expr> ) | Identifier | Integer

// void Parser::Expr(Token::Token tk) {

// 	if(tk.id == (Token::modTk | Token::lparenTk | Token::identifierTk | Token::intTk )) {
		
// 		A(tk);
		
// 		if(tk.id == (Token::plusTk | Token::minusTk)) {
			
// 			tk = scanner.getToken();
// 			Expr(tk);
// 			return;
		
// 		}

// 		return;
// 	}

// 	else {
// 		error("Expr: Expected %,(,ident,int");
// 		return;
// 	}
// }

// // <out> ->  print <expr>
// void Parser::Out(Token::Token tk) {

// 	if(tk.id == printTk){
// 		tk = scanner.getToken();
// 		Expr(tk);
// 		return;
// 	}
// 	else {
// 		error("Out: Expected printTk");
// 		return;
// 	}

// }

// //<RO>	->	< | = < | > | = > | < > | =  
// void Parser::RO(Token::Token tk) {

// 	// < | < >
// 	if(tk.id == Token::lessTk){
// 		tk = scanner.getToken();
// 		if(tk.id == Token::greaterTk){
// 			tk = scanner.getToken();
// 			return;
// 		}
// 		return;
// 	}

// 	// = | =< | =>
// 	if(tk.id == Token::assignTk) {
// 		tk = scanner.getToken();
// 		if(tk.id == Token::lessTk) {
// 			tk = scanner.getToken();
// 			return;
// 		}
// 		else if(tk.id == Token::greaterTk) {
// 			tk = scanner.getToken();
// 			return;
// 		}
// 		else {
// 			return;
// 		}
// 	}

// 	if(tk.id == Token::greaterTk) {
// 		tk = scanner.getToken();
// 		return;
// 	}

// 	else {
// 		error("RO: Expected RO token");
// 		return;
// 	}
// }

// // <if>	->	cond [ <expr> <RO> <expr> ] <stat>
// void Parser::If(Token::Token tk) {

// 	if(tk.id == Token::condTk) {

// 		tk = scanner.getToken();

// 		if(tk.id == Token::lbracketTk) {

// 			tk = scanner.getToken();
// 			Expr(tk);
// 			RO(tk);
// 			Expr(tk);

// 			if(tk.id == Token::rbracketTk) {

// 				tk = scanner.getToken();
// 				Stat(tk);
// 				return;

// 			}

// 			else {
// 				error("If: Expected ]");
// 				return;
// 			}

// 		}

// 		else {
// 			error("If: Expected [");
// 			return;
// 		}
// 	}

// 	else {
// 		error("If: Expected cond");
// 		return;
// 	}

// 	return;
// }

// // <loop>	->	iter [ <expr> <RO> <expr> ] <stat>
// void Parser::Loop(Token::Token tk) {

// 	if(tk.id == Token::iterTK) {

// 		tk = scanner.getToken();

// 		if(tk.id == Token::lbracketTk) {

// 			tk = scanner.getToken();
// 			Expr(tk);
// 			RO(tk);
// 			Expr(tk);

// 			if(tk.id == Token::rbracketTk) {

// 				tk = scanner.getToken();
// 				Stat(tk);
// 				return;

// 			}
// 			else {
// 				error("Loop: Expected ]");
// 				return;
// 			}
// 		}
// 		else {
// 			error("Loop: Expected [");
// 			return;
// 		}
// 	}
// 	else {
// 		error("Loop: Expected iter");
// 		return;
// 	}

// }

// // <assign>	->	Identifier  = <expr>  
// void Parser::Assign(Token::Token tk) {

// 	if(tk.id == Token::identifierTk) {

// 		tk = scanner.getToken();

// 		if(tk.id == Token::assignTk) {

// 			tk = scanner.getToken();
// 			Expr(tk);
// 			return;

// 		}
// 		else {
// 			error("Assign: Expected =");
// 			return;
// 		}
// 	}
// 	error("Assign: Expected Identifier");
// 	return;
// }

// // <stat>  ->  <in> | <out> | <block> | <if> | <loop> | <assign>
// void Parser::Stat(Token::Token tk) {
// 	switch(tk.id){
// 		case(Token::scanTk):
// 			In(tk);
// 			break;
// 		case(Token::printTk):
// 			Out(tk);
// 			break;
// 		case(Token::voidTk):
// 			Block(tk);
// 			break;
// 		case(Token::condTk):
// 			If(tk);
// 			break;
// 		case(Token::iterTk):
// 			Loop(tk);
// 			break;
// 		case(Token::identifierTk):
// 			Assign(tk);
// 			break;
// 		default:
// 			error("Stat: No valid stat tokens");
// 			break;
// 	}
// 	return;
// }

// void Parser::Stats(Token::Token tk) {
// 	//stat(tk);
// 	if(tk.id == Token::semicolonTk){
// 		tk = scanner.getToken();
// 		//mStats(tk);
// 		return;
// 	}
// 	else {
// 		error("Stats: Expected a semicolonTk");
// 		return;
// 	}
// }

// // <block>	->	void <vars> <stats> return
// void Parser::Block(Token::Token tk) {
// 	if(tk.id == Token::voidTk){
// 		tk = scanner.getToken();
// 		Vars(tk);
// 		//stats(tk);
// 		if(tk.id == Token::returnTk){
// 			std::printf("exiting block");
// 			return;
// 		}
// 	}
// 	else{
// 		error("Block: Expected voidTk");
// 		return;
// 	}
// }

// <program>	->	<vars> <block>
void Parser::Program() {
	// if(tk.id == (Token::emptyTk || Token::varTk) ) {
	if( this->tk.id == Token::varTk ) {
		//Vars(tk);
		return;
	}
	else if( this->tk.id == Token::voidTk ) {
		//block();
		return;
	}

	else{
		error("Program: Expected a varTk or voidTk");
		return;
	}
}

void Parser::GetToken() {
	this->tk = this->scanner.getToken();
}

bool Parser::Parse() {
	if(DEBUG)
		std::printf("Parse: Entered Parse\n");
	this->GetToken();
	Program();
	if(this->tk.id == Token::eofTk)
		return true;
	return false;
}

// void Parser() {
	
// 	// tk = scanner.getToken();

// 	//program(tk);

// 	return;
// }