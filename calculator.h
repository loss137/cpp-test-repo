#pragma once

#include <iostream>
#include <string>

using Number = double;

class Calculator {
public:
    Calculator(Number init = 0) : number_(init) {
    }
    void Add(Number r); //суммв
    void Sub(Number r); //разность
    void Div(Number r); //деление
    void Mul(Number r); //умножение
    void Pow(Number r); //степень

    void Set(Number n); //устанавливает текущее значение
    void Negate(Number n); // изменяет знак текущего значения калькулятора на противоположный

    void Save(); //сохраняет текущее значение калькулятора
    void Load(); //загружает сохраненное значение

    void ClearMemory(); //очистка памяти

    bool GetHasMem() const; //сохранено ли число в памяти

    Number GetNumber() const; //возврат текущего значения

    std::string GetNumberRepr() const; //возврат текущего значения string

private:
    bool has_mem_ = false;
    Number number_;
    Number mem_;
};
