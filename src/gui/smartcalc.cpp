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
  ui->grid->setInteraction(QCP::iRangeZoom, true);
  ui->grid->setInteraction(QCP::iRangeDrag, true);
  ui->grid->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  // disable connecting dots with lines in grind plot

  // setLineStyle(QCPGraph::lsNone);
  // wGraphic = new QCustomPlot();
  // ui->centralwidget->layout()->addWidget(wGraphic);
  // connect(ui->grid, SIGNAL(QCustomPlot::plottableClick), this, SLOT(const
  // QString& arg1));
  // ui->gridLayout->addWidget(wGraphic,1,0,1,1);
  // ui->grid->installEventFilter(this);

  // plotting
}
// void SmartCalc::slotMouseMove(const QString& arg1) {
//   /* Если при передвижении мыши, ей кнопки нажаты,
//    * то вызываем отработку координат мыши
//    * через слот клика
//    * */
//   cout << "moved";
//   string test = "moved";
//   ui->lineEdit_answer->setText(test.c_str());
//   if (QApplication::mouseButtons()) {
//     // plot();
//   }
// }
void SmartCalc::plot() {
  x.clear();
  y.clear();
  ui->grid->addGraph();
  QCPGraph* graph =
      ui->grid->graph(0);  // Предполагая, что вы имеете один график
  // Отключаем отображение линий между точками на графике
  ui->grid->graph(0)->clearData();
  ui->grid->clearItems();
  ui->grid->replot();

  // DOTS   use dots instead of lines. comment if lines are needed
  graph->setLineStyle(QCPGraph::lsNone);
  QCPScatterStyle scatterStyle;
  scatterStyle.setShape(QCPScatterStyle::ssCircle);
  scatterStyle.setPen(QPen(Qt::blue, 2));
  scatterStyle.setBrush(Qt::blue);
  scatterStyle.setSize(1);
  graph->setScatterStyle(scatterStyle);

  QCPAxisRect* axisRect = ui->grid->axisRect();
  QCPRange xrange = axisRect->axis(QCPAxis::atBottom)->range();
  //  QCPRange yrange = axisRect->axis(QCPAxis::atLeft)->range();
  xBegin =
      ui->grid->xAxis->range().lower -
      (ui->grid->xAxis->range().upper - ui->grid->xAxis->range().lower) * 3;
  xEnd = ui->grid->xAxis->range().upper +
         (ui->grid->xAxis->range().upper - ui->grid->xAxis->range().lower) * 3;

  // DOTS
  h = (xEnd - xBegin) / 50000;
  ;
  // LINES
  // h = (xEnd - xBegin) / 5000;

  std::string expression = ui->lineEdit_expression->text().toStdString();
  // ToDo возможность задавать ppi
  // h должно динамически меняться в зависимости от поведения функции
  // если разница координат слишком больша относительно ppi, то h уменьшается
  // и наоборот, если разница между координатами точек слишком маленькая, то h
  // увеличивается
  // (это поможет красиво отрисовывать tan(x) например)
  int ppi = 300;
  Point<int, int> p{};
  QVector<Point<long double, long double>> points;
  N = (xEnd - xBegin) / h + 2;
  calc_s ans = {0, -100};
  calc_s ans2 = {0, -100};
  string readystr;
  string readystr2;
  string prevreadystr;
  for (X = xBegin; X <= xEnd; X += h) {
    readystr = replaceVars(expression, X);
    // { // LINES
    //   ans = parseAndCalc(readystr);
    //   readystr2 = replaceVars(expression, X + h);
    //   ans2 = parseAndCalc(readystr2);
    //   if (ans.e == E_NO_ERRORS && ans2.e == E_NO_ERRORS) {
    //     auto* line = new QCPItemLine(ui->grid);
    //     line->start->setCoords(X, ans.n);
    //     line->end->setCoords(X+h, ans2.n);
    //     line->setPen(QPen(Qt::black));
    //     ui->grid->addItem(line);
    //
    //     //   y.push_back(ans.n);
    //   }
    // }
    {  // DOTS
      calc_s ans = parseAndCalc(readystr);
      if (ans.e == E_NO_ERRORS) {
        x.push_back((X));
        y.push_back(ans.n);
      }
    }
  }

  // ui->grid->graph()->clearData();

  ui->grid->addGraph();
  ui->grid->graph(0)->addData(x, y);
  ui->grid->replot();
}

