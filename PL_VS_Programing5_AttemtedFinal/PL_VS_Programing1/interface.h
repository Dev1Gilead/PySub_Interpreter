#ifndef INTERFACE_H
#define INTERFACE_H
#include "lexanalyzer.h"
#include "expEvaluator.h"
#include "interpreter.h"
#include <vector>
#include <string>

using namespace std;
// type decloration

//interface class decloration
class Interface {
private:
	typedef vector<string> programType;
	//code taken from file
	programType programCode;
	//user input in terminal
	programType expEvaluatorCode;
	//evaluate programCode
	LexicalAnalyzer lexAnalysis;
	//evaluate expEvaluatorCode
	LexicalAnalyzer lexAnalysisExpEvaluator;
	//class with functions for evaluating user input in terminal
	ExpEvaluator expEvaluator;

	LexicalAnalyzer allInLineCodeLexed;

	ExpEvaluator expEvalFile;
	Interpreter pysubi;
	Interpreter inLinePySubi;


public:
	//commands
	void startInterface();
	void quit();
	void help(string);
	void read(string);
	void show(string);
	void clear();
	void run();
	void runInLine();
	void getLoop();
	//tool classes
	bool isCommand(string); 
	void useCommand(string, string);
	void helpInstructions(string);
};

#endif // !INTERFACE_H

