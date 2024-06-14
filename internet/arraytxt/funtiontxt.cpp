#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to read data from the database file
vector<string> readDataFromDB(const string& filename) {
    ifstream file(filename);
    vector<string> dataArray;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            dataArray.push_back(line);
        }
        file.close();
    }

    return dataArray;
}

// Function to write data to the database file
void writeDataToDB(const string& filename, const vector<string>& dataArray) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& data : dataArray) {
            file << data << "\n";
        }
        file.close();
    }
}

int main() {
    // Get current timestamp for generating unique ID
    srand(time(0));
    string id = to_string(rand());

    // Read input data
    string nameba, des, harga;
    cout << "Enter name: ";
    getline(cin, nameba);
    cout << "Enter description: ";
    getline(cin, des);
    cout << "Enter price: ";
    getline(cin, harga);

    // Simulate file upload
    // Assume the image file is successfully uploaded to the specified folder
    //string folder = "img/produc/";

    // Nama file database
    string filename = "produc.txt";

    // Membaca data dari file database (jika ada)
    vector<string> database = readDataFromDB(filename);

    // Melakukan operasi database
    // Misalnya, menambahkan data baru
    string newData = id + "," + nameba + "," + des + "," + harga;
    database.push_back(newData);

    // Menulis data ke file database
    writeDataToDB(filename, database);

    cout << "Successfully Updated\n";
    return 0;
}

