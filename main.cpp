#include <iostream>
#include "des.h"
#include "bit_tables.h"

using namespace std;

// DES Implementation
int main()
{
    // Ask message / 64 bits
    string tmp;
    bool error;
    do {
        cout << "Enter a 64 bits message in hexadecimal (16 characters without space) : " << endl;
        cin >> tmp;

        error = false;
        for (int i = 0; i < 16; i++) {
            if (tmp[i] != '0' && tmp[i] != '1' && tmp[i] != '2' && tmp[i] != '3' && tmp[i] != '4' && tmp[i] != '5' && tmp[i] != '6' && tmp[i] != '7' && tmp[i] != '8' && tmp[i] != '9' && tmp[i] != 'A' && tmp[i] != 'B' && tmp[i] != 'C' && tmp[i] != 'D' && tmp[i] != 'E' && tmp[i] != 'F')
                error = true;
        }
    } while (tmp.length() != 16 || error == true);

    // Convert hexa in binary
    char message[64];
    for (int i = 0; i < 16; i++) {
        char *a = convertHexToBin(tmp[i]);
        for (int j = 0; j < 4; j++)
            message[(i * 4) + j] = a[j] - 48;
        delete a;
    }

    // Ask key / 64 bits
    do {
        cout << "Enter a 64 bits key in hexadecimal (16 characters without space) : " << endl;
        cin >> tmp;

        error = false;
        for (int i = 0; i < 16; i++) {
            if (tmp[i] != '0' && tmp[i] != '1' && tmp[i] != '2' && tmp[i] != '3' && tmp[i] != '4' && tmp[i] != '5' && tmp[i] != '6' && tmp[i] != '7' && tmp[i] != '8' && tmp[i] != '9' && tmp[i] != 'A' && tmp[i] != 'B' && tmp[i] != 'C' && tmp[i] != 'D' && tmp[i] != 'E' && tmp[i] != 'F')
                error = true;
        }
    } while (tmp.length() != 16 || error == true);

    // Convert hexa in binary
    char key[64];
    for (int i = 0; i < 16; i++) {
        char *a = convertHexToBin(tmp[i]);
        for (int j = 0; j < 4; j++)
            key[(i * 4) + j] = a[j] - 48;
        delete a;
    }

    cout << endl << "MESSAGE :" << endl;
    displayBitTable(message, 64);
    cout << endl;
    displayAsHex(message, 64);

    cout << endl << endl << "KEY :" << endl;
    displayBitTable(key, 64);
    cout << endl;
    displayAsHex(key, 64);

    // Operate the DES algorithm
    Des *des = new Des(message, key);
    des->displayTrace(false); // Display execution trace : set true
    des->encryption();;
    des->print();
    delete des;

    return 0;
}
