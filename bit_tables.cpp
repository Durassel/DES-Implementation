#include <iostream>

using namespace std;

char *convertHexToBin(char character)
{
    switch(character) {
        case '0':
            return (char *) "0000";
        case '1':
            return (char *) "0001";
        case '2':
            return (char *) "0010";
        case '3':
            return (char *) "0011";
        case '4':
            return (char *) "0100";
        case '5':
            return (char *) "0101";
        case '6':
            return (char *) "0110";
        case '7':
            return (char *) "0111";
        case '8':
            return (char *) "1000";
        case '9':
            return (char *) "1001";
        case 'A':
            return (char *) "1010";
        case 'B':
            return (char *) "1011";
        case 'C':
            return (char *) "1100";
        case 'D':
            return (char *) "1101";
        case 'E':
            return (char *) "1110";
        case 'F':
            return (char *) "1111";
        default:
            return (char *) "";
    }
}

char* permute(char *table, char *perm_table, long tabsize)
{
    char *result = new char[tabsize];

    for (int i = 0; i < tabsize; i++)
        result[i] = table[(int) perm_table[i] - 1];

    return result;
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
