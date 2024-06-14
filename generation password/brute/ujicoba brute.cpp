#include <iostream>
#include <string>
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

    // Inisialisasi cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set URL tujuan (action pada formulir login)
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/testinput/");

        // Meminta pengguna memasukkan informasi login
        string nama="aditiya subakti", username="aditiya@gamil.com", password="123456";
       

        // Set data formulir login
        string postData = "nama="+nama +"email=" + username + "pass=" + password;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        // Matikan verifikasi sertifikat (Hanya untuk pengembangan)
        // Secara aman, Anda seharusnya tidak menggunakan opsi ini di produksi
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Set fungsi callback untuk menangani respons
        string responseData;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

        // Lakukan permintaan POST
        res = curl_easy_perform(curl);

        // Cek apakah permintaan berhasil atau tidak
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            cout << "Gagal" << endl;
        } else {
            cout << "Sukses" << endl;
            cout << "Response:\n" << responseData << endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    // Cleanup global cURL state
    curl_global_cleanup();

    return 0;
}

