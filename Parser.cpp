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
	std::printf("%s\nToken: ", msg.c_str());
	PrintToken();
	return;
}

// <vars> -> empty | var Identifier : Integer <vars>
void Parser::Vars(){
	if(DEBUG)
		std::printf("-->Vars\n");

	if(this->tk.id == Token::varTk) { 
		this->GetToken();

		if(this->tk.id == Token::identifierTk) {
			this->GetToken();

			if(this->tk.id == Token::colonTk) {
				this->GetToken();

				if(this->tk.id == Token::integerTk) {
					this->GetToken();
					Vars();
					if(DEBUG){ std::printf("Vars-->\n"); }
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
	if(DEBUG){ std::printf("Vars-->\n"); }
	return;
}


// <in> -> scan Identifier
void Parser::In() {
	if(DEBUG)
		std::printf("-->In\n");

	if(this->tk.id == Token::scanTk){

		this->GetToken();

		if(this->tk.id == Token::identifierTk){
			this->GetToken();
			if(DEBUG){ std::printf("In-->\n"); }
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
void Parser::R() {
	if(DEBUG)
		std::printf("-->R\n");

	if(this->tk.id == Token::lparenTk) {

		this->GetToken();
		Expr();

		if(this->tk.id == Token::rparenTk) {
			this->GetToken();
			if(DEBUG){ std::printf("R-->\n"); }
			return;
		}

	}

	if(this->tk.id == Token::identifierTk) {
		this->GetToken();
		if(DEBUG){ std::printf("R-->\n"); }
		return;
	}

	if(this->tk.id == Token::integerTk) {
		this->GetToken();
		if(DEBUG){ std::printf("R-->\n"); }
		return;
	}

	else {
		error("R: Expected (, identifier, integer");
		return;
	}

}

// <M>	->	% <M> |  <R>
void Parser::M() {
	if(DEBUG)
		std::printf("-->M\n");

	if(this->tk.id == Token::modTk) {
		this->GetToken();
		M();
		if(DEBUG){ std::printf("M-->\n"); }
		return;
	}

	if(this->tk.id == Token::lparenTk ||
		this->tk.id == Token::identifierTk ||
		this->tk.id == Token::integerTk) {

		R();
		if(DEBUG){ std::printf("M-->\n"); }
		return;
	}

	else {
		error("M: Expected ( or %");
		return;
	}

}

// <N>	->	<M> * <N> | <M>
void Parser::N() {
	if(DEBUG)
		std::printf("-->N\n");

	if(this->tk.id == Token::modTk ||
		this->tk.id == Token::lparenTk ||
		this->tk.id == Token::identifierTk ||
		this->tk.id == Token::integerTk) {

		M();

		if(this->tk.id == Token::multTk) {
			this->GetToken();
			N();
			if(DEBUG){ std::printf("N-->\n"); }
			return;
		}
		if(DEBUG){ std::printf("N-->\n"); }
		return;
	}

	else {
		error("N: Expected %");
		return;
	}
}

// <A>	->	<N> / <A> | <N>
void Parser::A() {
	if(DEBUG)
		std::printf("-->A\n");

	if(this->tk.id == Token::modTk ||
		this->tk.id == Token::lparenTk ||
		this->tk.id == Token::identifierTk ||
		this->tk.id == Token::integerTk){

		N();

		if(this->tk.id == Token::bslashTk) {
			this->GetToken();
			A();
			if(DEBUG){ std::printf("A-->\n"); }
			return;
		}
		if(DEBUG){ std::printf("A-->\n"); }
		return;
	} 

}

// <expr>	->	<A> + <expr> | <A> - <expr> | <A>
// <A>		->	<N> / <A> | <N>
// <N>		->	<M> * <N> | <M>
// <M>		->	% <M> |  <R>
// <R>		->	( <expr> ) | Identifier | Integer

void Parser::Expr() {
	if(DEBUG)
		std::printf("-->Expr\n");

	//if(this->tk.id == (Token::modTk || Token::lparenTk || Token::identifierTk || Token::intTk )) {
	switch(this->tk.id){
		case(Token::modTk):
		case(Token::lparenTk):
		case(Token::identifierTk):
		case(Token::integerTk):
			A();
			if(this->tk.id == Token::plusTk || this->tk.id == Token::minusTk) {
				this->GetToken();
				Expr();
				if(DEBUG){ std::printf("Expr-->\n"); }
				return;
			}
			return;
		default:
			error("Expr: Expected %,(,ident,int");
			return;
	}
	if(DEBUG){ std::printf("Expr-->\n"); }
	return;
}

// <out> ->  print <expr>
void Parser::Out() {
	if(DEBUG)
		std::printf("-->Out\n");

	if(this->tk.id == Token::printTk){
		this->GetToken();
		Expr();
		if(DEBUG){ std::printf("Out-->\n"); }
		return;
	}
	else {
		error("Out: Expected printTk");
		return;
	}

}

//<RO>	->	< | = < | > | = > | < > | =  
void Parser::RO() {
	if(DEBUG)
		std::printf("-->RO\n");

	// < | < >
	if(this->tk.id == Token::lessTk){
		this->GetToken();
		if(this->tk.id == Token::greaterTk){
			this->GetToken();
			if(DEBUG){ std::printf("RO-->\n"); }
			return;
		}
		if(DEBUG){ std::printf("RO-->\n"); }
		return;
	}

	// = | =< | =>
	if(this->tk.id == Token::assignTk) {
		this->GetToken();
		if(this->tk.id == Token::lessTk) {
			this->GetToken();
			if(DEBUG){ std::printf("RO-->\n"); }
			return;
		}
		else if(this->tk.id == Token::greaterTk) {
			this->GetToken();
			if(DEBUG){ std::printf("RO-->\n"); }
			return;
		}
		else {
			if(DEBUG){ std::printf("RO-->\n"); }
			return;
		}
	}

	if(this->tk.id == Token::greaterTk) {
		this->GetToken();
		if(DEBUG){ std::printf("RO-->\n"); }
		return;
	}

	else {
		error("RO: Expected RO token");
		return;
	}
}

// <if>	->	cond [ <expr> <RO> <expr> ] <stat>
void Parser::If() {
	if(DEBUG)
		std::printf("-->If\n");

	if(this->tk.id == Token::condTk) {

		this->GetToken();

		if(this->tk.id == Token::lbracketTk) {

			this->GetToken();
			Expr();
			RO();
			Expr();

			if(this->tk.id == Token::rbracketTk) {

				this->GetToken();
				Stat();
				if(DEBUG){ std::printf("If-->\n"); }
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
	if(DEBUG){ std::printf("If-->\n"); }
	return;
}

// <loop> -> iter [ <expr> <RO> <expr> ] <stat>
void Parser::Loop() {
	if(DEBUG)
		std::printf("-->Loop\n");

	if(this->tk.id == Token::iterTk) {

		this->GetToken();

		if(this->tk.id == Token::lbracketTk) {

			this->GetToken();
			Expr();
			RO();
			Expr();

			if(this->tk.id == Token::rbracketTk) {

				this->GetToken();
				Stat();
				if(DEBUG){ std::printf("Loop-->\n"); }
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

// <assign>	-> Identifier = <expr>  
void Parser::Assign() {
	if(DEBUG)
		std::printf("-->Assign\n");

	if(this->tk.id == Token::identifierTk) {

		this->GetToken();

		if(this->tk.id == Token::assignTk) {

			this->GetToken();
			Expr();
			if(DEBUG){ std::printf("Assign-->\n"); }
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
void Parser::Stat() {
	if(DEBUG)
		std::printf("-->Stat\n");

	switch(this->tk.id){
		case(Token::scanTk):
			In();
			break;
		case(Token::printTk):
			Out();
			break;
		case(Token::voidTk):
			Block();
			break;
		case(Token::condTk):
			If();
			break;
		case(Token::iterTk):
			Loop();
			break;
		case(Token::identifierTk):
			Assign();
			break;
		default:
			error("Stat: No valid stat tokens");
			break;
	}
	if(DEBUG){ std::printf("Stat-->\n"); }
	return;
}

// <mStat>	->	empty |  <stat>  ;  <mStat>
void Parser::MStat() {
	if(DEBUG)
		std::printf("-->MSstat\n");

	if(this->tk.id == Token::scanTk ||
		this->tk.id == Token::printTk ||
		this->tk.id == Token::voidTk ||
		this->tk.id == Token::condTk ||
		this->tk.id == Token::iterTk ||
		this->tk.id == Token::identifierTk) {

		Stat();
		if(this->tk.id == Token::semicolonTk){
			this->GetToken();
			MStat();
		}
		else {
			error("MStat: Expected ;");
			return;
		}
		if(DEBUG){ std::printf("MStats-->\n"); }
		return;
	}

	// if(this->tk.id == Token::semicolonTk) {
	// 	this->GetToken();
	// 	MStat();
	// 	if(DEBUG){ std::printf("MStats-->\n"); }
	// 	return;
	// }

	else {
		//Stat();
		if(DEBUG){ std::printf("MStats-->\n"); }
		return;
	}

}

// <stats>	->	<stat> ; <mStat>
void Parser::Stats() {
	if(DEBUG)
		std::printf("-->Stats\n");

	switch(this->tk.id){
		case(Token::scanTk):
		case(Token::printTk):
		case(Token::voidTk):
		case(Token::condTk):
		case(Token::iterTk):
		case(Token::identifierTk):
			Stat();
			if(this->tk.id == Token::semicolonTk) {
				this->GetToken();
				MStat();
				if(DEBUG){ std::printf("Stats-->\n"); }
				return;
			} else {
				error("Stats: Expected a semicolonTk");
				return;
			}
		default:
			error("Stats: No valid stat tokens");
			break;
	}
	
}

// <block>	->	void <vars> <stats> return
void Parser::Block() {
	if(DEBUG)
		std::printf("-->Block\n");

	if(this->tk.id == Token::voidTk){
		this->GetToken();
		Vars();
		Stats();
		if(this->tk.id == Token::returnTk){
			this->GetToken();
			if(DEBUG){ std::printf("Block-->\n"); }
			return;
		}
	}
	else{
		error("Block: Expected voidTk");
		return;
	}
}

// <program>	->	<vars> <block>
void Parser::Program() {
	if(DEBUG)
		std::printf("-->Program\n");

	// if(tk.id == (Token::emptyTk || Token::varTk) ) {
	if( this->tk.id == Token::varTk ) {
		Vars();
		if( this->tk.id == Token::voidTk) {
			Block();
			if(DEBUG){ std::printf("Program-->\n"); }
			return;
		} else {
			error("Program: Expected void");
			return;
		}
		return;	
	}

	else if( this->tk.id == Token::voidTk ) {
		Block();
		if(DEBUG){ std::printf("Program-->\n"); }
		return;
	}

	else{
		error("Program: Expected a varTk or voidTk");
		return;
	}
}

void Parser::GetToken() {
	this->tk = this->scanner.getToken();
	PrintToken();
}

void Parser::PrintToken() {
	// printf("{ %s , ""%s"", %2d }\n",
	// 		Token::Idname[token.id].c_str(),
	// 		token.instance.c_str(),
	// 		token.line);
	printf("{ %s , ""%s"", %2d }\n",
		Token::Idname[tk.id].c_str(),
		tk.instance.c_str(),
		tk.line);
}

bool Parser::Parse() {
	if(DEBUG) {
		std::printf("Parse: ");
	}
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