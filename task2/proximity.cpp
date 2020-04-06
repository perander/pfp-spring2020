#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


void proximity(int lower, int upper, string fileName) {
    fstream file (fileName, ios::in);

    ofstream outfile;
    outfile.open (fileName + ".result.txt", ios::out);

    int a, b;

    while (file >> a && file >> b) {
        int size = 8;
        cout << a << " " << b << endl;

        ifstream file_a ("F" + to_string(a) + ".vb");
        ifstream file_b ("F" + to_string(b) + ".vb");

        int n = sizeof(file_a) * 8;
        int first[n];
        int second[n];
        int i = 0;
        
        while (! file_a.eof()) {
            string line;
            while(getline(file_a, line)) {
                int val = stoi(line, nullptr, 10);
                first[i] = val;
                i++;
            }
        }

        i = 0;

        while (! file_b.eof()) {
            string line;
            while(getline(file_b, line)) {
                int val = stoi(line, nullptr, 10);
                second[i] = val;
                i++;
            }
        }

        sort(first, first + n);
        sort(second, second + n);

        int size_of_intersection = 0;


        int p_0 = 0;
        int p_1 = n-1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (second[j] >= first[i]-lower && second[j] <= first[i] + upper) {
                    size_of_intersection++;
                    // actually put the first[i] into a list / set in order
                    // to not count duplicates
                }
            }
        }
        
        cout << size_of_intersection << endl;
    }
}



int main (int argc, char** argv) {

    if (argc != 4) {
        cout << "please give 3 parameters" << endl;
    } else {
        int lower = stoi(argv[1]);
        int upper = stoi(argv[2]);

        if (lower > upper) {
            cout << "arguments should be in order: lower, upper" << endl;
        } else {
            string pairs = argv[3];
            proximity(lower, upper, pairs);
        }
    }
}