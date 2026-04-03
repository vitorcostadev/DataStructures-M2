#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

enum Operations{
    ADD, // Adição
    SUB, // Subtração
    MULT, // Multiplicação
    DIV, // Divisão
    PARCELAS,
    ZERA,
    FIM
};

template<typename T>
struct Pass
{
    Operations operation;
    T value;
};

template<typename T>
struct AlgebricExpression
{
    Pass<T> pass;
    T expressionSum;
};

template<typename T>
void createAlgebric(AlgebricExpression<T> &alg)
{
    alg.expressionSum = 0;
}

template<typename T>
void createPass(Pass<T> &pass)
{
    pass.operation = ZERA;
    pass.value = 0;
}

template<typename T>
Operations getOperation(Pass<T> pass) { return pass.operation; }

template<typename T>
T getValue(Pass<T> pass) { return pass.value; }

template<typename T>
void setOperation(Pass<T> &pass, Operations operation) { pass.operation = operation; }

template<typename T>
void setValue(Pass<T> &pass, T val) { pass.value = val; }

template<typename T>
T getExpressionSum(AlgebricExpression<T> alg) { return alg.expressionSum; }

template<typename T>
void setExpressionSum(AlgebricExpression<T> &alg, T value) { alg.expressionSum = value; }

template<typename T>
void setAlgebricPass(AlgebricExpression<T> &alg, Pass<T> pass) { alg.pass = pass; }

template<typename T>
void addToExpressionSum(AlgebricExpression<T> &alg, T val){ alg.expressionSum += val; }

template<typename T>
void subtractFromExpressionSum(AlgebricExpression<T> &alg, T val){ alg.expressionSum -= val; }


template<typename T>
void multiplyExpressionSum(AlgebricExpression<T> &alg, T val){ alg.expressionSum *= val; }


template<typename T>
void divideExpressionSum(AlgebricExpression<T> &alg, T val){
    if(val != 0){
        alg.expressionSum /= val;
    }else
    {
        throw "DIVISION_BY_ZERO";
    }
}

template<typename T>
void calcExpressValue(AlgebricExpression<T> &algebric){
    Operations op = getOperation(algebric.pass);
    T val = getValue(algebric.pass);

    switch(op){
        case ADD:
            addToExpressionSum(algebric, val);
            break;
        case SUB:
            subtractFromExpressionSum(algebric, val);
            break;
        case MULT:
            multiplyExpressionSum(algebric, val);
            break;
        case DIV:
            divideExpressionSum(algebric, val);
            break;
        case ZERA:
            setExpressionSum(algebric, static_cast<T>(0));
            break;
        default:
            break;
    }
}

#endif
