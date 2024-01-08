#include "gui/smartcalc.h"
#include <cstdlib>
#include <QApplication>
#include <iostream>


#ifndef CHEADER_H_INCLUDED
#define CHEADER_H_INCLUDED
extern "C" {
#include "backend/stack.h"
}
#endif




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SmartCalc w;
    w.show();
    char  s[20] = "1+2";
    long double ans;
    ans = calculate(s).n;
    std::cout << ans;
    return a.exec();
}

calcresult calcCpp(char s[] ) {

    calcresult ans = {0,0};
    // ans.n = calculate(s).n;
    return ans;
}