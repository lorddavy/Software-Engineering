#include<iostream>
using namespace std;
#include "myFraction.hxx"

int main()
{

myFraction<int> f1 = myFraction<int>(2,3);	//creación f1
myFraction<int> f2 = myFraction<int>(8,12);	//creación f2

myFraction<int> f3 = f1 + f2;	//suma
myFraction<int> f4 = f1 * f2;	//multiplicación

std::cout << "Resultado 1: " << f3.a() << "/" << f3.b() << std::endl;	//prints f3
std::cout << "Resultado 2: " << f4.a() << "/" << f4.b() << std::endl;	//prints f4

return(0);
}
