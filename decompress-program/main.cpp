#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


//since we will be taking integers as input we don't need to actually use the hash table again for
//converting it to integer again. It still uses O(1) time to reach array this way.
int main() {

    //using vector to be safe
    vector<string> table(4096);

    //we initialize alphabetic characters to the table
    for (int i = 0; i <= 255; i++) {
        string s = "";
        s += char(i);
        table[i] = s;
    }

    int next_code = 256; // next available slot in our array


    // handling file operations. If there is an error I can see in the file and understand it is due to file operations
    ifstream input("compout.txt");
    ofstream output("decompout.txt");

    if (!input.is_open()) {
        cerr << "Error: Could not open 'compout'" << endl;
        return 1;
    }
    if (!output.is_open()) {
        cerr << "Error: Could not create 'decompout'" << endl;
        return 1;
    }


    int old_code, new_code;

    // reading first entry
    if (!(input >> old_code)) {
        return 0;                           // file is empty
    }

    // write the first one
    output << table[old_code];

    // as long as we have another integer, loop moves on
    while (input >> new_code) {
        string s;

        if (new_code < next_code) {
            s = table[new_code];
        } else {
            s = table[old_code];
            s += s[0];                      // append the first character of itself
        }

        output << s;

        // add the new pattern to our vector
        // new Pattern = table[old] + (First Char of s)
        if (next_code < 4096) {
            string combined = table[old_code] + s[0];
            table[next_code] = combined;
            next_code++;
        }

        // we move on with the next character
        old_code = new_code;
    }

    input.close();
    output.close();

    return 0;
}

