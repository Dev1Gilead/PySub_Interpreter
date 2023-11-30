#ifndef LEXANALYZER_H
#define LEXANALYZER_H
#include <vector>
#include <string>
using namespace std;

enum class categoryType
{
    KEYWORD,
    IDENTIFIER,
    STRING_LITERAL,
    NUMERIC_LITERAL,
    ASSIGNMENT_OP,
    ARITH_OP,
    LOGICAL_OP,
    RELATIONAL_OP,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COMMA,
    COMMENT,
    INDENT,
    UNKNOWN
};


class  LexicalAnalyzer
{
private:
    int test;
    typedef vector<vector<pair<string, categoryType>>> tokenType;
    typedef vector<pair<string, categoryType>> tokenLineType;
    typedef pair<string, categoryType> pairType;
    tokenType tokenInfo;
public:
    void generateTokens(vector<string>);
    void show();
    void clear();
    //type check classes
    bool isUnderScore(string programLine, int index);
    bool isKeyWord(string tokenValue);
    bool logicalOp(string tokenValue);
    bool isQuotaion(char c);
    bool isLeftParenthesis(char c);
    bool isRightParenthesis(char c);
    bool isColon(char c);
    bool isComma(char c);
    bool isComment(char c);
    bool isWhitespace(char c);
    bool isOperator(char c);
    bool isAssignmentOP(char c);
    bool isRelationalOP(string tokenValue);
    bool isArithOP(char c);
    friend class ExpEvaluator;
    friend class Interpreter;
    
};

#endif // !LEXANALYZER_H
