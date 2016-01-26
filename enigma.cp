/** Your Name: Aliisa Roe
 *  Assigment: HW 7 Extra Credit
 *  Date: 11/02/2015
 *  --------------------------------------------------------------------
 *  WINTERXISXCOMING encrypts to: GGFLLFIMPDZSNHYE
 *  The secret phrase is: EVERYTHINGXISXAWESOME
 **/
 
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
using namespace std;

//--------------------------------------------------------------------------------------
//method prototypes
//--------------------------------------------------------------------------------------
void spin_rotor(char (&rotor)[26]); // spins the rotor one time
void spin_rotor_n_times(int n, char (&rotor) [26]); //spins the rotor n times
string encrypt(string message); //encodes a message
int get_number(char c, char rotor [26]); //looks up the position of a letter on a rotor


//--------------------------------------------------------------------------------------
//Global variables BUT I THOUGHT WE DON'T USE GLOBAL VARIABLES??? MONSTER?!
//--------------------------------------------------------------------------------------
char base_rotor [26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

//the rotors we're using
char rotor_I [26] =     {'E','K','M','F','L','G','D','Q','V','Z','N','T','O','W','Y','H','X','U','S','P','A','I','B','R','C','J'};
char rotor_II [26] =    {'A','J','D','K','S','I','R','U','X','B','L','H','W','T','M','C','Q','G','Z','N','P','Y','F','V','O','E'};
char rotor_III  [26] =  {'B','D','F','H','J','L','C','P','R','T','X','V','Z','N','Y','E','I','W','G','A','K','M','U','S','Q','O'};

//the reflector we're using
char reflector_B [26] = {'Y','R','U','H','Q','S','L','D','P','X','N','G','O','K','M','I','E','B','F','Z','C','W','V','J','A','T'};
//--------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	string message;
	string messageAfterEnigma;
	string outputFileName = argv[5];
	
	string inputFileName = argv[4];
	ifstream messageFile;
	messageFile.open(inputFileName);
	if (messageFile.is_open()){ 
		getline(messageFile, message);
	}
	else { cout << "File read error" << endl; }
	messageFile.close();
	
	int rotor1Spin, rotor2Spin, rotor3Spin;
	rotor1Spin = atoi(argv[1]);
	rotor2Spin = atoi(argv[2]);
	rotor3Spin = atoi(argv[3]);
	
	spin_rotor_n_times(rotor1Spin, rotor_I);
	spin_rotor_n_times(rotor2Spin, rotor_II);
	spin_rotor_n_times(rotor3Spin, rotor_III);

	messageAfterEnigma = encrypt(message);
	cout << messageAfterEnigma << endl;
	
	ofstream newFile (outputFileName);
	newFile << messageAfterEnigma << endl;
		
}


//encodes a string based on current rotor positions
//returns the encoded version of the string
string encrypt(string message)
{
	string encrypted_message = "";
	char rotor3EncryptChar, rotor2EncryptChar, rotor1EncryptChar, reflectedEncryptChar;
	for ( int i = 0; i < message.length(); i++){
		rotor3EncryptChar = rotor_III[(int)message[i] - (int)'A'];
		rotor2EncryptChar = rotor_II[(int)rotor3EncryptChar - (int)'A'];
		rotor1EncryptChar = rotor_I[(int)rotor2EncryptChar - (int)'A'];
		
		reflectedEncryptChar = reflector_B[(int)rotor1EncryptChar - (int)'A'];
		
		rotor1EncryptChar = base_rotor[get_number(reflectedEncryptChar, rotor_I)];
		rotor2EncryptChar = base_rotor[get_number(rotor1EncryptChar, rotor_II)];
		rotor3EncryptChar = base_rotor[get_number(rotor2EncryptChar, rotor_III)];
		
		encrypted_message += rotor3EncryptChar;
		
		spin_rotor(rotor_I);
		if (rotor_I[0] == 'R'){
			spin_rotor(rotor_II);
		}
		if (rotor_II[0] == 'F') {
			spin_rotor(rotor_III);
		}
	}
	return encrypted_message;
}

/* helper function that finds the position of 
 * the character c on the given rotor
 */
int get_number(char c, char rotor[26])
{
	for ( int i = 0; i < 26; i++) {
		if (rotor[i] == c) {
			return i;
		}
	}
}

//spins the rotor once
void spin_rotor(char (&rotor)[26])
{
	char temp = rotor[25];
	for (int i = 25; i > 0; i--){
		rotor[i] = rotor[i-1];	
	}
	rotor[0] = temp;
}

//spins rotor many times
void spin_rotor_n_times(int n, char (&rotor) [26])
{
	for (int i = 0; i < n ; i ++) {
		spin_rotor(rotor);
	}
	
}
