#include "smartcalc.h"
#include "./ui_smartcalc.h"


#ifndef CHEADER_H_INCLUDED
#define CHEADER_H_INCLUDED
extern "C" {
#include "../backend/stack.h"
}
#endif

SmartCalc::SmartCalc(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::SmartCalc) {
    ui->setupUi(this);
    h = 0.1;
}

SmartCalc::~SmartCalc() {
    delete ui;
}


void SmartCalc::on_pushButton_E_calc_clicked() {
    char message[] = "Example message";
    char s[300];
    calcresult ans;
    strcpy(s,"1+2");
    // char *str1 = newprint(str);

    ans = { calculate(s).n, calculate(s).e };
    // if(ui->checkBox_lifetime_calc->checkState() == Qt::Checked)
    ui->lineEdit_infotext->setText(s);
    //здесь я собираюсь использовать функцию newprint
}

 calcresult SmartCalc::calcpol() {
    int size, error;
    char s[300] =        "1+2";

    calcresult ans = {0,0};
    ans.n = calcCpp(s).n;
    return ans;
}



