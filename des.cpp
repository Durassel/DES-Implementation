#include <iostream>
#include "des.h"
#include "subkey.h"
#include "sbox.h"
#include "bit_tables.h"
#include "data_tables.h"
#include "expansion.h"

using namespace std;

// Constructor
Des::Des(char message[], char key[])
{
    // Initialization
    this->message = message;
    this->key = key;
}

// Destructor
Des::~Des()
{
    // Free memory
    delete message;
    delete key;
    delete initial;
    delete expansion;
    delete firstXor;
    delete sbox;
    delete perm;
    delete lastXor;
    delete join;
    delete revers;

    for (int i = 0; i < 16; i++)
        delete subkeys[i];
    delete subkeys;

    for (int i = 0; i < 17; i++)
        delete L[i];
    delete L;

    for (int i = 0; i < 17; i++)
        delete R[i];
    delete R;
}

void Des::displayTrace(bool value)
{
    trace = value;
}

char* Des::split(char *table, long tabsize, long start, long endT)
{
    char *result = new char[tabsize / 2];

    for(int i = start; i < endT; i++) {
        if (start > 0)
            result[i - start] = table[i];
        else
            result[i] = table[i];
    }

    return result;
}

void Des::encryption(void)
{
    // Subkeys generation
    Subkey *sk = new Subkey(key);
    sk->displayTrace(true);
    subkeys = sk->generateSubkeys();

    if (trace) {
        cout << endl << endl << "SUBKEYS : " << endl;
        for (int i = 0; i < 16; i++) {
            displayBitTable(subkeys[i], 48);
            cout << " / ";
            displayAsHex(subkeys[i], 48);
            cout << endl;
        }
    }

    // Initial permutation
    initial = permute(message, init_perm, 64);

    // Split initial in 2 parts
    L = new char* [17];
    R = new char* [17];
    L[0] = split(initial, 64, 0, 32);
    R[0] = split(initial, 64, 32, 64);

    // 16 rounds
    for (int i = 0; i < 16; i++) {
        expansion = permute(R[i], expansion_table, 48);

        if (trace) {
            cout << endl << "ROUND " << i + 1 << endl;
            cout << "L" << i << " : ";
            displayBitTable(L[i], 32);
            cout << " / ";
            displayAsHex(L[i], 32);
            cout << endl << "R" << i << " : ";
            displayBitTable(R[i], 32);
            cout << " / ";
            displayAsHex(R[i], 32);

            cout << endl << "Expansion    : ";
            displayBitTable(expansion, 48);
            cout << " / ";
            displayAsHex(expansion, 48);

            cout << endl << "Used subkey  : ";
            displayBitTable(subkeys[i], 48);
            cout << " / ";
            displayAsHex(subkeys[i], 48);
        }

        firstXor = new char [48];
        for (int j = 0; j < 48; j++)
            firstXor[j] = (char)(subkeys[i][j] ^ expansion[j]);

        if (trace) {
            cout << endl << "Xor output   : ";
            displayBitTable(firstXor, 48);
            cout << " / ";
            displayAsHex(firstXor, 48);

            cout << endl << "SBOX debug :" << endl;
        }

        Sbox *sb = new Sbox(firstXor);
        sb->displayTrace(trace);
        sbox = sb->generateOutput();

        perm = permute(sbox, permut_32, 32);

        if (trace) {
            cout << endl << "After perm32 : ";
            displayBitTable(perm, 32);
            cout << " / ";
            displayAsHex(perm, 32);
        }

        lastXor = new char [32];
        for (int j = 0; j < 32; j++)
            lastXor[j] = (char)(L[i][j] ^ perm[j]);

        if (trace) {
            cout << endl << "Xor output   : ";
            displayBitTable(lastXor, 32);
            cout << " / ";
            displayAsHex(lastXor, 32);
        }

        L[i + 1] = R[i];
        R[i + 1] = lastXor;

        if (trace)
            cout << endl;
    }

    // End of DES
    join = new char [64];

    for (int i = 0; i < 32; i++) {
        join[i] = R[16][i];
        join[i + 32] = L[16][i];
    }

    revers = permute(join, reverse_perm, 64);

    if (trace) {
        cout << "Joining R16+L16 : ";
        displayBitTable(join, 64);
        cout << " / ";
        displayAsHex(join, 64);
    }
}

void Des::print(void)
{
    cout << endl << endl << "Encrypted message : " << endl;
    displayBitTable(revers, 64);
    cout << endl;
    displayAsHex(revers, 64);
    cout << endl;
}
