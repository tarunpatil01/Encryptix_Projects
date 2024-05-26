#include <iostream>
using namespace std;

int main(){
    unsigned x,y;
    char choice ;
    cout<< "Calculator:\n"<< "\n Insert two no to perform operation"<<endl;
    cin>>x>>y;
    cout<< "Which operation you want to performed ";
    cin >> choice;
    switch (choice)
    {
    case '+':
        cout << "Addition of "<< x <<" and "<< y <<" is "<< x + y << endl; 
        break;
    case '-':
        cout<< "Subsraction of "<< x <<" and "<< y <<" is "<< x - y << endl;
        break;
    case '/':
        cout<< "Division of "<< x <<" and "<< y <<" is "<< x / y << endl;
        break;
    case '*':
        cout<< "Multiplication of "<< x <<" and "<< y <<" is "<< x * y << endl;
        break;
    default:
        cout << "Sorry! I am only allowed to do +, -, /, * "<< endl;
        break;
    }
}