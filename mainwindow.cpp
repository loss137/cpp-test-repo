#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
}

MainWindow::~MainWindow() {
    delete ui;
    SetText("0");
}

void MainWindow::SetText(const QString &text)
{
    input_number_ = RemoveTrailingZeroes(text);
    input_number_ = NormalizeNumber(input_number_);
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::AddText(const QString &suffix)
{
    input_number_ += suffix;
    SetText(input_number_);
}

QString MainWindow::RemoveTrailingZeroes(const QString &text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString MainWindow::NormalizeNumber(const QString &text) {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        // Рекурсивный вызов.
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        // Рекурсивный вызов.
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

void MainWindow::SetOperation(Operation op)
{
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
        ui->l_formula->setText(QString("%1 %2").arg(calculator_.GetNumber())
                                      .arg(OpToString(op)));
        input_number_ = "";
    } else {
        ui->l_formula->setText(QString("%1 %2 %3 = ").arg(calculator_.GetNumber())
                                            .arg(OpToString(op))
                                            .arg(active_number_));
    }
    switch (current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(active_number_);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(active_number_);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(active_number_);
        break;
    case Operation::DIVISION:
        calculator_.Div(active_number_);
        break;
    case Operation::POWER:
        calculator_.Pow(active_number_);
        break;
    default:
        break;
    }
    current_operation_ = op;
}

QString MainWindow::OpToString(Operation op) {
    switch(op) {
    case Operation::NO_OPERATION: return "";
    case Operation::ADDITION: return "+";
    case Operation::DIVISION: return "÷";
    case Operation::MULTIPLICATION: return "×";
    case Operation::SUBTRACTION: return "−";
    case Operation::POWER: return "^";
    }
}

void MainWindow::on_tb_zero_clicked()
{
    AddText("0");
}


void MainWindow::on_tb_one_clicked()
{
    AddText("1");
}


void MainWindow::on_tb_two_clicked()
{
    AddText("2");
}


void MainWindow::on_tb_three_clicked()
{
    AddText("3");
}


void MainWindow::on_tb_four_clicked()
{
    AddText("4");
}


void MainWindow::on_tb_five_clicked()
{
    AddText("5");
}


void MainWindow::on_tb_six_clicked()
{
    AddText("6");
}


void MainWindow::on_tb_seven_clicked()
{
    AddText("7");
}


void MainWindow::on_tb_eight_clicked()
{
    AddText("8");
}


void MainWindow::on_tb_nine_clicked()
{
    AddText("9");
}


void MainWindow::on_tb_negate_clicked() {
    if (input_number_.startsWith("-")) {
        input_number_ = input_number_.mid(1);
    } else {
        input_number_ = "-" + input_number_;
    }
    SetText(input_number_);
}


void MainWindow::on_tb_comma_clicked() {
    bool point_confirmation = false;
    for (int i = 0; i < input_number_.size(); ++i) {
        if (input_number_[i] == '.') {
            point_confirmation = true;
            break;
        }
    }
    if (!point_confirmation) {
        AddText(".");
    }
}


void MainWindow::on_tb_backspace_clicked()
{
    if (input_number_.isEmpty()) {
        return;
    } else {
        input_number_.chop(1);
        SetText(input_number_);
    }
}


void MainWindow::on_tb_equal_clicked() {
    if (current_operation_ == Operation::NO_OPERATION) {
        return;
    }
    ui->l_formula->setText(QString("%1 %2 %3 =").arg(QString::number(calculator_.GetNumber()))
                               .arg(OpToString(current_operation_))
                               .arg(QString::number(active_number_)));
    switch (current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(active_number_);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(active_number_);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(active_number_);
        break;
    case Operation::DIVISION:
        calculator_.Div(active_number_);
        break;
    case Operation::POWER:
        calculator_.Pow(active_number_);
        break;
    case Operation::NO_OPERATION:
        break;
    }
    active_number_ = calculator_.GetNumber();
    ui->l_result->setText(QString::number(active_number_));
    input_number_ = "";
    current_operation_ = Operation::NO_OPERATION;
}


void MainWindow::on_tb_reset_clicked()
{
    current_operation_ = Operation::NO_OPERATION;
    ui->l_formula->setText("");
    SetText("0");
}


void MainWindow::on_tb_mc_clicked()
{
    remembered_number_ = 0;
    memory_active_ = false;
    ui->l_memory->setText("");
}


void MainWindow::on_tb_ms_clicked()
{
    remembered_number_ = active_number_;
    memory_active_ = true;
    ui->l_memory->setText("M");

}


void MainWindow::on_tn_mr_clicked()
{
    if (memory_active_) {
    active_number_ = remembered_number_;
    ui->l_result->setText(QString::number(remembered_number_));
    input_number_ = "";
    } else {
        return;
    }
}


void MainWindow::on_tb_add_clicked() {
    HandleOperationButton(Operation::ADDITION);
}

void MainWindow::on_tb_substract_clicked() {
    HandleOperationButton(Operation::SUBTRACTION);
}

void MainWindow::on_tb_multiplicate_clicked() {
    HandleOperationButton(Operation::MULTIPLICATION);
}

void MainWindow::on_tb_divide_clicked() {
    HandleOperationButton(Operation::DIVISION);
}

void MainWindow::on_tb_power_clicked() {
    HandleOperationButton(Operation::POWER);
}

void MainWindow::HandleOperationButton(Operation new_op) {
    if (current_operation_ != Operation::NO_OPERATION) {
        switch (current_operation_) {
        case Operation::ADDITION:
            calculator_.Add(active_number_);
            break;
        case Operation::SUBTRACTION:
            calculator_.Sub(active_number_);
            break;
        case Operation::MULTIPLICATION:
            calculator_.Mul(active_number_);
            break;
        case Operation::DIVISION:
            calculator_.Div(active_number_);
            break;
        case Operation::POWER:
            calculator_.Pow(active_number_);
            break;
        case Operation::NO_OPERATION:
            break;
        }

        active_number_ = calculator_.GetNumber();
        ui->l_result->setText(QString::number(active_number_));

    } else {
        calculator_.Set(active_number_);
    }
    current_operation_ = new_op;
    ui->l_formula->setText(QString("%1 %2").arg(QString::number(calculator_.GetNumber())).arg(OpToString(current_operation_)));
    input_number_ = "";
}

