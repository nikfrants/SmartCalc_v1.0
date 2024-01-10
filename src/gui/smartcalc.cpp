#include "smartcalc.h"

#include <string>

#include "./ui_smartcalc.h"

#ifndef CHEADER_H_INCLUDED
#define CHEADER_H_INCLUDED
extern "C" {
#include "../backend/stack.h"
}
#endif
using namespace std;
SmartCalc::SmartCalc(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::SmartCalc) {
  ui->setupUi(this);
  h = 0.1;
}

SmartCalc::~SmartCalc() { delete ui; }
void getVariablesFromPolish(stack* polish, variables* array[], int* arrayindex);
void SmartCalc::on_pushButton_E_calc_clicked() {
  calculate_Polish();
  // здесь я собираюсь использовать функцию newprint
}
void SmartCalc::calculate_Polish() {
  std::string infotext;
  std::string Xvalues = ui->lineEdit_X_value->text().toStdString();
  std::string answer;
  std::string expression = ui->lineEdit_expression->text().toStdString();
  int size, error, xExists = 0;
  string tmplt = "x";
  for (int i = 0; i < expression.size(); i++) {
    if (expression[i] == 'x') {xExists=1;
      expression.replace(i, 1, ui->lineEdit_X_value->text().toStdString());
    }
  }
  parseData* parsedExpression = {nullptr};
  parsedExpression = parser((char*)expression.c_str(), &size);  // TODO CLEAR
  error = check(parsedExpression, size, (char*)expression.c_str());
  if (error != E_NO_ERRORS ||
      parsedExpression[0].type == E_INCORRECT_EXPRESSION || xExists == 1 && Xvalues.empty()) {
    // printf("Error - %s", errorDescription(error));
    calc_s ans = {0,
                  error != E_NO_ERRORS ? error : E_INCORRECT_EXPRESSION};
    infotext = errorDescription(ans.e);
    answer = NAN;
    // return ans.n;
  } else {
    // infotext=
    stack notation, reversed;
    stackInit(&notation), stackInit(&reversed);
    notation = evaluatePolishNotation((char*)expression.c_str());
    while (notation.stSize) push(&reversed, pop(&notation));
    string notationStr = polishToString(&reversed);
    calc_s ans = calcPolishNotation(&reversed);
    freeStack(&notation);
    freeStack(&reversed);
    if (ans.e != E_NO_ERRORS) {
      answer = NAN;
      infotext = errorDescription(ans.e);
    } else {
      answer = to_string(ans.n);

      infotext = notationStr;
    }
    free(parsedExpression);


  }
  ui->lineEdit_answer->setText(answer.c_str());
  ui->lineEdit_infotext->setText(infotext.c_str());
}
int isInVector(vector<string> s, string* temp) {
  for (const auto& i : s) {
    if (i == *temp) return 1;
  }
  return 0;
}
std::vector<std::string> SmartCalc::Variables(parseData* data, int size) {
  vector<string> ans;
  string temp;

  for (int i = 0; i < size; ++i) {
    temp.assign(data[i].varName, *data[i].varName + 5);
    if (data[i].type == TYPE_VARIABLE && !isInVector(ans, &temp))
      ans.emplace_back(temp);
  }
  return ans;
}
void getVariablesFromPolish(stack* polish, variables* array[],
                            int* arrayindex) {
  stNode* temp = polish->root;
  *arrayindex = -1;
  // for(int i = 0; i < 100;++i) {
  //   for(auto & adres : array[i]->adress)
  //   adres = nullptr;
  // }
  int addressidx = 0;
  while (temp != nullptr) {
    if (temp->data.type == TYPE_VARIABLE) {
      if (!var_in_array(*array, temp->data.varName)) {
        ++*arrayindex;
        stNode* searchvar = temp;
        strcpy(array[*arrayindex]->name, temp->data.varName);
        addressidx = 1;
        while (searchvar != nullptr) {
          if (searchvar->data.type == TYPE_VARIABLE &&
              strcmp(array[*arrayindex]->name, searchvar->data.varName) == 0) {
            array[*arrayindex]->adress[addressidx] = &searchvar->data.number;
            array[*arrayindex]->adresscount = addressidx;
            ++addressidx;
          }
          searchvar = searchvar->next;
        }
      }
    }
    temp = temp->next;
  }
  *arrayindex += 1;
}
std::string SmartCalc::polishToString(stack* parsedExpression) {
  std::string s;
  stNode* temp = parsedExpression->last;
  for (int i = 0; temp; ++i) {
    char buf[150];
    if (temp->data.type == TYPE_DIGIT)
      if (fmodl(temp->data.number, (int)temp->data.number) == 0)
        sprintf(buf, "%.0LF ", temp->data.number);
      else
        sprintf(buf, "%.2LF ", temp->data.number);
    if (temp->data.type == TYPE_FUNCTION) sprintf(buf, "%s", temp->data.func);
    if (temp->data.type == TYPE_VARIABLE)
      sprintf(buf, "%s ", temp->data.varName);
    if (temp->data.type == TYPE_OPERATOR) sprintf(buf, "%c ", temp->data.op);
    // strcpy(&str[i], buf);
    // s[0]=' ';
    for (int j = 0; buf[j]; ++j, ++i) s += buf[j];
    temp = temp->prev;
  }
  return s;
}
std::vector<long double> SmartCalc::getVariables(const std::string& Xvalues) {
  int idx = 0;
  std::vector<long double> varsInGui;
  char* cstr = new char[Xvalues.length() + 1];
  strcpy(cstr, Xvalues.c_str());
  char* token = strtok(cstr, " ,");
  while (token != nullptr && idx < 100) {
    varsInGui.push_back(std::strtold(token, nullptr));
    idx++;
    token = strtok(nullptr, " ,");
  }
  delete[] cstr;
  return varsInGui;
}

