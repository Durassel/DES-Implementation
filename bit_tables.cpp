#include <iostream>

using namespace std;

char *convertHexToBin(char character)
{
    switch(character) {
        case '0':
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'A':
            return "1010";
        case 'B':
            return "1011";
        case 'C':
            return "1100";
        case 'D':
            return "1101";
        case 'E':
            return "1110";
        case 'F':
            return "1111";
    }
}

void displayBitTable(char *table, long tabsize)
{
    for (long i = 0; i < tabsize; i++) {
        cout << (int) table[i];

        if (((i + 1) % 4) == 0)
            cout << " ";
    }
}

void displayAsHex(char *table, long tabsize)
{
   long hexsize = tabsize / 4;

   char hexcodes[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

   for (long i = 0; i < hexsize; i++) {
       long value = 0;

       for (long j = 0; j < 4; j++)
            value = (2 * value) + table[4 * i + j];

       cout << hexcodes[value];

        if (((i + 1) % 4) == 0)
            cout << " ";
   }
}
