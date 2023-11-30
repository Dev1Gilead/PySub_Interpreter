#include "interpreter.h"
#include "expEvaluator.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
int x = 0;
bool nextLine = false;
LexicalAnalyzer lexAn;
LexicalAnalyzer ifsLexAn;
bool runElif = false;


LexicalAnalyzer Interpreter::loopWhile(LexicalAnalyzer lexAnalysis, ExpEvaluator &expEval, LexicalAnalyzer::tokenLineType TokenLine_maybe, int & indexTokenInfo) {
	
	LexicalAnalyzer::tokenLineType tokenLine;
	LexicalAnalyzer::tokenLineType returnTokenLine;
	LexicalAnalyzer returnLex;
	indexTokenInfo += 1;
	tokenLine = lexAnalysis.tokenInfo[indexTokenInfo];

	while (tokenLine[0].second == categoryType::INDENT) { 
			returnTokenLine.clear();
		//getting rid of the indent
		for (int tInt = 1; tInt < tokenLine.size(); tInt++) {
			returnTokenLine.push_back(tokenLine[tInt]);
		}
		returnLex.tokenInfo.push_back(returnTokenLine);
		
			indexTokenInfo++;
		if (indexTokenInfo >= lexAnalysis.tokenInfo.size()) {
			break;
		}
		else if (lexAnalysis.tokenInfo[indexTokenInfo].empty()) {
			break;
		}
		else if (lexAnalysis.tokenInfo[indexTokenInfo][0].second != categoryType::INDENT) {
			break;
		}
		tokenLine = lexAnalysis.tokenInfo[indexTokenInfo];

	}
	indexTokenInfo--;
	return returnLex;				
	
}

