#include <cstring>
#include <iostream>
#include "permutations.h"
#include "bit_tables.h"
#include "pc.h"
#include "subkey.h"

using namespace std;

// Constructor
Subkey::Subkey(char key[])
{
    this->key = key;
}

// Destructor
Subkey::~Subkey()
{

}

void Subkey::displayTrace(bool value)
{
    trace = value;
}

char *Subkey::leftShift(char *table, long tabsize, long shift)
{
    char *tmp;
    tmp = new char[tabsize];

    for (int i = tabsize - 1; i >= 0; i--) {
        if (i - shift < 0)
            tmp[i - shift + tabsize] = table[i];
        else
            tmp[i - shift] = table[i];
    }

    return tmp;
}

char * Subkey::concatenation(char *a, char *b, long tabsize)
{
    char * tmp;
    tmp = new char[tabsize];

    for (int i = 0; i < tabsize / 2; i++)
        tmp[i] = a[i];

    for (int i = 0; i < tabsize / 2; i++)
        tmp[i + (tabsize / 2)] = b[i];

    return tmp;
}

char **Subkey::generateSubkeys()
{
    if (trace)
    {
        cout << "GLOBAL KEY (64 bits)" << endl;
        displayBitTable(key, 64);
        cout << " / ";
        displayAsHex(key, 64);
        cout << endl << endl;
    }

    subkeys = new char* [16];

    for (int i = 0; i < 16; i++) {
        if (trace)
            cout << "ROUND " << i + 1;

        // Split and permute
        L = permute(key, pc_1_left, 28);
        R = permute(key, pc_1_right, 28);

        if (trace) {
            cout << endl << "L : ";
            displayBitTable(L, 28);
            cout << " / ";
            displayAsHex(L, 28);
            cout << endl << "R : ";
            displayBitTable(R, 28);
            cout << " / ";
            displayAsHex(R, 28);
            cout << endl;
        }

        // Left shift
        L = leftShift(L, 28, keyshift[i]);
        R = leftShift(R, 28, keyshift[i]);

        if (trace) {
            cout << endl << "leftshifting L and R by " << (int) keyshift[i] << " bits";
            cout << endl << "shifted L : ";
            displayBitTable(L, 28);
            cout << " / ";
            displayAsHex(L, 28);
            cout << endl << "shifted R : ";
            displayBitTable(R, 28);
            cout << " / ";
            displayAsHex(R, 28);
            cout << endl;
        }

        // Concatenation
        subkeys[i] = concatenation(L, R, 28 + 28);

        if (trace) {
            cout << endl << "reunited : ";
            displayBitTable(subkeys[i], 56);
            cout << " / ";
            displayAsHex(subkeys[i], 56);
        }

        // PC_2 permutation
        subkeys[i] = permute(subkeys[i], pc_2, 48);

        if (trace) {
            cout << endl << "After pc_2 permutation : 48 BITS KEY VALUE : " << endl;
            displayBitTable(subkeys[i], 48);
            cout << " / ";
            displayAsHex(subkeys[i], 48);
            cout << endl << endl;
        }
    }

    if (trace) {
        cout << "SUBKEYS" << endl;
        for (int i = 0; i < 16; i++) {
            displayBitTable(subkeys[i], 48);
            cout << " / ";
            displayAsHex(subkeys[i], 48);
            cout << endl;
        }
    }

    return subkeys;
}
