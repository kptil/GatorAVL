// GatorAVL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include "TreeNode.h"
#include "AVLTree.h"

using namespace std;

/* Takes a string as input and returns true if it contains only uppercase letters (ascii 65-90), lowercase
   letters (ascii 97-122) or the space character (32). */
bool testName(string name) {
    bool valid;
    for (int i = 0; i < name.length(); i++) {
        int ascii = int(name[i]);
        valid = (ascii == 32) || (ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122);
        if (!valid) { return false; }
    }
    return true;
}

// Takes a string as input and return true only if it contains exactly 8 numeric digits.
bool testID(string ID) {
    if (ID.length() != 8) { return false; }
    else {
        for (int i = 0; i < ID.length(); i++) {
            if (!isdigit(ID[i])) { return false; }
        }
        return true;
    }
}

int main()
{
    // The tree is constructed and the number of commands is read in.
    AVLTree tree;
    int numCommands = 0;
    cin >> numCommands;

    // Reads in the name of each command and calls the appropriate functions.
    string command = "";
    for (int i = 0; i < numCommands; i++) {
        cin >> command;
        if (command == "insert") {
            // Gets input for name and ID arguments into strings.
            string name = "";
            string studID = "";
            getline(cin, name, '"'); // discards up to and including first "
            getline(cin, name, '"'); // gets what's within ""
            getline(cin, studID);

            studID = studID.substr(1); // removes the single leading space

            // Calls test functions to ensure data constraints are met befor calling insert.
            if (testID(studID) && testName(name)) {
                int ID = stoi(studID);
                if (tree.insert(ID, name)) {
                    cout << "successful" << endl;
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        if (command == "search") {
            string searchToken = "";
            getline(cin, searchToken);

            /* If the first non-space character is a digit, process searchToken as an ID. If not, procces it
               as a name. An invalid ID or name will cause unsuccessful to print. */
            if (isdigit(searchToken[1])) {
                // Transform into char pointer, then integer, excluding the leading space.
                char* ID = &(searchToken[1]);
                TreeNode* result = tree.search(stoi(ID));
                if (result == nullptr) {
                    cout << "unsuccessful" << endl;
                }
                else {
                    cout << result->name << endl;
                }
            }
            else {
                // Subset to remove initial space and quotation marks.
                searchToken = searchToken.substr(2);
                searchToken.pop_back();
                vector<TreeNode*> results = tree.search(searchToken);
                if (results.size() == 0) {
                    cout << "unsuccessful" << endl;
                }
                else {
                    for (int i = 0; i < results.size(); i++) {
                        cout << results[i]->studentID << endl;
                    }
                }
            }
        }
        // Remove unsuccessful if ID invalid or does not exist in tree.
        if (command == "remove") {
            int ID = 0;
            cin >> ID;
            if (tree.remove(ID)) {
                cout << "successful" << endl;
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        // Remove unsuccessful if the tree has less than n nodes.
        if (command == "removeInorder") {
            int n = 0;
            cin >> n;
            if (tree.removeInOrder(n)) {
                cout << "successful" << endl;
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        if (command == "printInorder") {
            tree.printInOrder();
        }
        if (command == "printPreorder") {
            tree.printPreOrder();
        }
        if (command == "printPostorder") {
            tree.printPostOrder();
        }
        if (command == "printLevelCount") {
            tree.printLevelCount();
        }
    }
}

