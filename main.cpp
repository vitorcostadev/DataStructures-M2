#include <iostream>
#include <cctype>
#include "Operations.h"
#include "Stack.h"
#include <vector>
#define PREFIX "/"

using namespace std;

void initMessage()
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

bool parseUserInput(string userInput)
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

bool isValidCommand(string command, vector<string> validCommands)
{
    for(string validCmd : validCommands)
    {
        for(char& ch : command)
        {
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }
        for(char& ch : validCmd)
        {
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }
        if(validCmd == command) return true;
    }
    return false;
}

int getValueFromCommand(string userInput)
{
    size_t spacePos = userInput.find(' ');
    if (spacePos != string::npos)
    {
        string valueStr = userInput.substr(spacePos + 1);
        try
        {
            return stoi(valueStr);
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

string getCommandWithoutValue(string userInput)
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
void printParcelas(Stack<Pass<T>> stack){
    cout << "--> Parcelas da expressão algébrica: " << endl;
    int sz = size(stack);
    for(int i = 1; i <= sz; i++){
        try{
            Pass<T> pass = get(stack, i);
            Operations op = getOperation(pass);
            T val = getValue(pass);
            cout << "Operação: " << op << ", Valor: " << val << endl;
        }catch(const char* msg){
            cout << "Erro ao acessar parcela: " << msg << endl;
            break;
        }
    }
}

int main()
{
    Stack<Pass<int>> stack;
    create(stack);

    Pass<int> pass;
    createPass(pass);

    AlgebricExpression<int> alg;
    createAlgebric(alg);

    string userInput = "";
    bool started = false;

    do
    {
        initMessage();
        cout << endl;
        cout << "--> Digite o comando (PREFIXO " << PREFIX <<"): ";
        getline(cin, userInput);

        if(!parseUserInput(userInput))
        {
            cout << "ERRO! Comando deve começar com " << PREFIX << endl;
            cin.get();
            continue;
        }

        userInput.erase(0, 1);
        string command = getCommandWithoutValue(userInput);

        if(!isValidCommand(command,
    {
        "INICIO", "ZERA", "SOMA", "MULTIPLICA",
        "DIVIDE", "PARCELAS", "IGUAL", "FIM"
    }))
        {
            cout << "ERRO! Comando digitado incorretamente ou não existe." << endl;
            cin.get();
            continue;
        }

        if(command == "fim")
        {
            break;
        }

        if(command == "inicio")
        {
            if(!started)
            {
                cout << "--> Editor de expressão algébrica inicializado!" << endl;
                createAlgebric(alg);
                createPass(pass);
                started = true;
            }else
            {
                cout << "--> Você já inicializou a expressão neste processo." << endl;
            }
            cin.get();
        }

        if(started == true){
            if(command == "soma")
            {
                try
                {
                    setOperation(pass, ADD);
                    setValue(pass, getValueFromCommand(userInput));
                    push(stack, pass);

                    cout << "--> O valor " << getValue(pass) << " foi adicionado à expressão." << endl;
                }
                catch(const char* msg)
                {
                    if(string(msg) == "VALUE_NOT_FOUND")
                    {
                        cout << "ERRO! Valor não encontrado no comando." << endl;
                    }
                    else if(string(msg) == "INVALID_VALUE")
                    {
                        cout << "ERRO! Valor inválido no comando." << endl;
                    }
                }
                cin.get();
            }

            else if(command == "igual")
            {
                while(size(stack) > 0)
                {
                    try
                    {
                        Pass<int> pass = top(stack);
                        alg.pass = pass;
                        calcExpressValue(alg);
                        pop(stack);
                    }
                    catch(const char* msg)
                    {
                        cout << "ERRO na operação: " << msg << endl;
                        break;
                    }
                }
                cout << "--> Resultado da expressão algébrica: " << getExpressionSum(alg) << endl;
                cin.get();
            }

            else if(command == "parcelas")
            {
                printParcelas(stack);
                cin.get();
            }

            else if(command == "zera")
            {
                setExpressionSum(alg, 0);
                destroy(stack);
                cout << "O valor da expressão foi alterado para 0." << endl;
                cin.get();
            }

            else if(command == "divide")
            {
                try
                {
                    setOperation(pass, DIV);
                    setValue(pass, getValueFromCommand(userInput));
                    push(stack, pass);

                    cout << "--> O valor " << getValue(pass) << " foi dividido na expressão." << endl;
                }
                catch(const char* msg)
                {
                    if(string(msg) == "VALUE_NOT_FOUND")
                    {
                        cout << "ERRO! Valor não encontrado no comando." << endl;
                    }
                    else if(string(msg) == "INVALID_VALUE")
                    {
                        cout << "ERRO! Valor inválido no comando." << endl;
                    }
                }
                cin.get();
            }

            else if(command == "multiplica")
            {
                try
                {
                    setOperation(pass, MULT);
                    setValue(pass, getValueFromCommand(userInput));
                    push(stack, pass);

                    cout << "--> O valor " << getValue(pass) << " foi multiplicado na expressão." << endl;
                }
                catch(const char* msg)
                {
                    if(string(msg) == "VALUE_NOT_FOUND")
                    {
                        cout << "ERRO! Valor não encontrado no comando." << endl;
                    }
                    else if(string(msg) == "INVALID_VALUE")
                    {
                        cout << "ERRO! Valor inválido no comando." << endl;
                    }
                }
                cin.get();
            }
        }else
        {
            cout << "Você deve utilizar o comando " << PREFIX << "inicio primeiro!" << endl;
            cin.get();
        }

    }
    while(true);

    destroy(stack);

    return 0;
}
