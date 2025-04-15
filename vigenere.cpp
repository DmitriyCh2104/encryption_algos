#include <iostream>
#include <string>
#include <cctype>

// Specific imports 
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::isalpha;
using std::isupper;
using std::tolower;

// encryptation function *******
string vigenereEncrypt(string text, string keyword) {
    string result = ""; // store user text
    int keyIndex = 0;   // Track position in keyword

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) { // verify if is valid letter
            // get shift from keyword letter
            char keyChar = tolower(keyword[keyIndex % keyword.length()]);
            int shift = keyChar - 97;

            if (isupper(text[i])) { // transform capital letters
                result += char((text[i] + shift - 65) % 26 + 65);
            }
            else { // transform lowercase letters
                result += char((text[i] + shift - 97) % 26 + 97);
            }
            keyIndex++; // move to next keyword letter 
        }
        else {
            result += text[i]; // if is digit : dont change
        }
    }
    return result;
}

// Decryption function ***********
string vigenereDecrypt(string text, string keyword) {
    string result = ""; // Store user text
    int keyIndex = 0;   // Track position in keyword

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) { // Verify if is valid letter
            // Get shift from keyword letter
            char keyChar = tolower(keyword[keyIndex % keyword.length()]);
            int shift = keyChar - 97;

            if (isupper(text[i])) { // Transform capital letters
                result += char((text[i] - shift - 65 + 26) % 26 + 65);
            }
            else { // Transform lowercase letters
                result += char((text[i] - shift - 97 + 26) % 26 + 97);
            }
            keyIndex++; // Move to next keyword letter
        }
        else {
            result += text[i]; // If is digit : dont change
        }
    }
    return result;
}

// function for get keyword
string getKeyword() {
    string keyword;
    while (true) {
        cout << "Enter keyword (letters only): "; // user input
        getline(cin, keyword);

        bool isValid = true;
        if (keyword.empty()) { // verify if not empty
            isValid = false;
        }
        else {
            for (char c : keyword) {
                if (!isalpha(c)) { // Verify if letter
                    isValid = false;
                    break;
                }
            }
        }

        if (isValid) {
            return keyword; // return keyword if OK
        }
        else {
            cout << "Error! Keyword must contain only letters and cannot be bellow empty." << endl;
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

// Function for show main menu
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
    string keyword;

    while (true) {
        showMenu();    
        getline(cin, choice); // read user choice from options

        if (choice == "1") {
            // encryptation
            text = getText();
            keyword = getKeyword();
            string encrypted = vigenereEncrypt(text, keyword);
            cout << "Encrypted text: " << encrypted << endl; // user gets encrypted message
            cout << "Press enter to return to menu...";
            cin.get();
        }
        else if (choice == "2") {
            // Decryptation
            text = getText();
            keyword = getKeyword();
            string decrypted = vigenereDecrypt(text, keyword);
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