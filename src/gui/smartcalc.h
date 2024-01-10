#ifndef SMARTCALC_H
#define SMARTCALC_H
#ifndef CHEADER_H_INCLUDED
#include <QMainWindow>
#include <QVector>
#include <string>
#include <iostream>
#define CHEADER_H_INCLUDED
extern "C" {
#include "../backend/stack.h"
}
#endif

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
namespace Ui { class SmartCalc; }
QT_END_NAMESPACE
calcresult calcCpp(char s[] );
class SmartCalc : public QMainWindow
{
    Q_OBJECT

public:
    SmartCalc(QWidget *parent = nullptr);
    ~SmartCalc();

private slots:
    void on_pushButton_E_calc_clicked();
    void calculate_Polish();
    void on_lineEdit_expression_textChanged(const QString &arg1);
  //  variables* SmartCalc::checkVariables();
  variables* checkVariables(variables vars_In_Notatation[]);
  void on_lineEdit_X_value_textChanged(const QString &arg1);
  std::vector<long double> getVariables(const std::string& Xvalues);
  static std::vector<std::string> Variables(parseData* data, int size) ;
  std::string polishToString(stack* parsedExpression) ;
private:
    Ui::SmartCalc *ui;
    double xBegin, xEnd, h,X;
    int N;
    QVector<double> x,y;
};
#endif // SMARTCALC_H
