#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// decodes a file of vbyte integers back to decimal
void decode(string fileName) {
    fstream file (fileName, ios::in);

    ofstream outfile;
    outfile.open (fileName + ".dec", ios::out);

    while (!file.eof()) {
        cout << "start decoding ... " << endl;
        string line;
        int x = 0;
        int k = 1;
        while (getline(file, line)) {
            int byte = stoi(line, nullptr, 10);
            cout << byte << endl;
            if (byte < 128) x += byte*k;
            else {
                x += (byte-128)*k;
                outfile << x << endl;
                break;
            }
            k *= 128;
        }
    }
}

int main( int argc, char** argv ) {
    string fileName = argv[1]; //Fi.vb

    ifstream file (fileName, ios::in | ios::binary);

    if (file.good() && sizeof(file) > 0) {
        decode(fileName);
    } else {
        cout << "file " << fileName << " is empty or doesn't exist" << endl;
    }
}
