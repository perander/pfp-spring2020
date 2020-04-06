#include <fstream>
#include <iostream>
#include <bits/stdc++.h> 

using namespace std;

// encodes one unsigned integer into vbyte
void encode(string fileName, unsigned int* array, int n) {
    ofstream outfile;
    outfile.open (fileName + ".sorted.vb", ios::out);

   for (int i = 0; i < n; i++) {
        cout << "start encoding ..." << endl;
        unsigned int integer = array[i];
        cout << "encoding " << integer << endl;
        while (true) {
            int byte = integer%128;
            if (integer < 128) {
                outfile << byte + 128 << endl;
                break;
            }
            outfile << byte << endl;
            integer = integer / 128;
        }
    }
}

void differences (string fileName) {
    int size = 8;

    fstream file (fileName, ios::in | ios::out | ios::binary);

    int n = sizeof(file);

    unsigned int found[n];

    if (file.is_open()) {
        for (int i = 0; i < n; i++) {
            file.read((char *) &found[i], size);
        }

        sort(found, found + n);

        unsigned int differences[n-1];

        for (int i = 1; i < n; ++i) {
            cout << found[i] << " - " << found[i-1] << " = " << found[i] - found[i-1] << endl;
            differences[i-1] = found[i] - found[i-1];
        }

        encode(fileName, differences, n-1);
    }
    else cout << "couldn't open\n";
}



int main (int argc, char** argv) {
    string fileName = argv[1]; //Fi

    ifstream file (fileName, ios::in | ios::binary);

    if (file.good() && sizeof(file) > 0) {
        differences(fileName);
    } else {
        cout << "file " << fileName << " is empty or doesn't exist" << endl;
    }
}