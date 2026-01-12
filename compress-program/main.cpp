#include <iostream>
#include <fstream>
#include <string>
#include "HASH.H"


using namespace std;


int main() {

    //initializing the hash table
    HashTable<string, int> table(-1, 4096);

    //add all characters in alphabet to the hash table (first 256 entry)
    for (int i = 0; i <= 255; i++) {
        string s = "";
        s += char(i); // Convert int to string
        table.insert(s, i);
    }

    int next_code = 256;

    //handle file stream. Writes error messages, so I can check is there a problem here
    ifstream input("compin.txt");
    ofstream output("compout.txt");
    if (!input.is_open()) {
        cerr << "Error: Could not open compin" << endl;
        return 1;
    }
    if (!output.is_open()) {
        cerr << "Error: Could not create 'compout'" << endl;
        return 1;
    }

    char c_char;
    string p = "";

    //getting first entry
    if (input.get(c_char)) {
        p += c_char;
    }

    //as long as we have a next character, loop goes on
    while (input.get(c_char)) {
        string c = "";
        c += c_char;

        string combined = p + c;

        if (table.find(combined) != -1) {    //if this combination already exists in the table, use it
            p = combined;                    // we go on with this combination
        } else {
            output << table.find(p) << " ";  //if we can't find a longer combination, we write it to the file

            if (next_code < 4096) {                     //if we still have space in hash, insert newly found combination to the table
                table.insert(combined, next_code);
                next_code++;
            }
            p = c;                          //we move on with the next character
        }
    }

    if (p != "") {
       output << table.find(p) << " ";      //when while breaks, we still have a last one character to be written in
    }

    input.close();
    output.close();
    return 0;
}
