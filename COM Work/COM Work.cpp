#include <iostream>
#include "xserial.hpp"
using namespace std;

int main() {
    // инициализируем доступный COM порт, без проверки бита четности, с 8-мью битами данных и одним стоп битом.
    
    xserial::ComPort com;

    int f;
    cin >> f;

    com.open(f);

    if (!com.getStateComPort()) { // Если порт не открылся
        cout << "Error: com port is not open!" << endl;
        system("pause");
        return 0; // закрываем программу
    }

    // выводим список доступых портов
    com.printListSerialPorts();


    system("pause");
    return 0;
}
