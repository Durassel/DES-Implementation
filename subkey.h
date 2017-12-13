#ifndef SUBKEY_H_INCLUDED
#define SUBKEY_H_INCLUDED

class Subkey
{
    private :
        char *key;          // Display execution trace
        char *L;            // Left
        char *R;            // Right
        char **subkeys;     // Subkeys generated
        // Display execution trace
        bool trace;
    public :
        Subkey(char key[64]);
        virtual ~Subkey();
        void displayTrace(bool);
        char *leftShift(char *, long, long);
        char *concatenation(char *, char *, long);
        char **generateSubkeys();
};

#endif // SUBKEY_H_INCLUDED
