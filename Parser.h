#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"

class Parser {

	Scanner scanner;
	Token::Token tk;

	void Program();
	void Block();
	void Vars();
	void Expr();
	void A();
	void N();
	void M();
	void R();
	void Stats();
	void MStats();
	void Stat();
	void In();
	void Out();
	void If();
	void Loop();
	void Assign();
	void RO();
	void error(std::string msg);
	void GetToken();

public:
	Parser(){ std::printf("Hello World\n"); }
	Parser(std::FILE* fp):scanner(fp){}
	void GetFile(std::FILE* fp){ this->scanner.GetFile(fp); }
	bool Parse();

};

#endif