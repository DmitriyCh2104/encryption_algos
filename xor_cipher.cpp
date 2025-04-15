#include <iostream>
#include <string>
#include <cctype>

// Specific imports 
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::isprint;

// function to convert char to binary 
string toBinary(char c) {
    string binary = "";
    int ascii = (unsigned char)c; // get ascii value
    for (int i = 7; i >= 0; i--) { // build 8 bits
        binary += (ascii >> i & 1) ? "1" : "0";
    }
    return binary;
}

// Function to convert binary string to char
char fromBinary(string binary) {
    int ascii = 0;
    for (int i = 0; i < 8; i++) { // read 8 bits
        ascii = ascii * 2 + (binary[i] - '0');
    }
    return char(ascii);
}

// encryptation function *******
string xorCipher(string text, string key) {
    string result = ""; // store user text
    int keyIndex = 0;   // Track position in key

    for (int i = 0; i < text.length(); i++) {
        result += char(text[i] ^ key[keyIndex % key.length()]);
        keyIndex++; // move to next key char ***
    }
    return result;

}

// function for get key
string getKey() {
    string key;
    while (true) {
        cout << "Enter key (printable characters only): "; // user input
        getline(cin, key);

        bool isValid = true;
        if (key.empty()) { // verify if not empty
            isValid = false;
        }
        else {
            for (char c : key) {
                if (!isprint(c)) { // Verify if printable
                    isValid = false;
                    break;
                }
            }
        }

        if (isValid) {
            return key; // return key
        }
        else {
            cout << "Error, Key must contain printable characters and cannot be bellow empty." << endl;
        }
    }
}

// Function for input user message
string getText() {
    string text;
    cout << "Enter text: ";
    getline(cin, text);
    return text;
}

// function for input binary message
string getBinaryText() {
    string input;
    string text = "";
    cout << "Enter binary text (space-separated 8-bit strings): "; // user input
    getline(cin, input);

    if (input.empty()) {
        return text; // return empty if no input
    }

    string binary = "";
    for (int i = 0; i <= input.length(); i++) {
        if (i == input.length() || input[i] == ' ') {
            if (binary.length() == 8) { // verify 8 bits
                bool isValid = true;
                for (char c : binary) {
                    if (c != '0' && c != '1') { // check if 0 or 1
                        isValid = false;
                        break;
                    }
                }
                if (isValid) {
                    text += fromBinary(binary);
                }
            }
            binary = "";
        }
        else {
            binary += input[i];
        }
    }
    return text;
}

// function for show main menu
void showMenu() {
    cout << "\n-=Main menu=-" << endl;
    cout << "1. Encrypt" << endl;
    cout << "2. Decrypt" << endl;
    cout << "3. Exit" << endl;
    cout << "Choose action (1-3): ";
}

// main block ***************************************************
int main() {
    string choice;
    string text;
    string key;

    while (true) {
        showMenu(); // show menu
        getline(cin, choice); // read user choice from options

        if (choice == "1") {
            // encryptation
            text = getText();
            key = getKey();
            string encrypted = xorCipher(text, key);
            cout << "Encrypted text (binary): ";
            if (encrypted.empty()) {
                cout << "(none)";
            }
            else {
                for (int i = 0; i < encrypted.length(); i++) {
                    cout << toBinary(encrypted[i]);
                    if (i < encrypted.length() - 1) cout << " ";
                }
            }
            cout << endl; // user gets encrypted message
            cout << "Press enter to return to menu...";
            cin.get(); 
        }
        else if (choice == "2") {
            // Decryptation
            text = getBinaryText();
            key = getKey();
            string decrypted = xorCipher(text, key);
            cout << "Decrypted text: " << decrypted << endl; // user gets decrypted message
            cout << "Press enter to return to menu...";
            cin.get(); 
        }
        else if (choice == "3") {
            // exit 
            cout << "Program closing, good bye !" << endl;
            break;
        }
        else {
            // Wrong input handle
            cout << "Wrong input, enter a number (1-3) " << endl;
            cout << "Press enter to try again... " << endl;
            cin.get(); 
        }
    }

    return 0;
}