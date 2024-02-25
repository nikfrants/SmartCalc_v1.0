#ifndef SMARTCALC_H
#define SMARTCALC_H
#ifndef CHEADER_H_INCLUDED
#include <QMainWindow>
#include <QVector>
#include <iostream>
#include <string>

#include "qcustomplot.h"
#define CHEADER_H_INCLUDED
extern "C" {
#include "../backend/stack.h"
}
#endif

template <typename T, typename T2> struct Point {
  T x;
  T2 y;
};
typedef struct vars {
  std::string name;
  long double value;
  long double *adress[10];

} vars;
struct calcresult {
  long double n;
  int e;
};
QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalc;
}
QT_END_NAMESPACE
calcresult calcCpp(char s[]);
class SmartCalc : public QMainWindow {
  Q_OBJECT

public:
  SmartCalc(QWidget *parent = nullptr);
  ~SmartCalc();

private slots:
  void calcCredit();
  void on_pushButton_E_calc_clicked();
  void calculate_Polish();

  // void on_lineEdit_expression_textChanged(const QString &arg1);
  //  variables* SmartCalc::checkVariables();
  // variables* checkVariables(variables vars_In_Notatation[]);
  // void on_lineEdit_X_value_textChanged(const QString &arg1);
  static std::vector<long double> getVariables(const std::string &Xvalues);
  static std::vector<std::string> Variables(parseData *data, int size);
  static std::string polishToString(stack *parsedExpression);
  void changeStringAdd(const std::string &str);
  static calc_s parseAndCalc(const std::string &expression);
  void plot();
  std::string replaceVars(std::string expression, long double x);

  void on_lineEdit_expression_textChanged(const QString &arg1);
  void on_lineEdit_X_value_textChanged(const QString &arg1);
  void on_pushButton_D_1_clicked();
  void on_pushButton_D_0_clicked();
  void on_pushButton_D_dot_clicked();
  void on_pushButton_M_div_clicked();
  void on_pushButton_D_2_clicked();
  void on_pushButton_D_3_clicked();
  void on_pushButton_M_mul_clicked();
  void on_pushButton_D_4_clicked();
  void on_pushButton_D_5_clicked();
  void on_pushButton_D_6_clicked();
  void on_pushButton_M_sub_clicked();
  void on_pushButton_D_7_clicked();
  void on_pushButton_D_8_clicked();
  void on_pushButton_D_9_clicked();
  void on_pushButton_M_add_clicked();
  void on_pushButton_bracket_o_clicked();
  void on_pushButton_bracket_c_clicked();
  void on_pushButton_constant_e_clicked();
  void on_pushButton_constant_pi_clicked();
  void on_pushButton_M_mod_clicked();
  void on_pushButton_M_2sqrt_clicked();
  void on_pushButton_M_pow_clicked();
  void on_pushButton_E_clean_clicked();
  void on_pushButton_M_asin_clicked();
  void on_pushButton_M_acos_clicked();
  void on_pushButton_M_atan_clicked();
  void on_pushButton_M_log_clicked();
  void on_pushButton_M_sin_clicked();
  void on_pushButton_M_cos_clicked();
  void on_pushButton_M_tan_clicked();
  void on_pushButton_M_ln_clicked();
  void on_pushButton_V_graph_clicked();

  void on_pushButton_V_graph_2_clicked();

  void on_doubleSpinBox_paym_3_valueChanged(const QString &arg1);

  void on_spinBox_credit_range_2_valueChanged(const QString &arg1);

  void on_doubleSpinBox_credit_summ_1_valueChanged(const QString &arg1);

private:
  Ui::SmartCalc *ui;
  QCustomPlot *wGraphic; // Объявляем объект QCustomPlot
  QCPCurve *verticalLine;
  double xBegin, xEnd, h, X;
  int N;
  QVector<double> x, y;
  void slotMouseMove(const QString &arg1);
};
#endif // SMARTCALC_H
