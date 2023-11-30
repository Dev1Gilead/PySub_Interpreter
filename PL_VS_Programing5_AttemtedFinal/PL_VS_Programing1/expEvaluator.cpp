#include "expEvaluator.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>

using namespace std;

bool isKeyPresent(const std::map<int, std::string>& myMap, int keyToCheck) {
	auto it = myMap.find(keyToCheck);
	return it != myMap.end();
}

//SymbolTable functions
void ExpEvaluator::storeSymbolTable(string key, string value) {
	symbolTable[key] = value;
}
string ExpEvaluator::retrieveSymbolTable(string key) {
	auto it = symbolTable.find(key);
	if (it != symbolTable.end()) {
		string temp = symbolTable[key];
		return temp;
	}
	else {
		cout << "error: identifier not in map\n";
		cout << "RESTART TERMINAL";
		string x;
		while (true) {
			cin >> x;
		}
		
	}


}
void ExpEvaluator::clearSymbolTable() {
	symbolTable.clear();
}
void ExpEvaluator::showSymbolTalble() {
	for (const auto& pair : symbolTable) {
		std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
	}
}


//postfix and infix functions
int ExpEvaluator::operatorPrecedence(LexicalAnalyzer::pairType pair) {
	if (pair.second == categoryType::LOGICAL_OP) {
		if (pair.first == "not") return 2;
		else if (pair.first == "and") return 1;
		else if (pair.first == "or") return 0;
		else cout << "Error";
	}
	else if (pair.second == categoryType::ARITH_OP) {
		if (pair.first == "*" || pair.first == "/" || pair.first == "%") return 5;
		else if (pair.first == "+" || pair.first == "-") return 4;
		else cout << "Error";
	}
	else if (pair.second == categoryType::RELATIONAL_OP) {
		return 3;
	}
	else cout << "Error";
}
LexicalAnalyzer::tokenLineType ExpEvaluator::convertToPostfix(LexicalAnalyzer expLexicalAnalyzer) {

	LexicalAnalyzer::tokenLineType postfixVect;
	LexicalAnalyzer::tokenLineType stackVec;
	//expLexicalAnalyzer.show();

	//traverse user input by line
	for (LexicalAnalyzer::tokenLineType tempTokenLine : expLexicalAnalyzer.tokenInfo) {
		//traverse by data type of line
		for (LexicalAnalyzer::pairType tempPair : tempTokenLine) {
			//check if number
			if (tempPair.second == categoryType::NUMERIC_LITERAL) {
				postfixVect.push_back(tempPair);
			}
			else if (tempPair.second == categoryType::IDENTIFIER) {
				// call simble table
				postfixVect.push_back(tempPair);
			}
			//check if left pren
			else if (tempPair.second == categoryType::LEFT_PAREN) {
				stackVec.push_back(tempPair);
			}
			//check if right pren
			else if (tempPair.second == categoryType::RIGHT_PAREN) {
				//pop and push back the stack till left pren found
				while (!stackVec.empty() && stackVec.back().second != categoryType::LEFT_PAREN) {
					postfixVect.push_back(stackVec.back());
					stackVec.pop_back();
				}
				
				//removes right pren
				if (stackVec.empty()) {
					cout << "ERROR: Invalid input. No left pren! Answer is invalid" << endl;
				}
				else if (stackVec.back().second == categoryType::LEFT_PAREN) {
					stackVec.pop_back();
				}

			}
			//check if oporator 
			else if (tempPair.second == categoryType::ARITH_OP || tempPair.second == categoryType::LOGICAL_OP || tempPair.second == categoryType::RELATIONAL_OP) {
				while (!stackVec.empty() && stackVec.back().second != categoryType::LEFT_PAREN && operatorPrecedence(stackVec.back()) >= operatorPrecedence(tempPair)) {
					postfixVect.push_back(stackVec.back());
					stackVec.pop_back();
				}
				stackVec.push_back(tempPair);
			}
	
		}
	}
	while (!stackVec.empty()) {
		postfixVect.push_back(stackVec.back());
		stackVec.pop_back();
	}
	//ExpEvaluator temp;
	//temp.showVec(postfixVect);
	return postfixVect;
}
int ExpEvaluator::evaluateOperands(int operand1, LexicalAnalyzer::pairType op, int operand2) {
	if (op.first == "+") return(operand1 + operand2);
	else if (op.first == "-") return(operand1 - operand2);
	else if (op.first == "*") return(operand1 * operand2);
	else if (op.first == "/") return(operand1 / operand2);
	else if (op.first == "%") return(operand1 % operand2);
	else if (op.first == "and") return(operand1 && operand2);
	else if (op.first == "or") return(operand1 || operand2);
	else if (op.first == "==") return(operand1 == operand2);
	else if (op.first == "<") return(operand1 < operand2);
	else if (op.first == "<=") return(operand1 <= operand2);
	else if (op.first == ">=") return(operand1 >= operand2);
	else if (op.first == ">") return(operand1 > operand2);
	else if (op.first == "!=") return(operand1 != operand2);
}
int ExpEvaluator::evaluatePostfix(LexicalAnalyzer::tokenLineType postfixVect) {
	stack<int> tempStack;

	for (LexicalAnalyzer::pairType postfixPair : postfixVect) {
		////number goes in stack
		if (postfixPair.second == categoryType::NUMERIC_LITERAL) { 
				
			tempStack.push(stoi(postfixPair.first));
		}
		else if (postfixPair.second == categoryType::IDENTIFIER) {

			tempStack.push(stoi(retrieveSymbolTable(postfixPair.first)));
		}
		//oporator evaluates the top two strings in the stack
		else if ((postfixPair.second == categoryType::ARITH_OP || postfixPair.second == categoryType::LOGICAL_OP || postfixPair.second == categoryType::RELATIONAL_OP) && postfixPair.first != "not") {
			int operand2;
			operand2 = tempStack.top();
			tempStack.pop();
			int operand1;
			operand1 = tempStack.top();
			tempStack.pop();
			tempStack.push(evaluateOperands(operand1, postfixPair, operand2));
		}
		//Only unary oporator 
		else if (postfixPair.first == "not") {
			int operand = tempStack.top();
			tempStack.pop();
			tempStack.push(!operand);
		}
	}
	return (tempStack.top());
}

