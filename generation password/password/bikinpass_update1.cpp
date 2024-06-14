#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void generatePermutations(const string &str, vector<string> &permutations, string prefix = "") {
    if (prefix.size() == str.size()) {
        permutations.push_back(prefix);
        return;
    }

    // Rekursif untuk memasukkan angka pada posisi saat ini
    for (char c = '0'; c <= '9'; ++c) {
        generatePermutations(str, permutations, prefix + c);
    }

    // Jika karakter saat ini adalah huruf, tambahkan versi kapitalisasi dan non-kapitalisasi
    if (isalpha(str[prefix.size()])) {
        char c = str[prefix.size()];
        if (islower(c)) {
            generatePermutations(str, permutations, prefix + (char)toupper(c));
        } else {
            generatePermutations(str, permutations, prefix + (char)tolower(c));
        }
    }
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

    savePermutationsToFile(permutations, "permutasi.csv");

    return 0;
}

