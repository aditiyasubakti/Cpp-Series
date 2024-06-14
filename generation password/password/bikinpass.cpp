#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void generatePermutations(const string &str, vector<string> &permutations) {
    string s = str;
    sort(s.begin(), s.end()); 
    do {
        permutations.push_back(s);
    } while (next_permutation(s.begin(), s.end()));
}

void savePermutationsToFile(const vector<string> &permutations, const string &filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto &perm : permutations) {
            file << perm << endl;
        }
        file.close();
        cout << "Permutasi berhasil disimpan di " << filename << endl;
    } else {
        cerr << "Tidak bisa membuka file untuk menulis." << endl;
    }
}

int main() {
    string input;
    vector<string> permutations;
    string garis = "+===============================================================+\n";
    
    cout << garis;
    cout << "|\t\t\tMesin Pencari Password\t\t\t|\n";
    cout << "|\tCukup tuliskan yang Anda ingat sedikit\t\t\t|\n";
    cout << "|\tMesin ini akan membuatkan beberapa kombinasi yang cocok\t|\n";
    cout << "|\tExample: 'liyoe1uov' dan password aslinya '1iloveyou'\t|\n";
    cout << "|\tAkan secara otomatis dibuatkan\t\t\t\t|\n";
    cout << garis;
    
    cout << "Masukkan string: ";
    cin >> input;

    generatePermutations(input, permutations);

    savePermutationsToFile(permutations, "permutasi.txt");

    return 0;
}

