#include "solitairecrypto.h"
#include <algorithm>
#include <sstream>      // std::ostringstream

SolitaireCrypto::SolitaireCrypto() {
    // initialize random seed:
	srand (time(NULL));
	resetDeck();
	keystream.assign("");
	cleartext.assign("");
	ciphertext.assign("");
	passkey.assign("");
}


void SolitaireCrypto::setKeystream(string str) {
	upperCaseString(str);
	keystream.assign(str);
}

void SolitaireCrypto::setCleartext(string str) {
	upperCaseString(str);
	cleartext.assign(str);
}

void SolitaireCrypto::setCiphertext(string str) {
	upperCaseString(str);
	ciphertext.assign(str);
}

void SolitaireCrypto::setPasskey(string str) {
	upperCaseString(str);
	passkey.assign(str);
}

string SolitaireCrypto::getKeystream() {
	return keystream;
}

string SolitaireCrypto::getCleartext() {
	return cleartext;
}

string SolitaireCrypto::getCiphertext() {
	return ciphertext;
}

string SolitaireCrypto::getPasskey() {
	return passkey;
}
	
void SolitaireCrypto::resetDeck() {
    for(uint8_t i=0;i<MAXCARDS;i++) {deck[i]=i+1;}
}

string SolitaireCrypto::getDeck() {
	ostringstream oss("");
    for (uint8_t i = 0; i < MAXCARDS; i++) {
        oss << deck[i];
		oss << " ";
	}
	return oss.str();
}
	
void SolitaireCrypto::upperCaseString(string str) {
	std::transform(str.begin(), str.end(),str.begin(), ::toupper);
}

void SolitaireCrypto::shuffle() {
    random_shuffle(&deck[0], &deck[MAXCARDS]);
}

void SolitaireCrypto::jo1shift() {
    uint8_t jo1pos=0;
    short stor[2];

	for(uint8_t i=0;deck[i]!=53;i++) {jo1pos=i+1;}
	
	if(jo1pos==53) {
		stor[0]=deck[0];
		stor[1]=deck[0];
        for(uint8_t i=1;i<MAXCARDS;i++) {
			stor[i%2]=deck[i];
			deck[i]=stor[(i+1)%2];
		}
		deck[0]=53;
	}
	if(jo1pos!=53) {
		stor[0]=deck[jo1pos+1];
		deck[jo1pos+1]=53;
		deck[jo1pos]=stor[0];
	}
}

void SolitaireCrypto::jo2shift() {
    uint8_t jo2pos=0;
    short stor[2];

    for(uint8_t i=0;deck[i]!=MAXCARDS;i++) {jo2pos=i+1;}

	if(jo2pos==52) {
		stor[0]=deck[jo2pos-52];
		stor[1]=deck[jo2pos-52];
		for(uint8_t i=(jo2pos-51);i<53;i++) {
			stor[i%2]=deck[i];
			deck[i]=stor[(i+1)%2];
		}
        deck[jo2pos-51]=MAXCARDS;
	}

	if(jo2pos==53) {
		stor[0]=deck[jo2pos-52];
		stor[1]=deck[jo2pos-52];
        for(uint8_t i=(jo2pos-51);i<MAXCARDS;i++) {
			stor[i%2]=deck[i];
			deck[i]=stor[(i+1)%2];
		}
        deck[jo2pos-51]=MAXCARDS;
	}
	if(jo2pos<52) {
		stor[0]=deck[jo2pos+1];
		stor[1]=deck[jo2pos+2];
        deck[jo2pos+2]=MAXCARDS;
		deck[jo2pos]=stor[0];
		deck[jo2pos+1]=stor[1];
	}
}

void SolitaireCrypto::triplecut() {
    uint8_t jo1pos=0;
    uint8_t jo2pos=0;
	
	for(uint8_t i=0;deck[i]!=53;i++) {jo1pos=i+1;}
    for(uint8_t i=0;deck[i]!=MAXCARDS;i++) {jo2pos=i+1;}

	if(jo1pos<jo2pos) {
        vector<short> topdeck(jo1pos);
        vector<short> bottomdeck(53-jo2pos);
        vector<short> middeck(jo2pos-jo1pos+1);

		for(uint8_t i=0;i<jo1pos;i++) {topdeck[i]=deck[i];}
		for(uint8_t i=0;i<(jo2pos-jo1pos+1);i++) {middeck[i]=deck[i+jo1pos];}
		for(uint8_t i=0;i<(53-jo2pos);i++) {bottomdeck[i]=deck[i+jo2pos+1];}
		for(uint8_t i=0;i<(bottomdeck.size());i++) {deck[i]=bottomdeck[i];}
		for(uint8_t i=0;i<(middeck.size());i++) {deck[i+bottomdeck.size()]=middeck[i];}
		for(uint8_t i=0;i<(topdeck.size());i++) {deck[i+bottomdeck.size()+middeck.size()]=topdeck[i];}
	}

	if(jo2pos<jo1pos) {
        vector<short> topdeck(jo2pos);
        vector<short> bottomdeck(53-jo1pos);
        vector<short> middeck(jo1pos-jo2pos+1);

		for(uint8_t i=0;i<jo2pos;i++) {topdeck[i]=deck[i];}
		for(uint8_t i=0;i<(jo1pos-jo2pos+1);i++) {middeck[i]=deck[i+jo2pos];}
		for(uint8_t i=0;i<(53-jo1pos);i++) {bottomdeck[i]=deck[i+jo1pos+1];}
		for(uint8_t i=0;i<(bottomdeck.size());i++) {deck[i]=bottomdeck[i];}
		for(uint8_t i=0;i<(middeck.size());i++) {deck[i+bottomdeck.size()]=middeck[i];}
		for(uint8_t i=0;i<(topdeck.size());i++) {deck[i+bottomdeck.size()+middeck.size()]=topdeck[i];}
	}
}

