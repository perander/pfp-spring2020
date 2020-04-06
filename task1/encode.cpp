#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// encodes one unsigned integer into vbyte
void encode(string fileName) {
    fstream file (fileName + ".txt", ios::in);

    ofstream outfile;
    outfile.open (fileName + ".vb", ios::out);

    while (!file.eof()) {
        cout << "start encoding ..." << endl;
        string line;
        while (getline(file, line)) {
            int i = stoi(line, nullptr, 10);
            cout << "encoding " << i << endl;
            while (true) {
                int byte = i%128;
                if (i < 128) {
                    outfile << byte + 128 << endl;
                    break;
                }
                outfile << byte << endl;
                i = i / 128;
            }
        }
    }
}

void writefile(string fileName, unsigned int* integers, int n) {
    ofstream outfile;
    outfile.open (fileName + ".txt", ios::out);
    
    for(int count = 0; count < n; count ++){
            outfile << integers[count] << endl ;
    }
}

// reads binary file into decimal (no en-/decodings)
void preparefile(string fileName) {
    int size = 8;

    fstream file (fileName, ios::in | ios::out | ios::binary);

    int n = sizeof(file);
    cout << "file size " << n << endl;

    unsigned int found[n];
    

    if (file.is_open()) {

        for (int i = 0; i < n; i++) {
            file.read((char *) &found[i], size);
            unsigned int nb = static_cast<int>(found[i]);
            cout << nb << endl;
        }
        writefile(fileName, found, n);
    }
    else cout << "couldn't open\n";
}


int main( int argc, char** argv )
{
    string fileName = argv[1];

    ifstream file (fileName, ios::in | ios::binary);

    if (file.good() && sizeof(file) > 0) {
        cout << fileName << " valid" << endl;
        preparefile(fileName); //write the binary integers to a text file

        encode(fileName); // from integers to vbyte

        cout << "Encoding took " << ((float)t)/CLOCKS_PER_SEC << " seconds" << endl; 

    } else {
        cout << "file " << fileName << " is empty or doesn't exist" << endl;
    }
}
