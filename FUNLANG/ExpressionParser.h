#pragma once
#include <iostream>
#include <vector>
#include <set>

const std::string SYNTAX_ERROR_F = "Syntax error: expected factor, line: pos:";
const std::string SYNTAX_ERROR_MUL = "Syntax error: expected multiplicative operator, line: pos:";
const std::string SYNTAX_ERROR_PLUS = "Syntax error: expected additive operator, line: pos:";
const std::string SYNTAX_ERROR_RELATION = "Syntax error: expected relation operator, line: pos:";
const std::string SYNTAX_ERROR_CONDITION = "Syntax error: expected condition operator, line: pos:";
const std::string SYNTAX_ERROR_CLOSE_BRACKET = "Syntax error: expected close bracket, line: pos:";

//Добавил новое множество и изменил старые - нужно обновить include.h
std::set<std::string> ConditionValues = { "and", "or" };
std::set<std::string> RelationValues = { "=", "<>", ">", "<", ">=", "<=" };
std::set<std::string> PlusValues = { "+", "-" };
std::set<std::string> MulValues = { "*", "/", "div", "mod" };

std::string errorMessage;

bool Error(const std::string& message) {
    errorMessage = message;
    return false;
}

bool RuleF(std::string& input, std::size_t& pos);//распознает a | -a_a | not aa| (a) | 5 | -5 | -5.33
bool RuleFPrime(std::string& input, std::size_t& pos);
bool RuleMul(std::string& input, std::size_t& pos);
bool RuleTermPrime(std::string& input, std::size_t& pos);
bool RuleTerm(std::string& input, std::size_t& pos);
bool RulePlus(std::string& input, std::size_t& pos);
bool RuleSimpleExprPrime(std::string& input, std::size_t& pos);
bool RuleSimpleExpr(std::string& input, std::size_t& pos); //распознает только выражения без сравнений и без and/or/not
bool RuleRelation(std::string& input, std::size_t& pos);
bool RuleExpr1Prime(std::string& input, std::size_t& pos);
bool RuleExpr1(std::string & input, std::size_t& pos);
bool RuleCondition(std::string& input, std::size_t& pos);
bool RuleExpr0Prime(std::string& input, std::size_t& pos);
bool RuleExpr0(std::string& input, std::size_t& pos);
bool RuleExpr(std::string input); //распознает все выражения, в том числе со сравнениями и and/or/not

//идентификатор может содержать только буквы и нижнее подчеркивание
bool ParseIdent(const std::string& input, size_t& pos) {
    //Идентификатор не должен содержать в себе ключевые слова, иначе разбор будет неоднозначный
    std::set<std::string> keywords = { "or", "and", "div", "mod" };
    size_t start = pos;

    while (pos < input.size() && (isalpha(input[pos]) || input[pos] == '_')) {
        pos++;
        for (const auto& keyword : keywords) {
            if (pos - start >= keyword.length() &&
                input.substr(pos - keyword.length(), keyword.length()) == keyword) {
                pos -= keyword.length();
                return true;
            }
        }
    }
    return pos > start;
}

//распознает int и float
bool ParseNumber(const std::string& input, size_t& pos) {
    bool decimalPointEncountered = false;
    size_t start = pos;
    if (isdigit(input[pos])) {
        while (pos < input.size() && (isdigit(input[pos]) || input[pos] == '.')) {
            if (input[pos] == '.') {
                if (decimalPointEncountered) {
                    break;
                }
                decimalPointEncountered = true;
            }
            pos++;
        }
    }
    return pos > start && input[pos - 1] != '.'; 
}

bool RuleExpr(std::string input) {
	input.erase(remove(input.begin(), input.end(), '\n'), input.end());
    std::size_t pos = 0;
    if (RuleExpr0(input, pos) && pos == input.size()) {
        return true;
    }
    if (!errorMessage.empty()) {
        std::cout << errorMessage << std::endl;
        errorMessage.clear();
    }
    return false;
}

// <expr0>:: = <expr> < expr0'>
bool RuleExpr0(std::string& input, std::size_t& pos) {
    //DeleteSpaces(input);

    if (RuleExpr1(input, pos)) {
        return RuleExpr0Prime(input, pos);
    }
    return false;
}

// <expr0'>::= <condition> <expr> <expr0'> | ε
bool RuleExpr0Prime(std::string& input, std::size_t& pos) {
    std::size_t old_pos = pos;
    if (RuleCondition(input, pos) && RuleExpr1(input, pos) && RuleExpr0Prime(input, pos)) {
        return true;
    }
    pos = old_pos;
    return true;
}

