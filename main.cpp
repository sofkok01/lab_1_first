#include <iostream>
using namespace std;

void changeBit() {
    int number;
    cout << "ОБМЕН ЗНАЧЕНИЯ 3-го и 7-го бита" << endl;
    cout << "Введите число (int): ";
    cin >> number;
    cout << "Исходное число: " << number << endl;
    cout << "Исходное двоичное: ";
    for (int i = 31; i >= 0; i--) {
        cout << ((number >> i) & 1);
        if (i % 8 == 0) cout << " ";
    }
    cout << endl;
    //извлекаем значения битов
    int bit3 = (number >> 3) & 1;
    int bit7 = (number >> 7) & 1;

    //смена битов
    if (bit3 != bit7) {
        number ^= ((1 << 3) | (1 << 7)); //сначала создаем общую маску, а после XORим те изменяем биты
    }
    cout << "После обмена: " << number << endl;
    cout << "После обмена двоичное: ";
    for (int i = 31; i >= 0; i--) {
        cout << ((number >> i) & 1);
        if (i % 8 == 0) cout << " ";
    }
    cout << endl;

}
void sizeOfType() {
    cout
        << "int: " << sizeof(int) << " байт" << endl
        << "short int: " << sizeof(short int) << " байт" << endl
        << "long int: " << sizeof(long int) << " байт" << endl
        << "float: " << sizeof(float) << " байт" << endl
        << "double: " << sizeof(double) << " байт" << endl
        << "long double: " << sizeof(long double) << " байт" << endl
        << "char: " << sizeof(char) << " байт" << endl
        << "bool: " << sizeof(bool) << " байт" << endl;
}
void binary_view(short task) {
    switch (task) {
        case 2: {
            cout << "Знак |        Значащие разряды           " << endl;
            cout << "-----|-----------------------------------" << endl;
            break;
        }
        case 3: {
            cout << "Знак |экспонента|         мантисса          " << endl;
            cout << "-----| -------- |---------------------------" << endl;
            break;
        }
        case 4: {
            cout << "Знак |  экспонента |                           мантисса                        " << endl;
            cout << "-----| ----------- | ----------------------------------------------------------" << endl;
            break;
        }
    }
}