void SolitaireCrypto::countcut(int count) {

    if(count==MAXCARDS) {count=53;}
    vector<short> topdeck(count);
    vector<short> bottomdeck(53-count);

	for(uint8_t i=0;i<topdeck.size();i++) {topdeck[i]=deck[i];}
	for(uint8_t i=0;i<bottomdeck.size();i++) {bottomdeck[i]=deck[i+count];}
	for(uint8_t i=0;i<bottomdeck.size();i++) {deck[i]=bottomdeck[i];}
	for(uint8_t i=0;i<topdeck.size();i++) {deck[i+bottomdeck.size()]=topdeck[i];}
}

short SolitaireCrypto::output() {
    short index=deck[0];
    if(index==MAXCARDS) {index=53;}
    return deck[index];
}

void SolitaireCrypto::solitaire() {
    jo1shift();
    jo2shift();
    triplecut();
    countcut(deck[53]);
}

short SolitaireCrypto::charCodeAt(char c) {
    return short(c);
}
char SolitaireCrypto::fromCharCode(short i) {
	return char(i);
}


void SolitaireCrypto::keydeck() {
	resetDeck();
	for(uint8_t i=0;i<passkey.length();i++) {
		solitaire();
		countcut(charCodeAt(passkey[i])-64);
	}
}

void SolitaireCrypto::keygen(unsigned int msgLen) {
	keystream.assign("");
	for(unsigned int k=0; k< msgLen; k++) {
        solitaire();
		if(output()<53) {
			keystream += fromCharCode(((output()-1)%26)+65);
		}
		if(output()>=53) {
			k--;
		}
	}
}

string SolitaireCrypto::encrypt() {
	if (keystream.length() != cleartext.length()) {
        ciphertext.assign("");
        return "";
	}

	string output("");
	char keywork;
	char clearwork;
	char outwork;

    for(unsigned int i=0; i<keystream.length(); i++) {

        keywork=charCodeAt(keystream[i]);
		keywork=(keywork-64)%26;
		clearwork=charCodeAt(cleartext[i]);
		if(clearwork>=65&&clearwork<=90) {clearwork=(clearwork-64)%26;}
		if(clearwork>=97&&clearwork<=122) {clearwork=(clearwork-96)%26;}
		outwork=(clearwork+keywork)%26;
		outwork=outwork+64;
		if(outwork==64) {outwork=90;}
		output += fromCharCode(outwork);
	}

    ciphertext.assign(output);
    return output;
}


string SolitaireCrypto::decrypt() {
    if (keystream.length() != ciphertext.length()) {
        cleartext.assign("");
        return "";
    }

	string output("");
	char keywork;
	char cipherwork;
	char outwork;		

    for(unsigned int i=0; i<keystream.length(); i++) {
        keywork=charCodeAt(keystream[i]);
		keywork=(keywork-64)%26;
		cipherwork=charCodeAt(ciphertext[i]);
		cipherwork=(cipherwork-64)%26;
		outwork=(cipherwork-keywork)%26;
		if(outwork<0) {outwork=26+outwork;}
		outwork=outwork+64;
		if(outwork==64) {outwork=90;}
		output += fromCharCode(outwork);
	}
    cleartext.assign(output);
	return output;
}


void SolitaireCrypto::on_keyDeck(string passkey) {
	this->setPasskey(passkey);
	this->keydeck();
    cout << "deck:" << endl << this->getDeck() << endl;
}

void SolitaireCrypto::on_shuffle() {
	this->shuffle();
    cout << "deck:" << endl << this->getDeck() << endl;
}

string SolitaireCrypto::on_generateKeystream(unsigned int msgLen) {
	this->keygen(msgLen);
    cout << "generateKeystream from current deck. keystream:" << endl << this->getKeystream() << endl;
    return this->getKeystream();
}

string SolitaireCrypto::on_encrypt(string clearText) {
	this->setCleartext(clearText);
	this->encrypt();
    cout << "ciphertext:" << endl << this->getCiphertext() << endl;
    return this->getCiphertext();
}

string SolitaireCrypto::on_decrypt(string cipherText) {	
	this->setCiphertext(cipherText);
	this->decrypt();
    cout << "clearText:" << endl << this->getCleartext() << endl;
    return this->getCleartext();
}



