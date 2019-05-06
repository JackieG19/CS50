# Problem Set 2

### Caesar

Supposedly, Caesar (yes, that Caesar) used to "encrypt" (i.e., conceal in a reversible way) confidential messages by shifting 
each letter therein by some number of places. For instance, he might write A as B, B as C, C as D, …​, and, wrapping around 
alphabetically, Z as A. And so, to say HELLO to someone, Caesar might write IFMMP. Upon receiving such messages from Caesar, 
recipients would have to "decrypt" them by shifting letters in the opposite direction by the same number of places.
The secrecy of this "cryptosystem" relied on only Caesar and the recipients knowing a secret, the number of places by which 
Caesar had shifted his letters (e.g., 1). Not particularly secure by modern standards, but, hey, if you’re perhaps the first 
in the world to do it, pretty secure!

### Vigenère

Vigenère’s cipher improves upon Caesar’s cipher by encrypting messages using a sequence of keys (or, put another way, a keyword). 
In other words, if p is some plaintext and k is a keyword (i.e., an alphbetical string, whereby A represents 0, B represents 1,
C represents 2, …​, and Z represents 25), then each letter, ci, in the ciphertext, c, is computed as:

 ci = (pi+kj) mod 26
 
Note this cipher’s use of kj as opposed to just k. And if k is shorter than p, then the letters in k must be reused cyclically 
as many times as it takes to encrypt p. In other words, if Vigenère himself wanted to say HELLO to someone confidentially, 
using a keyword of, say, ABC, he would encrypt the H with a key of 0 (i.e., A), the E with a key of 1 (i.e., B), and the first 
L with a key of 2 (i.e., C), at which point he’d be out of letters in the keyword, and so he’d reuse (part of) it to encrypt 
the second L with a key of 0 (i.e., A) again, and the O with a key of 1 (i.e., B) again. And so he’d write HELLO as HFNLP.


### Crack

On most systems running Linux these days is a file called /etc/shadow, which contains usernames and passwords. 
Fortunately, the passwords therein aren’t stored "in the clear" but are instead encrypted using a "one-way hash function." 
When a user logs into these systems by typing a username and password, the latter is encrypted with the very same hash function,
and the result is compared against the username’s entry in /etc/shadow. If the two hashes match, the user is allowed in. 
If you’ve ever forgotten some password, you might have been told that tech support can’t look up your password but can change 
it for you. Odds are that’s because tech support can only see, if anything at all, a hash of your password, not your password 
itself. But they can create a new hash for you.

Even though passwords in /etc/shadow are hashed, the hash function is not always that strong. Quite often are adversaries, 
upon obtaining that file somehow, able to guess (and check) users' passwords or crack them using brute force (i.e., trying all
possible passwords). Below is what /etc/shadow might look like, albeit simplified, wherein each line is formatted as 
username:hash.
