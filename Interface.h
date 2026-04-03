#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "Operations.h"
#include "Stack.h"

#define PREFIX "/"

using namespace std;

inline void initMessage()
{
    cout << "\033[2J\033[1;1H";
    cout << "----- > EDITOR DE EXPRESSÃO ALGÉBRICA < -----" << endl;
    cout << "["<<PREFIX<<"INICIO]  :  {INICIALIZA O PROGRAMA}" << endl;
    cout << "["<<PREFIX<<"ZERA]  :  {(RE)INICIZALIZA A EXPRESSÃO ARITIMÉTICA}" << endl;
    cout << "["<<PREFIX<<"SOMA (value)]  :  {SOMA value COM O VALOR DA EXPRESSÃO ARITIMÉTICA}" << endl;
    cout << "["<<PREFIX<<"MULTIPLICA (value)]  :  {MULTIPLICA O value COM O VALOR DA EXPRESSÃO ARITIMÉTICA}" << endl;
    cout << "["<<PREFIX<<"DIVIDE (value)]  :  {DIVIDE O value COM O VALOR DA EXPRESSÃO ARITIMÉTICA}" << endl;
    cout << "["<<PREFIX<<"PARCELAS]  :  {EXIBE OS VALORES DE CADA PARCELA DA EXPRESSÃO}" << endl;
    cout << "["<<PREFIX<<"IGUAL]  :  {EXIBE O RESULTADO DA AVALIAÇÃO DA EXPRESSÃO ARITIMÉTICA}" << endl;
    cout << "["<<PREFIX<<"FIM]  :  {FINALIZA O PROGRAMA}" << endl;
    cout << "----- > EDITOR DE EXPRESSÃO ALGÉBRICA < -----" << endl;
}

inline bool parseUserInput(string &userInput)
{
    for (char& c : userInput)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    if(userInput.empty() || userInput[0] != PREFIX[0])
    {
        return false;
    }

    return true;
}

inline bool isValidCommand(string command, vector<string> validCommands)
{
    for(string validCmd : validCommands)
    {
        for(char& ch : validCmd)
        {
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }
        if(validCmd == command) return true;
    }
    return false;
}

inline float getValueFromCommand(string userInput)
{
    size_t spacePos = userInput.find(' ');
    if (spacePos != string::npos)
    {
        string valueStr = userInput.substr(spacePos + 1);
        try
        {
            return stof(valueStr);
        }
        catch (const invalid_argument& e)
        {
            throw "INVALID_VALUE";
        }
    }
    else
    {
        throw "VALUE_NOT_FOUND";
    }
}

inline string getCommandWithoutValue(string userInput)
{
    size_t spacePos = userInput.find(' ');
    if (spacePos != string::npos)
    {
        return userInput.substr(0, spacePos);
    }
    else
    {
        return userInput;
    }
}

template<typename T>
void printParcelas(Stack<Pass<T>> stack)
{
    std::cout << "--> Parcelas da expressão algébrica: " << endl;
    int sz = size(stack);
    for(int i = 1; i <= sz; i++)
    {
        try
        {
            Pass<T> pass = get(stack, i);
            Operations op = getOperation(pass);
            T val = getValue(pass);
            std::cout << "Operação: " << op << ", Valor: " << val << endl;
        }
        catch(const char* msg)
        {
            std::cout << "Erro ao acessar parcela: " << msg << endl;
            break;
        }
    }
}

#endif
