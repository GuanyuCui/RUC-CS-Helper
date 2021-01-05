#ifndef UNARY_FUNCTION_H
#define UNARY_FUNCTION_H

#include <string>

class UnaryFunction
{
    public:
        UnaryFunction(std::string fName, std::string varName, std::string expr);
        ~UnaryFunction();
        std::string & getExpr();
        std::string & getVarName();
        
    private:
        std::string fName;
        std::string varName;
        std::string expr;
};

UnaryFunction::UnaryFunction(std::string _fName, std::string _varName, std::string _expr)
:fName(_fName), varName(_varName), expr(_expr)
{

}

UnaryFunction::~UnaryFunction()
{

}

std::string & UnaryFunction::getVarName()
{
    return this -> varName;
}

std::string & UnaryFunction::getExpr()
{
    return this -> expr;
}

#endif