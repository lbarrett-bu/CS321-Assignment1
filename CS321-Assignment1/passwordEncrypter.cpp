#include "passwordEncrypter.h"

#include <stdlib.h>
#include <iostream>
//c++ string class
#include <string>

using namespace std;

int main() {
	string password;
	cout << "Please enter your password gamer: ";
	cin >> password;
	string en_passwd = crypt(password.c_str(), "22");
	cout << "the encrypted password is " << en_passwd << endl;
	return 1;
}