std::string longDoubleToString(long double n) {
  char buffer[100];

  int bufferSize = snprintf(buffer, 100, "%.10Lf", n);

  if (bufferSize >= 0 && bufferSize < 100) {
    return std::string(buffer);
  } else {
    return "Error: Unable to convert long double to string";
  }
}
string SmartCalc::replaceVars(string expression, long double x) {
  string tmplt = "x";
  for (int i = 0; i < expression.size(); i++)
    if (expression[i] == 'x') expression.replace(i, 1, longDoubleToString(x));
  return expression;
}
calc_s SmartCalc::parseAndCalc(const std::string& expression) {
  int size, error, xExists = 0;

  parseData* parsedExpression = {nullptr};
  parsedExpression = parser((char*)expression.c_str(), &size);
  error = check(parsedExpression, size, (char*)expression.c_str());
  if (error != E_NO_ERRORS && error != E_ONLY_DIGITS_EXIST ||
      parsedExpression[0].type == E_INCORRECT_EXPRESSION) {
    calc_s ans = {0, error != E_NO_ERRORS ? error : E_INCORRECT_EXPRESSION};
    return ans;
  }
  stack notation, reversed;
  stackInit(&notation), stackInit(&reversed);
  notation = evaluatePolishNotation((char*)expression.c_str());
  while (notation.stSize) push(&reversed, pop(&notation));
  string notationStr = polishToString(&reversed);
  calc_s ans = calcPolishNotation(&reversed);

  free(parsedExpression);
  freeStack(&notation);
  freeStack(&reversed);
  return ans;
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
    if (expression[i] == 'x') {
      xExists = 1;
      expression.replace(i, 1, ui->lineEdit_X_value->text().toStdString());
    }
  }
  parseData* parsedExpression = {nullptr};
  parsedExpression = parser((char*)expression.c_str(), &size);  // TODO CLEAR
  error = check(parsedExpression, size, (char*)expression.c_str());
  if (error != E_NO_ERRORS ||
      parsedExpression[0].type == E_INCORRECT_EXPRESSION ||
      xExists == 1 && Xvalues.empty()) {
    // printf("Error - %s", errorDescription(error));
    calc_s ans = {0, error != E_NO_ERRORS ? error : E_INCORRECT_EXPRESSION};
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
      answer = longDoubleToString(ans.n);

      infotext = notationStr;
    }
    free(parsedExpression);
    freeStack(&notation);
    freeStack(&reversed);
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
// void getVariablesFromPolish(stack* polish, variables* array[],
//                             int* arrayindex) {
//   stNode* temp = polish->root;
//   *arrayindex = -1;
//   // for(int i = 0; i < 100;++i) {
//   //   for(auto & adres : array[i]->adress)
//   //   adres = nullptr;
//   // }
//   int addressidx = 0;
//   while (temp != nullptr) {
//     if (temp->data.type == TYPE_VARIABLE) {
//       if (!var_in_array(*array, temp->data.varName)) {
//         ++*arrayindex;
//         stNode* searchvar = temp;
//         strcpy(array[*arrayindex]->name, temp->data.varName);
//         addressidx = 1;
//         while (searchvar != nullptr) {
//           if (searchvar->data.type == TYPE_VARIABLE &&
//               strcmp(array[*arrayindex]->name, searchvar->data.varName) == 0)
//               {
//             array[*arrayindex]->adress[addressidx] = &searchvar->data.number;
//             array[*arrayindex]->adresscount = addressidx;
//             ++addressidx;
//           }
//           searchvar = searchvar->next;
//         }
//       }
//     }
//     temp = temp->next;
//   }
//   *arrayindex += 1;
// }
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
void SmartCalc::on_lineEdit_expression_textChanged(const QString& arg1) {
  if (ui->checkBox_lifetime_calc->checkState() == Qt::Checked)
    calculate_Polish();
}
void SmartCalc::on_lineEdit_X_value_textChanged(const QString& arg1) {
  if (ui->checkBox_lifetime_calc->checkState() == Qt::Checked)
    calculate_Polish();
}

