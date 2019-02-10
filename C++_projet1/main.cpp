#include <iostream>
#include <./calculator.h>

int Calculator::calculate(int x, int y, char oper) {
    switch (oper)   {
    case '+': return (x+y);
    case '-' : return (abs(x-y));
    case '*' : return (x*y);
    case '/' : return (x/y);
    default: return (0);    }   }

using namespace std ;

int main()
{
    int c = 10;
    int y = 20;
    char oper;
    cout << "Donner le calcul :  x ? y " << endl;
    cin >> c >> oper >> y ;
    Calculator cal ;
    int result = cal::calculate(c,y,oper);
    cout << "le resultat est " << result << endl;
    return 0;
}