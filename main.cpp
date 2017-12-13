#include <iostream>
#include "des.h"
#include "bit_tables.h"

using namespace std;

// DES Implementation
int main()
{
    // Ask message / 64 bits
    string tmp;
    do {
        cout << "Enter a 64 bits message (0/1) : " << endl;
        cin >> tmp;
    } while (tmp.length() != 64);

    char message[64];
    for (int i = 0; i < 64; i++)
        message[i] = tmp[i] - 48;

    // Ask key / 64 bits
    do {
        cout << "Enter a 64 bits key (0/1) : " << endl;
        cin >> tmp;
    } while (tmp.length() != 64);

    char key[64];
    for (int i = 0; i < 64; i++)
        key[i] = tmp[i] - 48;

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
    des->displayTrace(false); // Display execution trace
    des->encryption();;
    des->print();

    delete des;

    return 0;
}