variables* SmartCalc::checkVariables(variables vars_In_Notatation[]) {
  char s[300];
  calc_s ans = {0, E_NO_ERRORS};
  QString expr = ui->lineEdit_expression->text();
  strcpy(s, expr.toStdString().c_str());

  int size, idx = 0;
  variables arr[100] = {};
  variables varsInGui[100] = {0};
  vars_In_Notatation = getVariablesParsed(s, arr, &size);

  std::string listvars = ui->lineEdit_X_value->text().toStdString();
  std::string str = ui->lineEdit_X_value->text().toStdString();
  variables array[100];
  int arraysize;
  parseData* parsed = parser((char*)listvars.c_str(), &arraysize);
  if (parsed[0].type != E_INCORRECT_EXPRESSION &&
      !containsVariables(parsed, arraysize) && str.empty()) {
    //  strcpy(vars_In_Notatation[0].name, "\000");
    //  vars_In_Notatation->value = 0;
  } else if (!containsVariables(parsed, arraysize) && str.empty()) {
    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    char* token = strtok(cstr, " ,");
    while (token != nullptr && idx < 100 &&
           vars_In_Notatation[idx].name[0] != '\000') {
      varsInGui[idx].value = std::strtold(token, nullptr);
      //    varsInGui[idx].value = std::atof(token);
      //  varsInGui[idx].value = std::stold(token);
      idx++;
      token = strtok(nullptr, " ,");
    }
    delete[] cstr;
    if (size != idx) {
      strcpy(vars_In_Notatation[0].name, "error");
      vars_In_Notatation->value = -1;
      return vars_In_Notatation;
    } else if (size)
      for (int i = 0; vars_In_Notatation[i].name[0] != '\000'; i++)
        vars_In_Notatation[i].value = varsInGui[i].value;

  } else {
    strcpy(vars_In_Notatation[0].name, "error");
    vars_In_Notatation->value = -1;
  }
  return vars_In_Notatation;
}

void SmartCalc::on_lineEdit_expression_textChanged(const QString& arg1) {
  if (ui->checkBox_lifetime_calc->checkState() == Qt::Checked)
    calculate_Polish();
}

void SmartCalc::on_lineEdit_X_value_textChanged(const QString& arg1) {
  if (ui->checkBox_lifetime_calc->checkState() == Qt::Checked)
    calculate_Polish();
}
//
// void SmartCalc::calculate_Polish1() {
//   variables vars[100] = {0};
//   char s[300] = {0};
//   parseData* newexpression = {nullptr};
//   int size, error;
//   strcpy(s, ui->lineEdit_expression->text().toStdString().c_str());
//   newexpression = parser(s, &size);
//   error = check(newexpression, size, s);
//   if (error != E_NO_ERRORS) {
//     // printf("Error - %s", errorDescription(error));
//     ui->lineEdit_infotext->setText(errorDescription(error));
//     // return ans.n;
//   } else {
//     if (containsVariables(newexpression, size) == 0 &&
//           !ui->lineEdit_X_value->text().toStdString().empty()||
//           containsVariables(newexpression, size) == 1 &&
//            ui->lineEdit_X_value->text().toStdString().empty() ) {
//       ui->lineEdit_infotext->setText(errorDescription(E_INCORRECT_VARIABLES));}
//     else {
//       variables* fromgui = checkVariables(vars);
//       char *polish = new char[300];
//
//       if (getPolish(s, polish) == "Expression is incorrect") {
//         delete [] polish;
//         ui->lineEdit_infotext->setText(errorDescription(E_INCORRECT_EXPRESSION));
//       } else {
//         delete [] polish;
//         if (fromgui && fromgui[0].value != -1 && fromgui[0].name !=
//         "error")
//         {
//
//           strcpy(s, ui->lineEdit_expression->text().toStdString().c_str());
//           calc_s ans = calculate(s, fromgui);
//           if (ans.e != E_NO_ERRORS)
//             ui->lineEdit_infotext->setText(errorDescription(ans.e));
//           else {
//             char *temp1 =(char*) malloc(sizeof(char*)*300);
//             for(int i = 0; i < 300; ++i) *(temp1+i) = '\000';
//             getPolish(s,  temp1);
//             // ui->lineEdit_infotext->setText(polish);
//             ui->lineEdit_infotext->setText(temp1);
//             free(temp1);
//           }
//           ui->lineEdit_answer->setText(std::to_string(ans.n).c_str());
//         } else {
//           ui->lineEdit_infotext->setText(errorDescription(E_INCORRECT_VARIABLES));
//         }
//       }
//
//     }
//   }
//   free(newexpression);
//
// }