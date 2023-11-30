#include <iostream>
#include "interface.h"
#include "lexanalyzer.h"
#include "expEvaluator.h"
#include "interpreter.h"
#include <vector>
#include <string>
#include <map>
#include <fstream>
using namespace std;

// declorations
bool isRunning = true;
bool isHelping = false;
bool loopRunning = false;
bool Interface::isCommand(string commandName) {
	if (commandName == "help"
		|| commandName == "quit"
		|| commandName == "read"
		|| commandName == "show"
		|| commandName == "clear"
		|| commandName == "run") {
		return true;
	}
	else return false;

}

void Interface::startInterface() {
	

	cout << "\nThis is the start of the interface!\n";
	while(isRunning){

		if (loopRunning) {
			cout << "... ";
		}
		else {
			cout << ">>> ";
		}

		string userInput;
		getline(cin, userInput);
		while (userInput.empty() && !loopRunning) {
			getline(cin, userInput);
		}

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


		//allInLineCodeLexed.tokenInfo.push_back(lexAnalysisExpEvaluator.tokenInfo[0]);
		// 
		// check if user input is an exprestion
		if(isCommand(commandName)){
		 useCommand(argName, commandName);
		}
		else if ((loopRunning ||
			lexAnalysisExpEvaluator.tokenInfo[0][0].second == categoryType::KEYWORD 
			|| lexAnalysisExpEvaluator.tokenInfo[0][0].second == categoryType::COMMENT
			|| lexAnalysisExpEvaluator.tokenInfo[0][0].second == categoryType::IDENTIFIER && lexAnalysisExpEvaluator.tokenInfo[0][0 + 1].second == categoryType::ASSIGNMENT_OP
			|| expEvaluator.isExpression(lexAnalysisExpEvaluator)
			)  && !isCommand(commandName)) {


			if (loopRunning ||lexAnalysisExpEvaluator.tokenInfo[0][0].first == "while" || lexAnalysisExpEvaluator.tokenInfo[0][0].first == "if") {
				if (loopRunning) {
					getLoop();
				}
				else {
					getLoop();
					loopRunning = true;
				}
				
			}


			//int postfixResult = expEvaluator.evaluatePostfix(expEvaluator.convertToPostfix(lexAnalysisExpEvaluator));
			//cout << postfixResult << endl;
		}
		
	}
}


void Interface::getLoop() {
 
	if (!loopRunning) {
		allInLineCodeLexed.tokenInfo.push_back(lexAnalysisExpEvaluator.tokenInfo[0]);
	}
	else if (lexAnalysisExpEvaluator.tokenInfo[0].empty()) {
		inLinePySubi.lineType(allInLineCodeLexed, expEvalFile);
		loopRunning = false;
	} 
	else if (lexAnalysisExpEvaluator.tokenInfo[0][0].second == categoryType::INDENT) {
		allInLineCodeLexed.tokenInfo.push_back(lexAnalysisExpEvaluator.tokenInfo[0]);
	}
	else {
		cout << "Error, no indent in if or while statment";
	}
	//if (lexAnalysisExpEvaluator.tokenInfo[0][0].first == "while") {
	//	allInLineCodeLexed.tokenInfo.push_back(lexAnalysisExpEvaluator.tokenInfo[0]);

	//	cout << endl;
	//	cout << "... ";
	//	string loopInput;
	//	getline(cin, loopInput);
	//	while (loopInput.empty()) {
	//		getline(cin, loopInput);
	//	}

	//	while (true) {
	//		cout << "... ";
	//		
	//		getline(cin, loopInput);
	//		while (loopInput.empty()) {
	//			getline(cin, loopInput);
	//		}

	//		lexAnalysisExpEvaluator.clear();
	//		expEvaluatorCode.push_back(loopInput);

	//		//generate tokens based off the user input
	//		lexAnalysisExpEvaluator.generateTokens(expEvaluatorCode);

	//	}


	//}
	//else if (lexAnalysisExpEvaluator.tokenInfo[0][0].first == "if") {

	//}
}


//helpful declorations
void Interface::useCommand(string argName, string commandName) {
	if (commandName == "help") help(argName);
	if (commandName == "quit") quit();
	if (commandName == "read") read(argName);
	if (commandName == "show") show(argName);
	if (commandName == "clear") clear();
	if (commandName == "run") run();

}
void Interface::helpInstructions(string argName) {

	map<string, string> instructions;
	instructions["quit"] = "This will quit the whole program.\n";
	instructions["show"] = "This will show the contents of what has been saved from the file that has been read.\n";
	instructions["read"] = "This will read the contents of the file given.\n";
	instructions["help"] = "This will give helpful imformation for commands imput.\n";
	instructions["clear"] = "This will clear the contents saved from the file that was read.\n";
	instructions["commands"] = "exit, quit, help, read, show, clear, read.\n";
	instructions["run"] = "Run will run the code that was red from the file.\n";

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
	lexAnalysis.clear();
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
	if (argName == ""){
		for (auto line : programCode) {
		cout << "[" << i << "]" << " " << line << endl;
		i++;
		}
	}
	else if (argName == "tokens") {
		lexAnalysis.show();
	}
	else if (argName == "variables") {
		expEvalFile.showSymbolTalble();

	}

}
void Interface::run() {
	pysubi.lineType(lexAnalysis, expEvalFile);
	cout << endl;
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
