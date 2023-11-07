#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H
#include <vector>
#include <string>
#include "lexanalyzer.h"
#include <map>
// type decloration

//interface class decloration
class ExpEvaluator {
private:
	typedef std::map<std::string, std::string> symbolTableType;
	symbolTableType symbolTable;
	
public:
	//postfix and infix functions
	LexicalAnalyzer::tokenLineType convertToPostfix(LexicalAnalyzer);
	int evaluatePostfix(LexicalAnalyzer::tokenLineType);
	int evaluateOperands(int, LexicalAnalyzer::pairType, int);
	int operatorPrecedence(LexicalAnalyzer::pairType);

	// SymbolTable functions
	void clearSymbolTable();
	void storeSymbolTable(std::string, std::string);
	string retrieveSymbolTable(string key);

	//helpful functions
	bool isExpression(LexicalAnalyzer);
	void showVec(LexicalAnalyzer::tokenLineType vecPair);
};

#endif // EXPEVALUATOR_H

