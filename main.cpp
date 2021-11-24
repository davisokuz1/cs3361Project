#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <sstream>

using namespace std;


int main() {

    char dfa[100];
    string hold[50];
    int A = 0;

    string dfa_outcome[100];
    string placeholder = "CS3361";
    string counter = "";

    int x = 0;
    int y = 0;
    int Current_State = 0;
    string NOF;  // Name of file
    bool error_A = false;

    ofstream file_B;
    ifstream file_A;

    /*This will prompt the user for the file must be exact path name e.g."C:\Users\okuda\Documents\testing1.txt"*/
    cout << "What file is to open?" << endl;
    cin >> NOF;

    file_A.open(NOF);
    file_B.open("THE OUTPUT");// Will output in system directory just search for it


    if (file_A.is_open()) {
        while (file_A.get(dfa[x]))   //Scan info from file into dfa
        {
            x++;
        }
        file_A.close();
    } else file_B << "Error: File Can't open";
    {
    }


    for (int j = 0; j < x; j++)  //Create the Loop for DFA
    {
        if (dfa[j] == ' ' || dfa[j] == '\t' || dfa[j] == '\n') {
            Current_State = 1;
        }

        /*
         * If there ia a '/' we start at the next object in the array. If anything else ignore
         */
        if (dfa[j] == '/') {
            dfa_outcome[y] = "multiplication";
            Current_State = 2;
            hold[A] = dfa[y];
            A++;
            x++;
        }
        if (dfa[j] == ')') {   //Search For: )
            Current_State = 7;
            dfa_outcome[y] = "Rparen";
            hold[A] = dfa[j];
            A++;
            x++;
        }
        if (dfa[j] == '(') {  //Search For: (
            Current_State = 6;
            dfa_outcome[x] = "Lparen";
            hold[A] = dfa[j];
            A++;
        }
        if (dfa[j] == '-') {  //Search For: -
            Current_State = 9;
            dfa_outcome[x] = "subtraction";
            hold[A] = dfa[j];
            A++;
            x++;
        }
        if (dfa[j] == '+') {  //Search For: +
            Current_State = 8;
            dfa_outcome[x] = "addition";
            hold[A] = dfa[j];
            A++;
            x++;
        }
        if (dfa[j] == '*') {  //Search For: *
            Current_State = 10;
            dfa_outcome[x] = "multiplication";
            hold[A] = dfa[j];
            A++;
            x++;
        }
        if (dfa[j] == '.') {  //Search For: .
            Current_State = 13;
        }

        //Reassures decimal numbers e.g 5.5, 5.6
        if (isdigit(dfa[j]) || dfa[j] == '.') {
            dfa_outcome[y] = "number";
            Current_State = 14;
            stringstream ss;
            hold[A] = dfa[j];
            A++;
            x++;
        }
        if (j < x && isalpha(dfa[j + 1]))  //Checks for peaks in letter and next value is a char or int
        {
            while (isdigit(dfa[j]))
                Current_State = 16;
            j++;
            if (j >= x) {
                break;
            }
        }
        if (j < x && isalpha(dfa[j])) {
            while (isdigit(dfa[j + 1]) || isalpha(dfa[j + 1])) {
                Current_State = 16;
                j++;
                if (j >= x) {
                    break;
                }
            }
            if (dfa[j - 3] == 'r' && dfa[j - 2] == 'e' && dfa[j - 1] == 'a' && dfa[j] == 'd') {
                dfa_outcome[y] = "read";
                hold[A] = "read";
                A++;
                y++;
            } else if (dfa[j - 4] == 'w' && dfa[j - 3] == 'r' && dfa[j - 2] == 'i' && dfa[j - 1] == 't' &&
                       dfa[j] == 'e') {
                dfa_outcome[y] = "write";
                hold[A] = "write";
                A++;
                y++;
            } else {
                dfa_outcome[y] = "Id";
                hold[A] = dfa[j];
                A++;
                y++;

            }

            if (dfa[j] == ':' && dfa[j + 1] == '=') { // Checks for =
                Current_State = 11;
                dfa_outcome[y] = "Assign";
                hold[A] = ":=";
                A++;
                y++;

            }
            if (dfa[j] == ' ' || dfa[j] == '\n') {

            }


            //Look to see if other tokens are inside the file besides the one losted.
            //If there is one then return an error.
            if (j < x) {
                if (dfa[j] != '.' && !isdigit(dfa[j]) && !isalpha(dfa[j])
                    && dfa[j] != '*' && dfa[j] != '/' && dfa[j] != '-' && dfa[j] != '+' && dfa[j] !=
                                                                                           '(' && dfa[j] != ')' &&
                    dfa[j] != ':' && dfa[j] != '=' && dfa[j] != ' ' && dfa[j] !=
                                                                       '\n' && dfa[j] != '\t' && dfa[j] != '\r') {
                    file_B << "Theres's a token that shouldn't be there." << endl;
                    error_A = true;
                    break;
                }
            }
        }

    }
    file_B << "\t <Program> " << endl;
    file_B << " \t \t <stmt_list>" << endl;
    file_B << " \t \t \t <stmt>" << endl;

    int j = 0;

/*
 * This is the Loop that does the parsing. Not sure how to do indents
 */
    if (dfa_outcome[j] == "read" || dfa_outcome[j] == "Id" || dfa_outcome[j] == "write") {
        for (j = 0; j < x; j++) {

            if (dfa_outcome[j] == "read") {
                file_B << "\t \t \t \t <read>" << endl;
                file_B << "\t \t \t \t \t " << hold[j] << endl;
                file_B << "\t \t \t \t </read>" << endl;
            }
            if (dfa_outcome[j] == "Id" && dfa_outcome[j + 1] == "Assign") {
                file_B << "\t \t \t \t <id>" << endl;
                file_B << "\t \t \t \t \t " << hold[j] << endl;
                file_B << "\t \t \t \t </id>" << endl;
                j++;
                file_B << "\t \t \t \t <Assign>" << endl;
                file_B << "\t \t \t \t \t " << hold[j] << endl;
                file_B << "\t \t \t \t </Assign>" << endl;
            }
            if (dfa_outcome[j] == "write") {
                file_B << "\t \t \t \t <read>" << endl;
                file_B << "\t \t \t \t \t " << hold[j] << endl;
                file_B << "\t \t \t \t </read>" << endl;

            }
            if (dfa_outcome[j] == "Lparen") {
                file_B << "\t \t \t \t <Lparen>" << endl;
                file_B << "\t \t \t \t \t " << hold[j] << endl;
                file_B << "\t \t \t \t </Lparen>" << endl;
            }
            if (dfa_outcome[j] == "Rparen") {
                file_B << "\t \t \t \t <rparen>" << endl;
                file_B << "\t \t \t \t \t " << hold[j] << endl;
                file_B << "\t \t \t \t </rparen>" << endl;
            }
            if (dfa_outcome[j] == "Id" && dfa_outcome[j + 1] != "Assign") {
                file_B << "\t \t \t \t <id>" << endl;
                file_B << "\t \t \t \t \t " << hold[j] << endl;
                file_B << "\t \t \t \t </id>" << endl;
            }
            if (dfa_outcome[j] == "addition_op") {
                file_B << "\t \t \t \t <addition_op>" << endl;
                file_B << "\t \t \t \t \t " << hold[j] << endl;
                file_B << "\t \t \t \t </addition_op>" << endl;
            }
            if (dfa_outcome[j] == "number") {
                file_B << "\t \t \t \t <Number>" << endl;
                file_B << "\t \t \t \t \t " << hold[j] << endl;;
                file_B << "\t \t \t \t </Number>" << endl;
            }
            if (dfa_outcome[j] == "mult_op") {
                file_B << "\t \t \t \t <addition_op>" << endl;
                file_B << "\t \t \t \t \t " << hold[j] << endl;
                file_B << "\t \t \t \t </addition_op>" << endl;
            }
        }
    }
    file_B << " \t \t \t </stmt>" << endl;
    file_B << " \t \t </stmt_list>" << endl;
    file_B << "\t </Program> " << endl;
    return 0;
}

