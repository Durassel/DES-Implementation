#ifndef DES_H_INCLUDED
#define DES_H_INCLUDED

class Des
{
    private :
        // User
        char *message;      // Message to encrypt
        char *key;          // Secret key to encrypt
        // DES Implementation
        char **subkeys;     // subkeys
        char **L;           // Left
        char **R;           // Right
        char *initial;      // first permutation
        char *expansion;    // expansion
        char *firstXor;     // First XOR between key and expansion
        char *sbox;         // Sbox
        char *perm;         // permut_32
        char *lastXor;      // Lasr XOR between L and perm
        char *join;         // Joining R[16] and L[16]
        char *revers;       // Reverse permutation
        // Display execution trace
        bool trace;
    public :
        Des(char message[64], char key[64]);
        virtual ~Des();
        void displayTrace(bool);
        char* split(char *, long, long, long);
        void encryption(void);
        void print(void);
};

#endif // DES_H_INCLUDED
