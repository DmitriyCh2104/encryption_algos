#include <iostream>
#include <string>
#include <cctype> 

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::isalpha;
using std::isupper;  // reduce compiled size

// encryptation function *******
string caesarEncrypt(string text, int shift) {
    string result = "";     // store user text

    
    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) { // verify if is valid letter
            if (isupper(text[i])) { // transform capital letters
                result += char((text[i] + shift - 65) % 26 + 65);
            }
            else { // transform lowercase letters
                result += char((text[i] + shift - 97) % 26 + 97);
            }
        }
        else {
            result += text[i]; // if is digit : dont change
        }
    }
    return result;
}

// decryption function ***********
string caesarDecrypt(string text, int shift) {
    // use same function as for encryption but negative shift
    return caesarEncrypt(text, 26 - shift);
}

int getShift() {
    string input;
    int shift;
    while (true) {
        cout << "Enter shift (a positive integer between 1 and 26): ";   //user input 
        getline(cin, input); 

    
        bool isValid = true;
        if (input.empty()) { // verify if not empty
            isValid = false;
        }
        else {
            for (char c : input) {
                if (!isdigit(c)) { // verify if digit
                    isValid = false;
                    break;  
                }
            }
        }

        if (isValid) { // check if valid positive integer between 1 and 26
            shift = stoi(input); 
                if (shift >= 1 && shift <= 26) { 
                    return shift;  // return shift if within range
                }
        }
        else {
            cout << "Shift must be a number between 1 and 26 in digit format!" << endl; 
        } // user gets message about invalid input type 
    }
}

// function for input user message 
string getText() {
    string text;
    cout << "Enter text: ";
    getline(cin, text);
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
    int shift;

    while (true) {
        showMenu(); // show menu
        getline(cin, choice); // read user choice from options

        
        if (choice == "1") {
            // encryption
            text = getText(); 
            shift = getShift(); 
            string encrypted = caesarEncrypt(text, shift);
            cout << "Encrypted text: " << encrypted << endl; // user gets encrypted message
            cout << "Press enter to return to menu..."; 
            cin.get(); // wait 'enter' for return to menu
        }
        else if (choice == "2") {
            // decryption
            text = getText();
            shift = getShift();
            string decrypted = caesarDecrypt(text, shift);
            cout << "Decrypted text: " << decrypted << endl; // user gets decrypted message
            cout << "Press enter to return to menu...";
            cin.get(); // wait 'enter' for return to menu
        }
        else if (choice == "3") {
            // exit 
            cout << "Program closing, good bye !" << endl;
            break;
        }
        else {
            // wrong input handle
            cout << "Wrong input, enter a number (1-3) " << endl;
            cout << "Press enter to try again... " << endl;
            cin.get(); // wait 'enter' for return to menu
        }
    }

    return 0;
}