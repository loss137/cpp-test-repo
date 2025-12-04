#include "calculator.h"
#include <cmath>
using namespace std::literals;

void Calculator::Add(Number r) {
    number_ += r;
}

void Calculator::Sub(Number r) {
    number_ -= r;
}

void Calculator::Div(Number r) {
    if (r != 0) {
        number_ /= r;
    } else {
        std::cerr << "Ошибка: деление на ноль!" << std::endl;
    }
}

void Calculator::Mul(Number r) {
    number_ *= r;
}

void Calculator::Pow(Number r) {
    number_ = pow(number_, r);
}

void Calculator::Set(Number n) {
    number_ = n;
}

void Calculator::Save() {
    mem_ = number_;
    has_mem_ = true;
}

void Calculator::Load() {
    if (has_mem_) {
        number_ = mem_;
    }
}

void Calculator::ClearMemory() {
    has_mem_ = false;
}

bool Calculator::GetHasMem() const {
    return has_mem_;
}

Number Calculator::GetNumber() const {
    return number_;
}

std::string Calculator::GetNumberRepr() const {
    return std::to_string(number_);
}