void SmartCalc::on_pushButton_D_1_clicked() { changeStringAdd("1"); }

void SmartCalc::changeStringAdd(const string& str) {
  string curr = ui->lineEdit_expression->text().toStdString();
  ui->lineEdit_expression->setText((curr + str).c_str());
}

void SmartCalc::on_pushButton_D_0_clicked() { changeStringAdd("0"); }

void SmartCalc::on_pushButton_D_dot_clicked() { changeStringAdd("."); }

void SmartCalc::on_pushButton_M_div_clicked() { changeStringAdd("/"); }

void SmartCalc::on_pushButton_D_2_clicked() { changeStringAdd("2"); }

void SmartCalc::on_pushButton_D_3_clicked() { changeStringAdd("3"); }

void SmartCalc::on_pushButton_M_mul_clicked() { changeStringAdd("*"); }

void SmartCalc::on_pushButton_D_4_clicked() { changeStringAdd("4"); }

void SmartCalc::on_pushButton_D_5_clicked() { changeStringAdd("5"); }

void SmartCalc::on_pushButton_D_6_clicked() { changeStringAdd("6"); }

void SmartCalc::on_pushButton_M_sub_clicked() { changeStringAdd("-"); }

void SmartCalc::on_pushButton_D_7_clicked() { changeStringAdd("7"); }

void SmartCalc::on_pushButton_D_8_clicked() { changeStringAdd("8"); }

void SmartCalc::on_pushButton_D_9_clicked() { changeStringAdd("9"); }

void SmartCalc::on_pushButton_M_add_clicked() { changeStringAdd("+"); }

void SmartCalc::on_pushButton_bracket_o_clicked() { changeStringAdd("("); }

void SmartCalc::on_pushButton_bracket_c_clicked() { changeStringAdd(")"); }

void SmartCalc::on_pushButton_constant_e_clicked() { changeStringAdd("e"); }

void SmartCalc::on_pushButton_constant_pi_clicked() { changeStringAdd("pi"); }

void SmartCalc::on_pushButton_M_mod_clicked() { changeStringAdd("mod"); }

void SmartCalc::on_pushButton_M_2sqrt_clicked() { changeStringAdd("sqrt"); }

void SmartCalc::on_pushButton_M_pow_clicked() { changeStringAdd("^"); }

void SmartCalc::on_pushButton_E_clean_clicked() {
  ui->lineEdit_expression->setText("");
}

void SmartCalc::on_pushButton_M_asin_clicked() { changeStringAdd("asin"); }

void SmartCalc::on_pushButton_M_acos_clicked() { changeStringAdd("acos"); }

void SmartCalc::on_pushButton_M_atan_clicked() { changeStringAdd("atan"); }

void SmartCalc::on_pushButton_M_log_clicked() { changeStringAdd("log"); }

void SmartCalc::on_pushButton_M_sin_clicked() { changeStringAdd("sin"); }

void SmartCalc::on_pushButton_M_cos_clicked() { changeStringAdd("cos"); }

void SmartCalc::on_pushButton_M_tan_clicked() { changeStringAdd("tan"); }

void SmartCalc::on_pushButton_M_ln_clicked() { changeStringAdd("ln"); }

void SmartCalc::on_pushButton_V_graph_clicked() {// changeStringAdd("plot");
  plot();
}


