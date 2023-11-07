#include "lexanalyzer.h"
#include "interface.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <cctype>
using namespace std;

// fucions that check what the value type is
bool LexicalAnalyzer::isUnderScore(string programLine, int index) {
	string tempString = { "_", };
	int j = 0;
	if (programLine[index] == tempString[j]) {
		return true;
	}
	else return false;
}
bool LexicalAnalyzer::isKeyWord(string tokenValue) {
	vector<string> vecString = { "while","print","if","else","elif","int","input"};

	for (const auto& str : vecString) {
		if (str == tokenValue) {
			return true;
		}
	}
	return false;
}
bool LexicalAnalyzer::logicalOp(string tokenValue) {
	vector<string> vecString = { "and","or","not"};

	for (const auto& str : vecString) {
		if (str == tokenValue) {
			return true;
		}
	}
	return false;
}
bool LexicalAnalyzer::isQuotaion(char c) {
	vector<string> vecString = { "\'","\"" };
	string tempCstring = "";
	tempCstring += c;
	for (const auto& str : vecString) {
		if (tempCstring == str) {
			return true; }
	}
	return false;
}
bool LexicalAnalyzer::isLeftParenthesis(char c) {
	vector<string> vecString = { "(" };
	string tempCstring = "";
	tempCstring += c;
	for (const auto& str : vecString) {
		if (tempCstring == str) {
			return true;
		}
	}
	return false;
}
bool LexicalAnalyzer::isRightParenthesis(char c) {
	vector<string> vecString = { ")" };
	string tempCstring = "";
	tempCstring += c;
	for (const auto& str : vecString) {
		if (tempCstring == str) {
			return true;
		}
	}
	return false;
}
bool LexicalAnalyzer::isColon(char c) {
	vector<string> vecString = { ":" };
	string tempCstring = "";
	tempCstring += c;
	for (const auto& str : vecString) {
		if (tempCstring == str) {
			return true;
		}
	}
	return false;
}
bool LexicalAnalyzer::isComma(char c) {
	vector<string> vecString = { "," };
	string tempCstring = "";
	tempCstring += c;
	for (const auto& str : vecString) {
		if (tempCstring == str) {
			return true;
		}
	}
	return false;
}
bool LexicalAnalyzer::isComment(char c) {
	vector<string> vecString = { "#" };
	string tempCstring = "";
	tempCstring += c;
	for (const auto& str : vecString) {
		if (tempCstring == str) {
			return true;
		}
	}
	return false;
}
bool LexicalAnalyzer::isWhitespace(char c) {
	vector<string> vecString = { " ","\t"};
	string tempCstring = "";
	tempCstring += c;
	for (const auto& str : vecString) {
		if (tempCstring == str) {
			return true;
		}
	}
	return false;
}
bool LexicalAnalyzer::isOperator(char c) {
	vector<string> vecString = { "+","-","*","/","%","!","<",">","="};
	string tempCstring = "";
	tempCstring += c;
	for (const auto& str : vecString) {
		if (tempCstring == str) {
			return true;
		}
	}
	return false;
}
bool LexicalAnalyzer::isAssignmentOP(char c) {
	vector<string> vecString = {"="};
	string tempCstring = "";
	tempCstring += c;
	for (const auto& str : vecString) {
		if (tempCstring == str) {
			return true;
		}
	}
	return false;
}
bool LexicalAnalyzer::isRelationalOP(string tokenValue) {
	vector<string> vecString = { "<",">","<=",">=","==","!="};

	for (const auto& str : vecString) {
		if (str == tokenValue) {
			return true;
		}
	}
	return false;
}
bool LexicalAnalyzer::isArithOP(char c) {
	vector<string> vecString = { "+","-","*","/","%"};
	string tempCstring = "";
	tempCstring += c;
	for (const auto& str : vecString) {
		if (tempCstring == str) {
			return true;
		}
	}
	return false;
}

