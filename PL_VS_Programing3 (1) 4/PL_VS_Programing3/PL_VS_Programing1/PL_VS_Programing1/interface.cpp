#include <iostream>
#include "interface.h"
#include "lexanalyzer.h"
#include "expEvaluator.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>
using namespace std;

// declorations
bool isRunning = true;
bool isHelping = false;
bool Interface::isCommand(string commandName) {
	if (commandName == "help"
		|| commandName == "quit"
		|| commandName == "read"
		|| commandName == "show"
		|| commandName == "clear") {
		return true;
	}
	else return false;

}

void Interface::startInterface() {
	

	cout << "\nThis is the start of the interface!\n";
	while(isRunning){
		
		cout << ">>> ";
		string userInput;
		getline(cin, userInput);

		string argName = "";
		string commandName = "";

		bool addToCommandName = true;

		//traversing user's input

		for (auto ch : userInput) {
			if (ch == ')') {
				break;
			}
			else if (ch == '(') {
				addToCommandName = false;
			}
			else if (addToCommandName) {
				commandName += ch;
			}
			else {
				argName += ch;
			}
		}
		expEvaluatorCode.clear();
		lexAnalysisExpEvaluator.clear();
		expEvaluatorCode.push_back(userInput);
		//generate tokens based off the user input
		lexAnalysisExpEvaluator.generateTokens(expEvaluatorCode);
		// check if user input is an exprestion
		if (expEvaluator.isExpression(lexAnalysisExpEvaluator) && !isCommand(commandName)) {
			int postfixResult = expEvaluator.evaluatePostfix(expEvaluator.convertToPostfix(lexAnalysisExpEvaluator));
			cout << postfixResult << endl;
		}
		else useCommand(argName, commandName);
	}
}

//helpful declorations
void Interface::useCommand(string argName, string commandName) {
	if (commandName == "help") help(argName);
	if (commandName == "quit") quit();
	if (commandName == "read") read(argName);
	if (commandName == "show") show(argName);
	if (commandName == "clear") clear(); 
}
void Interface::helpInstructions(string argName) {

	map<string, string> instructions;
	instructions["quit"] = "This will quit the whole program.\n";
	instructions["show"] = "This will show the contents of what has been saved from the file that has been read.\n";
	instructions["read"] = "This will read the contents of the file given.\n";
	instructions["help"] = "This will give helpful imformation for commands imput.\n";
	instructions["clear"] = "This will clear the contents saved from the file that was read.\n";
	instructions["commands"] = "exit, quit, help, read, show, clear, read.\n";

	cout << instructions[argName];
}

//command delclorations
void Interface::quit() {
	isRunning = false;
}
void Interface::clear() {
	expEvaluatorCode.clear();
	programCode.clear();
	lexAnalysis.clear();
	expEvaluator.clearSymbolTable();
	lexAnalysisExpEvaluator.clear();
}
void Interface::read(string argName) {
	
	ifstream file;
	file.open(argName);

	if (!file.is_open()) {
		cout << "Error opening the file.\n";
	}
	else{
		programCode.clear();
		string line;
		while (getline(file, line)) {
			programCode.push_back(line);
		}
	}
	lexAnalysis.generateTokens(programCode);
	cout << endl;
}
void Interface::show(string argName) {
	int i = 0;
	if (argName != "tokens"){
		for (auto line : programCode) {
		cout << "[" << i << "]" << " " << line << endl;
		i++;
		}
	}
	else if (argName == "tokens") {
		lexAnalysis.show();
	}
}
void Interface::help(string argName) {
	//use if paramitar is given 1st time
	cout << endl << "Type a command for more info. Type exit to go back.\n";
	helpInstructions(argName);
	isHelping = true; 
	
	//if paramitar is given after help is entered
	while (isHelping) {

		cout << "help> ";
		string helpInput;
		getline(cin, helpInput);
		helpInstructions(helpInput);

		if (helpInput == "exit" || helpInput == "exit()") {
			isHelping = false;
			cout << endl;
		}
	}
}
