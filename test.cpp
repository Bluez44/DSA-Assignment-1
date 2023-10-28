#include<iostream>
#include<ctime>

using namespace std;

int main() {
    for(int i = 0; i < 10; i++) {
        if(i == 4) {
            cout << "Break ne du ma may\n";
            break;
        }
        else cout << "Concacduma\n";
    }
    return 0;
}