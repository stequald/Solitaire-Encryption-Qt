Solitaire-Encryption-Qt
=======================

The Solitaire cryptographic algorithm was designed by Bruce Schneier "to allow field agents to communicate securely without having to rely on electronics or having to carry incriminating tools." The Solitaire algorithm can be done by hand using a deck of cards or even in your head. Solitaire is designed to be secure even if the enemy knows how the algorithm works. It offers real security, not security through obscurity. Your messages are safe as long as your password is secure enough (64 characters or more recommended) and that only those that are intended to read the messages know the order of the deck. It is is best not to use the same deck order too many times or for too long of a message (say a few thousand characters).

Solitaire gets its security from the inherent randomness in a shuffled deck of cards. By manipulating this deck, a communicant can create a string of "random" letters that he then combines with his message. Of course Solitaire can be simulated on a computer, but it is designed to be implemented by hand.

Although you can attached any number to any card, conventionally the numbers A-clubs through K-clubs is 1 through 13, A-diamonds through K-diamonds is 14 though 26, A-hearts through K-hearts is 27 through 39, A-spades through K-spades is 40 through 52, and the black joker and red joker is equal to 53 and 54 respectively.

Step 1 is to set the deck. You can do it manually or use a password to key the deck. Step 2 is to generate the key stream. Step 3 is then to encrypt or decrypt the message. The password, key stream, clear text, and cipher text can only be capitalize alphabetical characters.

It is best to use the solitaire encryption algorithm by hand or in your and head and to just use the app as a checker. Mistakes can easily be made when a person is doing it manually.


Run
=======================

Dependencies:

Qt
	
Run:

qmake
make
./SolitaireCipher
