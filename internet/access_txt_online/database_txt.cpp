#include <iostream>
#include <curl/curl.h>

using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    char* data = static_cast<char*>(contents);
    cout.write(data, totalSize);
    return totalSize;
}

int main() {
    string url = "https://aditiyasubakti.000webhostapp.com/dashboard.php";  // Ganti URL sesuai kebutuhan

    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  // Tentukan URL yang akan diakses
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL); // Tidak ada data kustom yang diperlukan

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "Gagal mengakses URL: " << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);
    } else {
        cerr << "Gagal menginisialisasi libcurl." << endl;
    }

    return 0;
}