//helpful functions
void ExpEvaluator::showVec(LexicalAnalyzer::tokenLineType vecPair) {
	
	for (LexicalAnalyzer::pairType tempPair : vecPair) {
		cout << tempPair.first << " - ";
		if (tempPair.second == categoryType::NUMERIC_LITERAL) {
			cout << "NUMERIC_LITERAL";
		}
		else if (tempPair.second == categoryType::LOGICAL_OP) {
			cout << "LOGICAL_OP";
		}
		else if (tempPair.second == categoryType::IDENTIFIER) {
			cout << "IDENTIFIER";
		}
		else if (tempPair.second == categoryType::KEYWORD) {
			cout << "KEYWORD";
		}
		else if (tempPair.second == categoryType::STRING_LITERAL) {
			cout << "STRING_LITERAL";
		}
		else if (tempPair.second == categoryType::NUMERIC_LITERAL) {
			cout << "NUMERIC_LITERAL";
		}
		else if (tempPair.second == categoryType::ASSIGNMENT_OP) {
			cout << "ASSIGNMENT_OP";
		}
		else if (tempPair.second == categoryType::ARITH_OP) {
			cout << "ARITH_OP";
		}
		else if (tempPair.second == categoryType::RELATIONAL_OP) {
			cout << "RELATIONAL_OP";
		}
		else if (tempPair.second == categoryType::LEFT_PAREN) {
			cout << "LEFT_PAREN";
		}
		else if (tempPair.second == categoryType::RIGHT_PAREN) {
			cout << "RIGHT_PAREN";
		}
		else if (tempPair.second == categoryType::COLON) {
			cout << "COLON";
		}
		else if (tempPair.second == categoryType::COMMA) {
			cout << "COMMA";
		}
		else if (tempPair.second == categoryType::COMMENT) {
			cout << "COMMENT";
		}
		else if (tempPair.second == categoryType::INDENT) {
			cout << "INDENT";
		}
		else if (tempPair.second == categoryType::UNKNOWN) {
			cout << "UNKNOWN";
		}
		else {
			cout << "ERROR - NO TYPE DETECTED";
		}
		cout << endl;
	}
}

bool ExpEvaluator::isExpression(LexicalAnalyzer expLexicalAnalyzer) {
		LexicalAnalyzer::pairType tempPair = expLexicalAnalyzer.tokenInfo[0][0];
		if ((tempPair.second == categoryType::NUMERIC_LITERAL
			|| tempPair.second == categoryType::IDENTIFIER
			|| tempPair.second == categoryType::LEFT_PAREN
			|| tempPair.second == categoryType::RIGHT_PAREN
			|| tempPair.first == "not")) {
			//cout << expLexicalAnalyzer.tokenInfo[0][1].first;
			return true;


		}
		else return false;
	
	//for (LexicalAnalyzer::tokenLineType tempTokenLine : expLexicalAnalyzer.tokenInfo) {
	//	for (LexicalAnalyzer::pairType tempPair : tempTokenLine) {
	//		if ((tempPair.second == categoryType::NUMERIC_LITERAL
	//			|| tempPair.second == categoryType::IDENTIFIER
	//			|| tempPair.second == categoryType::LEFT_PAREN
	//			|| tempPair.second == categoryType::RIGHT_PAREN
	//			|| tempPair.first == "not")) {
	//			return true;
	//		}
	//		else return false;
	//	}
	//}
	//return true;
}