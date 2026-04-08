#include <iostream>
#include <iomanip>
#include <cstring>
#include "Interface.h"

using namespace std;

int main()
{
    Stack<Pass<float>> stack;
    Stack<float> parcelas;
    create(stack); create(parcelas);

    Pass<float> pass;
    AlgebricExpression<float> alg;

    string userInput = "", action="";
    Operations actuallyOp;
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
        "DIVIDE", "PARCELAS", "IGUAL", "FIM",
        "SUBTRAI"
    }))
        {
            cout << "ERRO! Comando digitado incorretamente ou não existe." << endl;
            cin.get();
            continue;
        }

        bool isMath = true;

        if(started == true && command != "inicio")
        {

            if(command == "soma"){
                actuallyOp = ADD;
                action = "adicionado à";
            } else if(command == "subtrai")
            {
                actuallyOp = SUB;
                action = "subtraído da";
            }else if(command == "multiplica")
            {
                actuallyOp = MULT;
                action = "multiplicado na";
            }else if(command == "divide")
            {
                actuallyOp = DIV;
                action = "dividido na";
            }
            else
            {
                isMath = false;
            }
        }else
        {
            if(command == "inicio")
            {
                isMath = false;
            }else
            {
                cout << "Você deve utilizar o comando " << PREFIX << "inicio antes!" << endl; cin.get(); continue;
            }
        }

        if(isMath)
        {
            try
            {
                float val = getValueFromCommand(userInput);

                if(val == 0 && actuallyOp == DIV){
                    cerr << "--> Você não pode dividir essa expressão por zero." << endl;
                }else{
                    setOperation(pass, actuallyOp);
                    setValue(pass, val);
                    push(stack, pass);

                    cout << "--> O valor " << fixed << setprecision(2) << getValue(pass) << " foi " << action << " expressão!" << endl;
                }
                cin.get();
            }catch(const char *err)
            {
                if(string(err) == "VALUE_NOT_FOUND")
                {
                    cerr << "ERRO! Valor não encontrado no comando." << endl;
                }
                else if(string(err) == "INVALID_VALUE")
                {
                    cerr << "ERRO! Valor inválido no comando." << endl;
                }else
                {
                    cerr << "ERRO! Não foi possivel definir a causa, log: " << err << endl;
                    destroy(stack);
                    exit(-1);
                }
                cin.get();
            }
        }else
        {
            if(command == "igual")
            {
                setExpressionSum(alg, static_cast<float>(0));
                Stack<Pass<float>> temp;
                create(temp);

                while(size(stack) > 0)
                {
                    pass = top(stack);
                    push(temp, pass);
                    pop(stack);
                }

                int cont = 0;
                while(size(temp) > 0)
                {
                    
                    pass = top(temp);
                    setAlgebricPass(alg, pass);
                    calcExpressValue(alg);
                    pop(temp);
                    
                    cont++;
                    if(cont > 1)
                    {
                    push(parcelas, getExpressionSum(alg));
                    }
                }

                Pass<float> basePass;
                setOperation(basePass, ADD);
                setValue(basePass, getExpressionSum(alg));
                push(stack, basePass);

                cout << "--> Resultado parcial: " << fixed << setprecision(2) << getExpressionSum(alg) << endl;
                destroy(temp);
                cin.get();

            }

            else if(command == "parcelas")
            {
                printParcelas(parcelas);
                cin.get();
            }

            else if(command == "zera")
            {
                setExpressionSum(alg, static_cast<float>(0));
                destroy(stack); destroy(parcelas);
                cout << "O valor da expressão foi alterado para 0." << endl;
                cin.get();

            }else if(command == "inicio")
        {
            if(!started)
            {
                cout << "--> Editor de expressão algébrica inicializado!" << endl;
                createAlgebric(alg);
                createPass(pass);
                started = true;
            }
            else
            {
                cout << "--> Você já inicializou a expressão neste processo." << endl;
            }
            cin.get();
        }
            else
            {
                break;
            }
        }
    }while(true);

    destroy(stack);
    destroy(parcelas);
    return 0;
}