//primary function in LexicalAnalyzer
void LexicalAnalyzer::generateTokens(vector<string> programCode) {
	//traverses line by line
	for (auto programLine : programCode) {
		tokenLineType tokenLine;
		//traverses char by char throught the line of code
		for (int i = 0; i < programLine.size(); i++) {
			//temp variables
			string tokenValue = "";
			categoryType tokenCategory;
			char c = programLine[i];

			//checking variable types
			if (isdigit(c)) {
				//coloct all digits
				while (isdigit(programLine[i + 1])) {
					tokenValue += programLine[i];
					i++;
				}
				tokenValue += programLine[i];

				//push data
				tokenCategory = categoryType::NUMERIC_LITERAL;
				pairType tokenPair = make_pair(tokenValue, tokenCategory);
				tokenLine.push_back(tokenPair);
			}
			else if (isalpha(c)) {
				tokenValue += c;
				while (isalpha(programLine[i+1]) || isUnderScore(programLine, i+1) || isdigit(programLine[i + 1])) {
					tokenValue += programLine[i+1];
					i++;
				}
				if (isKeyWord(tokenValue)) {
					//push data
					tokenCategory = categoryType::KEYWORD;
					pairType tokenPair = make_pair(tokenValue, tokenCategory);
					tokenLine.push_back(tokenPair);
				}
				else if (logicalOp(tokenValue)) {
					//push data
					tokenCategory = categoryType::LOGICAL_OP;
					pairType tokenPair = make_pair(tokenValue, tokenCategory);
					tokenLine.push_back(tokenPair);
				}
				else {
					//push data
					tokenCategory = categoryType::IDENTIFIER;
					pairType tokenPair = make_pair(tokenValue, tokenCategory);
					tokenLine.push_back(tokenPair);
				}
			}
			else if (isQuotaion(c)) {

				tokenValue += c;
				i++;
				while (programLine[i] != c) {
					tokenValue += programLine[i];
					i++;
				}
				tokenValue += c;
				//push data
				tokenCategory = categoryType::STRING_LITERAL;
				pairType tokenPair = make_pair(tokenValue, tokenCategory);
				tokenLine.push_back(tokenPair);

			}
			else if (isLeftParenthesis(c) || isRightParenthesis(c) || isColon(c) || isComma(c)) {
				tokenValue += c;
				if (isLeftParenthesis(c)) {
					//push data
					tokenCategory = categoryType::LEFT_PAREN;
					pairType tokenPair = make_pair(tokenValue, tokenCategory);
					tokenLine.push_back(tokenPair);
				}
				else if (isRightParenthesis(c)) {
					//push data
					tokenCategory = categoryType::RIGHT_PAREN;
					pairType tokenPair = make_pair(tokenValue, tokenCategory);
					tokenLine.push_back(tokenPair);
				}
				else if (isColon(c)) {
					//push data
					tokenCategory = categoryType::COLON;
					pairType tokenPair = make_pair(tokenValue, tokenCategory);
					tokenLine.push_back(tokenPair);
				}
				else if (isComma(c)) {
					//push data
					tokenCategory = categoryType::COMMA;
					pairType tokenPair = make_pair(tokenValue, tokenCategory);
					tokenLine.push_back(tokenPair);
				}
			}		
			else if (isComment(c)) {
				while (i < programLine.size() ) {
					tokenValue += programLine[i];
					i++;
				}
				//push data
				tokenCategory = categoryType::COMMENT;
				pairType tokenPair = make_pair(tokenValue, tokenCategory);
				tokenLine.push_back(tokenPair);
			}
			else if (isWhitespace(c)) {
				if (i == 0) {
					while (isWhitespace(programLine[i+1])) {
						tokenValue += programLine[i];
						i++;
					}
					//push data
					tokenCategory = categoryType::INDENT;
					pairType tokenPair = make_pair(tokenValue, tokenCategory);
					tokenLine.push_back(tokenPair);
				}
			}
			else if (isOperator(c)) {
				tokenValue += c;
				//check if next value is an oporator
				if (isOperator(programLine[i + 1])) {
					tokenValue += programLine[i + 1];
					i++;
				}
				//checks what type of opporator to assign it to
				if (isRelationalOP(tokenValue)) {
					//push dataread
					tokenCategory = categoryType::RELATIONAL_OP;
					pairType tokenPair = make_pair(tokenValue, tokenCategory);
					tokenLine.push_back(tokenPair);

				}
				else if (isArithOP(c)) {
					//push data
					tokenCategory = categoryType::ARITH_OP;
					pairType tokenPair = make_pair(tokenValue, tokenCategory);
					tokenLine.push_back(tokenPair);
				}
				else if (isAssignmentOP(c)) {
					//push data
					tokenCategory = categoryType::ASSIGNMENT_OP;
					pairType tokenPair = make_pair(tokenValue, tokenCategory);
					tokenLine.push_back(tokenPair);
				}

			}
			// UNKNOWN
			else {
				tokenValue += c;
				tokenCategory = categoryType::UNKNOWN;
				//push data
				pairType tokenPair = make_pair(tokenValue, tokenCategory);
				tokenLine.push_back(tokenPair);
			}


		}
		//puts the line of now identified data types into tokenInfo
		tokenInfo.push_back(tokenLine);
	}
}

//prints the tokenInfo data to the screen
void LexicalAnalyzer::show() {
	int lineNum = 0;
	for (tokenLineType tempTokenLine: tokenInfo) {
		int i = 0;
		cout << "Line #" << lineNum << endl;
		for (pairType tempPair: tempTokenLine) {
			cout << "token[" << i << "]:  " << tempPair.first << " - ";
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
			i++;
		}
		cout << "------------------------------------------" << endl;
		i++;
		lineNum++;
	}
	
}
void LexicalAnalyzer::clear() {
	tokenInfo.clear();
}