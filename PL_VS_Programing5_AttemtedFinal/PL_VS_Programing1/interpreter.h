#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "lexanalyzer.h"
#include "expEvaluator.h"
#include <vector>
#include <string>
using namespace std;



class Interpreter {
private:


public:
	LexicalAnalyzer loopWhile(LexicalAnalyzer, ExpEvaluator&, LexicalAnalyzer::tokenLineType, int&);
	void lineType(LexicalAnalyzer, ExpEvaluator&);
	
};

#endif // !INTERPRETER_H 