// <condition> ::= and | or
bool RuleCondition(std::string& input, std::size_t& pos) {
    //DeleteSpaces(input);

    for (std::size_t length : {3, 2}) {
        std::string token = input.substr(pos, length);
        if (ConditionValues.count(token) && token.length() == length) {
            pos += length;
            return true;
        }
    }
    return Error(SYNTAX_ERROR_RELATION);
}

// <expr1>::= <simple expr> <expr1'>
bool RuleExpr1(std::string & input, std::size_t& pos) {
    //DeleteSpaces(input);

    if (RuleSimpleExpr(input, pos)){
        return RuleExpr1Prime(input, pos);
    }
    return false;
}

// <expr1'>::= <relation> <simple expr> <expr1'> | ε
bool RuleExpr1Prime(std::string& input, std::size_t& pos) {
    std::size_t old_pos = pos;
    if (RuleRelation(input, pos) && RuleSimpleExpr(input, pos) && RuleExpr1Prime(input, pos)) {
        return true;
    }
    pos = old_pos;
    return true;
}

// <relation>::= = | <> | > | < | >= | <=
bool RuleRelation(std::string& input, std::size_t& pos) {
    //DeleteSpaces(input);

    for (std::size_t length : {2, 1}) {
        std::string token = input.substr(pos, length);
        if (RelationValues.count(token) && token.length() == length) {
            pos += length;
            return true;
        }
    }
    return Error(SYNTAX_ERROR_RELATION);
}

// <simple expr>::= <term> <simple expr'>
bool RuleSimpleExpr(std::string& input, std::size_t& pos) {
    //DeleteSpaces(input);

    if (RuleTerm(input, pos)) {
        return RuleSimpleExprPrime(input, pos);
    }
    return false;
}

// <simple expr'>::= <plus> <term> <simple expr'> | ε
bool RuleSimpleExprPrime(std::string& input, std::size_t& pos) {
    std::size_t old_pos = pos;
    if (RulePlus(input, pos) && RuleTerm(input, pos) && RuleSimpleExprPrime(input, pos)) {
        return true;
    }
    pos = old_pos;
    return true;
}

// <plus>::= + | -
bool RulePlus(std::string& input, std::size_t& pos) {
    //DeleteSpaces(input);

    std::size_t length = 1;
    std::string token = input.substr(pos, length);
    if (PlusValues.count(token) && token.length() == length) {
        pos += length;
        return true;
    }
    return Error(SYNTAX_ERROR_PLUS);
}

// <term>::= <f> <term'>
bool RuleTerm(std::string& input, std::size_t& pos) {
    //DeleteSpaces(input);

    if (RuleF(input, pos)) {
        return RuleTermPrime(input, pos);
    }
    return false;
}

// <term'>::= <mul> <f> <term'> | ε
bool RuleTermPrime(std::string& input, std::size_t& pos) {
    std::size_t old_pos = pos;
    if (RuleMul(input, pos) && RuleF(input, pos) && RuleTermPrime(input, pos)) {
        return true;
    }
    pos = old_pos;
    return true;
}

// <mul>::= * | / | div | mod
bool RuleMul(std::string& input, std::size_t& pos) {
    //DeleteSpaces(input);

    for (std::size_t length : {3, 1}) {
        std::string token = input.substr(pos, length);
        if (MulValues.count(token) && token.length() == length) {
            pos += length;
            return true;
        }
    }
    return Error(SYNTAX_ERROR_MUL);
}

// <f>::= -<f'> | not <f'> | <f'>
bool RuleF(std::string& input, std::size_t& pos) {
    //DeleteSpaces(input);

    for (std::size_t length : {3, 1}) {
        std::string token = input.substr(pos, length);
        if ((token == "not" && length == 3) || (token == "-" && length == 1)) {
            pos += length;
            return RuleFPrime(input, pos);
        }
    }
    return RuleFPrime(input, pos);
}

// <f'> ::= <ident> | <numb> | (<expr0>)
bool RuleFPrime(std::string& input, std::size_t& pos) {
    if (ParseIdent(input, pos)) {
        return true;
    }
    if (ParseNumber(input, pos)) {
        return true;
    }
    std::string token = input.substr(pos, 1);
    if (token == "(") {
        pos += 1;
        if (RuleExpr0(input, pos)) {
            token = input.substr(pos, 1);
            if (token == ")") {
                pos += 1;
                return true;
            }
            return Error(SYNTAX_ERROR_CLOSE_BRACKET);
        }
        return Error(SYNTAX_ERROR_F);
    }
    return Error(SYNTAX_ERROR_F);
}