void Interpreter::lineType(LexicalAnalyzer lexAnalysis, ExpEvaluator &expEval) {
	LexicalAnalyzer::tokenLineType universalTokenLine;
	//LexicalAnalyzer::tokenLineType elifuniversalTokenLine;

	for (int indexTokenInfo = 0; indexTokenInfo < lexAnalysis.tokenInfo.size(); ++indexTokenInfo) {
		LexicalAnalyzer::tokenLineType TokenLine = lexAnalysis.tokenInfo[indexTokenInfo];

		//cout << indexTokenInfo;
		//traverse by line
		for (LexicalAnalyzer::pairType tempPair : TokenLine) {
			lexAn.tokenInfo.push_back(TokenLine);
			int i = 0;
			//ckeck index bounds
			if (i > TokenLine.size()) {
				cout << "Error out of bounds";
				break;
			}

			//check if comment
			if (tempPair.second == categoryType::COMMENT) {
				//do nothing
			}
			//check if keyword
			else if (tempPair.second == categoryType::KEYWORD) {

				if (tempPair.first == "print") {
					if (TokenLine[i + 1].second == categoryType::LEFT_PAREN) {\
						//all good
					}
					else {
						cout << "Error: no left pren on print statment";
						break;
					}
					bool isCreatingLexi = true;
				
					i += 2; // go past left pren
					lexAn.clear();

					LexicalAnalyzer::tokenLineType tempTokenLine;
					LexicalAnalyzer::pairType veryTempPair;
					int j = i;
					while (isCreatingLexi) {
						if (j > TokenLine.size()) {
							cout << "error, out of bounds in print";
							break;
						}
						if (TokenLine[j].second == categoryType::STRING_LITERAL) {
							string modifiedStringB = TokenLine[j].first.substr(1, TokenLine[j].first.length() - 2);
							cout << modifiedStringB << " ";
							lexAn.clear();
							j++;
						}

						bool run = false;
						while (TokenLine[j].second != categoryType::COMMA && TokenLine[j].second != categoryType::RIGHT_PAREN) {
							veryTempPair = TokenLine[j];
							tempTokenLine.push_back(veryTempPair);
							j++;
							run = true;
						}

						if (TokenLine[j].second == categoryType::RIGHT_PAREN) {
							isCreatingLexi = false;
						}
			
						if (run) {
							lexAn.tokenInfo.push_back(tempTokenLine);
							if (expEval.isExpression(lexAn)) {
								int result = expEval.evaluatePostfix(expEval.convertToPostfix(lexAn));
								string tempString = to_string(result);
								expEval.storeSymbolTable(tempPair.first, tempString);

								cout << result << " ";
								lexAn.clear();
							}
						}
						else {
							j++;
						}

					
					}
					cout << endl;
				}
				else if (tempPair.first == "if") {
					int tempInt = i + 1;



					lexAn.clear();
					LexicalAnalyzer::tokenLineType tempTokenLine;
					LexicalAnalyzer::pairType veryTempPair;

					if (TokenLine[TokenLine.size() - 1].second == categoryType::COLON) {
						while (tempInt < TokenLine.size() - 1) {
							veryTempPair = TokenLine[tempInt];
							tempTokenLine.push_back(veryTempPair);
							tempInt++;
						}
						universalTokenLine = tempTokenLine;

					}
					lexAn.tokenInfo.push_back(universalTokenLine);




					LexicalAnalyzer tempLex = loopWhile(lexAnalysis, expEval, TokenLine, indexTokenInfo);


					if (expEval.isExpression(lexAn) && expEval.evaluatePostfix(expEval.convertToPostfix(lexAn)) != 0) {

						lineType(tempLex, expEval);
						lexAn.tokenInfo.push_back(universalTokenLine);

						runElif = false;
					}
					else {
						runElif = true;
					}
					
				}
				else if (tempPair.first == "elif") {
					
					int tempInt = i + 1;



					lexAn.clear();
					LexicalAnalyzer::tokenLineType tempTokenLine;
					LexicalAnalyzer::pairType veryTempPair;

					if (TokenLine[TokenLine.size() - 1].second == categoryType::COLON) {
						while (tempInt < TokenLine.size() - 1) {
							veryTempPair = TokenLine[tempInt];
							tempTokenLine.push_back(veryTempPair);
							tempInt++;
						}
						universalTokenLine = tempTokenLine;

					}
					lexAn.tokenInfo.push_back(universalTokenLine);



					LexicalAnalyzer tempLex = loopWhile(lexAnalysis, expEval, TokenLine, indexTokenInfo);

					if (runElif){
						if (expEval.isExpression(lexAn) && expEval.evaluatePostfix(expEval.convertToPostfix(lexAn)) != 0) {

							lineType(tempLex, expEval);
							lexAn.tokenInfo.push_back(universalTokenLine);

							runElif = false;
						}
					}
				}

				else if (tempPair.first == "else"){
					int tempInt = i + 1;



					lexAn.clear();



					LexicalAnalyzer tempLex = loopWhile(lexAnalysis, expEval, TokenLine, indexTokenInfo);

					if (runElif) {
						if (true) {

							lineType(tempLex, expEval);

							runElif = false;
						}
					}
				}

				else if (tempPair.first == "while") {
					int tempInt = i+1;

				
				
					lexAn.clear();
					LexicalAnalyzer::tokenLineType tempTokenLine;
					LexicalAnalyzer::pairType veryTempPair;

					if (TokenLine[TokenLine.size()-1].second == categoryType::COLON){
						while (tempInt < TokenLine.size()-1) {
							veryTempPair = TokenLine[tempInt];
							tempTokenLine.push_back(veryTempPair);
							tempInt++;
						}
						universalTokenLine = tempTokenLine;

					}
					lexAn.tokenInfo.push_back(universalTokenLine);
					

					
					
					LexicalAnalyzer tempLex = loopWhile(lexAnalysis, expEval, TokenLine, indexTokenInfo);


					if (expEval.isExpression(lexAn)) {
						while (expEval.evaluatePostfix(expEval.convertToPostfix(lexAn)) != 0) {
	
							lineType(tempLex, expEval);
							lexAn.tokenInfo.push_back(universalTokenLine);

						}
					}
				}
				nextLine = true;
			}
			 //check if assinging an identifier
			else if (tempPair.second == categoryType::IDENTIFIER && TokenLine[i + 1].second == categoryType::ASSIGNMENT_OP) {
				if (i+2 < TokenLine.size() && TokenLine[i + 2].first == "int" && TokenLine[i + 4].first == "input") {
					

					string modifiedString = TokenLine[i + 6].first.substr(1, TokenLine[i + 6].first.length() - 2);
					cout << modifiedString << std::endl;
					string inputInput;
					cin >> inputInput;
					expEval.storeSymbolTable(tempPair.first, inputInput);

					nextLine = true;
				}
				else if (true) {
					lexAn.clear();
					//cout << "Assinging oporator!!!\n";
					
					LexicalAnalyzer::tokenLineType tempTokenLine;
					LexicalAnalyzer::pairType veryTempPair;

					int j = i;
					j = j + 2;//go past the =
					while (j < TokenLine.size()) {
						veryTempPair = TokenLine[j];
						tempTokenLine.push_back(veryTempPair);
						j++;
					}
					lexAn.tokenInfo.push_back(tempTokenLine);
					int result = expEval.evaluatePostfix(expEval.convertToPostfix(lexAn));

					string tempString = to_string(result);

					expEval.storeSymbolTable(tempPair.first, tempString);
					//cout << expEval.retrieveSymbolTable(tempPair.first) << endl;
					nextLine = true;
					lexAn.clear();
				}
			}
			else if (expEval.isExpression(lexAn)) {
				//cout << "Expresssion\n";

				int expressionResult = expEval.evaluatePostfix(expEval.convertToPostfix(lexAn));
				//cout << expressionResult << endl;
				nextLine = true;
				lexAn.clear();
			}
			else {
				cout << i << "non of the above worked\n";
				nextLine = true;

			}
			i++;
			lexAn.clear();
			if (nextLine) {
				lexAn.clear();
				nextLine = false;
				break;
			}

		}
	}
	
}