int main(){
    setlocale(0, "");
    //individual task (var 9)
    //Обмен значений двух битов. Поменяйте местами значения 3-го и 7-го битов (нумерация с 0 от младшего разряда).
    changeBit();

    // 1) Вывести, сколько памяти (в байтах) на вашем компьютере отводится под различные типы данных
    // со спецификаторами и без: int, short int, long int, float, double, long double, char и bool
    sizeOfType();

    // 2-4 Вывести на экран двоичное представление в памяти (все разряды) числа
    // При выводе необходимо визуально обозначить знаковый разряд и значащие разряды отступами или цветом
    int intNumber;
    unsigned int intMask;
    cout << "Введите число (int): ";
    cin >> intNumber;

    int iorder = sizeof(intNumber) * 8;
    intMask = 1<<(iorder-1); //сдвигаем 1 тк первый бит под знак

    binary_view(2);

    for (int i = 1; i <= iorder; i++) {
        int bit = (intNumber & intMask) ? 1 : 0;
        if (i == 1) {
            cout << "  " << bit << "  | ";}
        else if (i%8==0) {
            cout << bit << " ";
        }
        else cout << bit;
        intMask>>=1;
    }
    cout << endl;


    cout << "Введите число (float): ";
    union {
        float floatNumber;
        unsigned int floatValue;
    };
    cin >> floatNumber;

    int forder = sizeof(floatValue) * 8;
    unsigned int floatMask = 1U<<(forder-1); //сдвигаем "1" тк первый бит под знак
    cout << floatMask << endl;
    binary_view(3);
    for (int i = 1; i <= forder; i++) {
        int bit = (floatValue & floatMask) ? 1 : 0;
        if (i == 1) {
            //знак
            cout << "  " << bit << "  | ";}
        else if (i < 9) {
            //экспонента
            cout << bit;
            if (i%8==0 && i!=8) cout << bit << " ";
        }
        else if (i == 9) {
            // Конец экспоненты
            cout << bit << " | ";}
        else {
            //мантисса
            cout << bit;
            if (i%8==0) cout << bit << " ";
        }
        floatMask>>=1;
    }
    cout << endl;

    cout << "Введите число (double): ";
    union {
        double doubleNumber;
        unsigned long long doubleValue; //тк double заниамет 8 байт, а unsigned int 4 байта
    };
    cin >> doubleNumber;

    int dorder = sizeof(doubleValue)*8;
    unsigned long long doubleMask = 1ULL <<(dorder-1); //тк требутеся 64 бита памяти, то используем везде ULL
    cout << doubleMask << endl;

    binary_view(4); // исправить через choice тк для каждого типа разные

    for (int i = 1; i<= dorder; i++) {
        int bit = (doubleValue & doubleMask) ? 1 : 0;

        if (i == 1) {
            //знак
            cout << "  " << bit << "  | ";}
        else if (2 <= i && i <= 11) {
            //экспонента
            cout << bit;}
        else if (i == 12) {
            // Конец экспоненты
            cout << bit << " | ";}
        else if (i > 12) {
            // Мантисса
            cout << bit;
            // Пробелы каждые 8 бит в мантиссе
            if ((i - 12) % 8 == 0 && i != 64) cout << " ";
        }
        doubleMask >>= 1;
    }
    cout << endl;


    // 5 изменение бита
    short int choice, bitPosition, newBit;
    while (true) {
        cout << "Выберите тип числа, в котором хотите изменить значение бита: \n\
         1. int \n\
         2. float \n\
         3. double" << endl;
        cin >> choice;
        if (choice >= 1 && choice <= 3) break;
        cout << "такого выбора нет, попробуйте снова" << endl;
    }

    switch (choice) {
        case 1:
            while (true) {
                cout << "Номер какого бита изменить [1.." << sizeof(int)*8 << "]: ";
                cin >> bitPosition;
                if (bitPosition >= 1 && bitPosition <= sizeof(int)*8) break;
                cout << "такого выбора нет, попробуйте снова" << endl;
            }
            break;
        case 2:
            while (true) {
                cout << "Номер какого бита изменить [1.." << sizeof(float)*8 << "]: ";
                cin >> bitPosition;
                if (bitPosition >= 1 && bitPosition <= sizeof(float)*8) break;
                cout << "такого выбора нет, попробуйте снова" << endl;
            }
            break;
        case 3:
            while (true) {
                cout << "Номер какого бита изменить [1.." << sizeof(double)*8 << "]: ";
                cin >> bitPosition;
                if (bitPosition >= 1 && bitPosition <= sizeof(double)*8) break;
                cout << "такого выбора нет, попробуйте снова" << endl;
            }
            break;
    }

    while (true){
        cout << "На какое значение (0|1): ";
        cin >> newBit;
        if (newBit == 0 || newBit == 1) break;
        cout << "Некорректное значение! только 0 и 1" << endl;
    }
    switch (choice) {
        case 1: {
            if (newBit==1) intNumber |= (1 << (sizeof(int)*8 - bitPosition));
            else intNumber &= ~(1 << (32 - bitPosition));
            cout << intNumber;
            break;
        }
        case 2: {
            //используем существующий выше модуль union (повторное приведет к ошибке)
            if (newBit==1) floatValue |= (1U << (sizeof(float)*8 - bitPosition));
            else floatValue &= ~(1U << (32 - bitPosition));
            cout << floatNumber;
            break;
        }
        case 3: {
            //используем существующий выше модуль union (повторное приведет к ошибке)
            if (newBit==1) doubleValue |= (1ULL << (sizeof(double)*8 - bitPosition));
            else doubleValue &= ~(1ULL << (64 - bitPosition));
            cout << doubleNumber;
            break;
        }
    }
}