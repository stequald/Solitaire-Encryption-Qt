#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <string>
#include <stdint.h>

using namespace std;

static const int MAXCARDS = 54;

class SolitaireCrypto {

public: 
	SolitaireCrypto();

    void setKeystream(string);
    void setCleartext(string); //only uppercase chars allowed
    void setCiphertext(string); //only uppercase chars allowed
    void setPasskey(string);

	string getKeystream();
	string getCleartext();
	string getCiphertext();
	string getPasskey();
	
	void resetDeck();
	string getDeck();

	void shuffle();
    void keygen(unsigned int);
	void solitaire();
	void keydeck();
	string encrypt();
	string decrypt();

    void on_keyDeck(string);
	void on_shuffle();
    string on_generateKeystream(unsigned int);
    string on_encrypt(string);
    string on_decrypt(string);
	
private: 
	void jo1shift();
	void jo2shift();
	void triplecut();
    void countcut(int);
    short output();

    short charCodeAt(char);
    char fromCharCode(short);
    void upperCaseString(string);

    short deck[MAXCARDS];
	string keystream;
	string cleartext;
	string ciphertext;
	string passkey;
};


