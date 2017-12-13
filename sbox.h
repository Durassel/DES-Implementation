#ifndef SBOX_H_INCLUDED
#define SBOX_H_INCLUDED

class Sbox
{
    private :
        char *input;
        char *output;
        // Display execution trace
        bool trace;
    public :
        Sbox(char tab[48]);
        virtual ~Sbox();
        void displayTrace(bool);
        char *generateOutput(void);
};

#endif // SBOX_H_INCLUDED
