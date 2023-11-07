#ifndef INTERFACE_H
#define INTERFACE_H
#include "lexanalyzer.h"
#include "expEvaluator.h"
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
public:
	//commands
	void startInterface();
	void quit();
	void help(string);
	void read(string);
	void show(string);
	void clear();
	//tool classes
	bool isCommand(string); 
	void useCommand(string, string);
	void helpInstructions(string);
};

#endif // !INTERFACE_H

