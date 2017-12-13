#include <iostream>
#include "sbox.h"
#include "bit_tables.h"
#include "sboxes.h"
#include "sbox_helper.h"

using namespace std;

// Constructor
Sbox::Sbox(char tab[48])
{
    input = tab;
}

// Destructor
Sbox::~Sbox()
{
    // Free memory
    delete input;
    delete output;
}

void Sbox::displayTrace(bool value)
{
    trace = value;
}

char *Sbox::generateOutput(void)
{
    if (trace) {
        cout << "Input bit block : ";
        displayBitTable(input, 48);
        cout << endl;

        cout << "Sbox input   : ";
        displayBitTable(input, 48);
        cout << " / ";
        displayAsHex(input, 48);
        cout << endl;
    }

    output = new char [32];

    for (int i = 0; i < 8; i++) {
        int first = i * 6;
        int last = first + 5;

        char *endpoints;
        endpoints = new char [2];
        endpoints[0] = input[first];
        endpoints[1] = input[last];

        int row = generateIntFromBitBlock(endpoints, 2);
        int column = generateIntFromBitBlock(&input[first + 1], 4);
        int index = (row * 16) + column;

        char *tmp = generateBitBlockFromInt((int) s_boxes[i][index]);
        for (int j = 0; j < 4; j++)
            output[(i * 4) + j] = tmp[j];
    }

    if (trace) {
        cout << "Sbox output  : ";
        displayBitTable(output, 32);
        cout << " / ";
        displayAsHex(output, 32);
    }

    return output;
}
