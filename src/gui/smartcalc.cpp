#include "smartcalc.h"

#include <string>

#include "./ui_smartcalc.h"

#ifndef CHEADER_H_INCLUDED
#define CHEADER_H_INCLUDED
extern "C" {
#include "../backend/stack.h"
}
#endif

SmartCalc::SmartCalc(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::SmartCalc) {
  ui->setupUi(this);
  h = 0.1;
}

SmartCalc::~SmartCalc() { delete ui; }

void SmartCalc::on_pushButton_E_calc_clicked() {
  calculate_Polish();
  // здесь я собираюсь использовать функцию newprint
}
void SmartCalc::calculate_Polish() {
  char s[300];
  calc_s ans = {0,E_NO_ERRORS};
  // char *str = new char[300];
  QString expr = ui->lineEdit_expression->text();
  strcpy(s, expr.toStdString().c_str());
  // char *str1 = newprint(str);

  // if(ui->checkBox_lifetime_calc->checkState() == Qt::Checked)
  // ui->lineEdit_infotext->setText(s);
  int size,idx=0;
  variables arr[100] = {};
  variables varsInGui[100] = {0};
  variables* vars_In_Notatation;
  vars_In_Notatation = getVariablesParsed(s, arr, &size);

  std::string listvars = ui->lineEdit_X_value->text().toStdString();
  std::string str = ui->lineEdit_X_value->text().toStdString();
  variables array [100];

  char *cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());

  char *token = strtok(cstr, " ,");
  while (token != nullptr && idx < 100 && vars_In_Notatation[idx].name[0]!='\000') {
    strcpy(varsInGui[idx].name, token);
  //  varsInGui[idx].value = std::stold(token);
    idx++;
    token =  strtok(nullptr, " ,");
  }

  delete[] cstr;
  if (size != idx)
    ans.e = E_INCORRECT_VARIABLES;
  else if(size)
    for (int i = 0; vars_In_Notatation[i].name[0] != '\000'; i++)
      vars_In_Notatation[i].value = varsInGui[i].value;

  if (ans.e == E_NO_ERRORS) ans = calculate(s,vars_In_Notatation);
  if (ans.e == E_NO_ERRORS)
    ui->lineEdit_infotext->setText(getPolish(s));
  else
    ui->lineEdit_infotext->setText(errorDescription(ans.e));
  ui->lineEdit_answer->setText(std::to_string(ans.n).c_str());
}

// void SmartCalc::on_pushButton_E_calc_clicked() {
//   char message[] = "Example message";
//   char s[300];
//   calcresult ans;
//   strcpy(s,"1+2");
//   // char *str1 = newprint(str);
//
//   ans = { calculate(s).n, calculate(s).e };
//   // if(ui->checkBox_lifetime_calc->checkState() == Qt::Checked)
//   ui->lineEdit_infotext->setText(s);
//   //здесь я собираюсь использовать функцию newprint
// }
void SmartCalc::on_lineEdit_expression_textChanged(const QString& arg1) {
  if (ui->checkBox_lifetime_calc->checkState() == Qt::Checked)
    calculate_Polish();
}

