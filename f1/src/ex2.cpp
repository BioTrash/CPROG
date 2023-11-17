#include <iostream>
#include <iomanip>

using namespace std;

int power(int, int);

int main() {
    cout << "x" << setw(15) << "x**3" << endl;
    for(int x = 0; x < 10; x++){
        cout << x << setw(15) << power(x, 3) << endl;
    }

    return 0;
}

int power(int bas, int expo) {
    int result = 1;
    for (int i = 0; i < expo; i++){
        result *= bas;
    }
    return result;
}