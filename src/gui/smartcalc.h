#ifndef SMARTCALC_H
#define SMARTCALC_H


#include <QMainWindow>
#include <QVector>

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
    calcresult calcpol();
private:
    Ui::SmartCalc *ui;
    double xBegin, xEnd, h,X;
    int N;
    QVector<double> x,y;
};
#endif // SMARTCALC_H
