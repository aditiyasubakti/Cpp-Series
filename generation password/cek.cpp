#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

// Fungsi callback untuk menangani data yang diterima.
size_t writeCallback(char* ptr, size_t size, size_t nmemb, string* data) {
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

int main() {
    CURL* curl;
    CURLcode res;
    string response;

    // Inisialisasi libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Inisialisasi handle
    curl = curl_easy_init();
    if (curl) {
        // Set URL yang ingin diambil
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/testinput/home.php");

        // Set metode permintaan POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Data yang akan dikirim dalam permintaan POST
        string postFields = "nama=waryo";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

        // Set fungsi callback untuk menangani data yang diterima
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

        // Set buffer untuk menyimpan data yang diterima
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Lakukan permintaan untuk mengubah nilai sesi 'nama'
        res = curl_easy_perform(curl);

        // Cek jika permintaan berhasil
        if (res != CURLE_OK) {
            cerr << "Failed to send request: " << curl_easy_strerror(res) << endl;
        } else {
            // Menampilkan respons dari server
            cout << "Response:\n" << response << endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    } else {
        cerr << "Failed to initialize libcurl." << endl;
    }

    // Cleanup libcurl
    curl_global_cleanup();

    return 0;
}

