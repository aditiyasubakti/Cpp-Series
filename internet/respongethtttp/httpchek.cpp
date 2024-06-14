#include <iostream>
#include <curl/curl.h>
using namespace std;

// Fungsi ini akan dipanggil oleh cURL untuk menangani respons HTTP
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    CURL* curl;
    CURLcode res;
    string link = "http://reglab.tif.uad.ac.id/user/profile";

    // Inisialisasi cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set URL yang ingin diakses
        curl_easy_setopt(curl, CURLOPT_URL, link.c_str());

        // Set fungsi callback untuk menangani respons
        string responseData;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

        // Matikan verifikasi sertifikat (Hanya untuk pengembangan)
        // Secara aman, Anda seharusnya tidak menggunakan opsi ini di produksi
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Lakukan permintaan GET
        res = curl_easy_perform(curl);

        // Cek apakah permintaan berhasil atau tidak
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            cout << "penangkapan link \n";
            cout << "link :" << link;
            cout << endl;
            cout << "Response:\n" << responseData << endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    } else {
        cerr << "Error initializing cURL." << endl;
    }

    // Cleanup global cURL state
    curl_global_cleanup();

    return 0;
}

