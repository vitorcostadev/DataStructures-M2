#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <iostream>
#include <cstring>
#include <vector>
#include <cctype>
#include <iomanip>
#include "Operations.h"
#include "Stack.h"
#include <algorithm>

#define PREFIX "/"

using namespace std;

inline void initMessage()
{
    cout << "\033[2J\033[1;1H";
    cout << "----- > EDITOR DE EXPRESSÃO ALGÉBRICA < -----" << endl;
    cout << "["<<PREFIX<<"INICIO]  :  {INICIALIZA O PROGRAMA}" << endl;
    cout << "["<<PREFIX<<"ZERA]  :  {(RE)INICIZALIZA A EXPRESSÃO ARITIMÉTICA}" << endl;
    cout << "["<<PREFIX<<"SOMA (value)]  :  {SOMA value COM O VALOR DA EXPRESSÃO ARITIMÉTICA}" << endl;
    cout << "["<<PREFIX<<"SUBTRAI (value)] : {SUBTRAI value COM O VALOR DA EXPRESSÃO ARITIMETICA}" << endl;
    cout << "["<<PREFIX<<"MULTIPLICA (value)]  :  {MULTIPLICA O value COM O VALOR DA EXPRESSÃO ARITIMÉTICA}" << endl;
    cout << "["<<PREFIX<<"DIVIDE (value)]  :  {DIVIDE O value COM O VALOR DA EXPRESSÃO ARITIMÉTICA}" << endl;
    cout << "["<<PREFIX<<"PARCELAS]  :  {EXIBE OS VALORES DE CADA PARCELA DA EXPRESSÃO}" << endl;
    cout << "["<<PREFIX<<"IGUAL]  :  {EXIBE O RESULTADO DA AVALIAÇÃO DA EXPRESSÃO ARITIMÉTICA}" << endl;
    cout << "["<<PREFIX<<"FIM]  :  {FINALIZA O PROGRAMA}" << endl;
    cout << "----- > EDITOR DE EXPRESSÃO ALGÉBRICA < -----" << endl;
}

inline bool parseUserInput(string &userInput)
{
    transform(userInput.begin(), userInput.end(), userInput.begin(),
              [](unsigned char c){ return tolower(c); });

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
        transform(validCmd.begin(), validCmd.end(), validCmd.begin(),
                  [](unsigned char c){ return tolower(c); });

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
        catch (const invalid_argument &e)
        {
            throw "INVALID_VALUE";
        }
        catch (const out_of_range &e)
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

inline void printParcelas(Stack<float> parcelas)
{
    int sz = size(parcelas);

    if (sz == 0)
    {
        cout << "--> Nenhuma parcela foi calculada ainda." << endl;
        return;
    }

    cout << "--> Parcelas da expressão algébrica: ";

    for(int i = sz; i >= 1; i--)
    {
        float v = get(parcelas, i);

        cout << fixed << setprecision(2) << v;

        if (i > 2) {
            cout << ", ";
        } else if (i == 2) {
            cout << " e ";
        }
    }
    cout << endl;
}

#endif
