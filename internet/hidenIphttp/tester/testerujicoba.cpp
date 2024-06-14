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

    if(curl) {
        // Set URL yang ingin diakses
        curl_easy_setopt(curl, CURLOPT_URL, "https://2981-112-78-46-157.ngrok-free.app/");

        // Set fungsi callback untuk menangani respons
        string responseData;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // Set custom User-Agent
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) KIW029.110 Safarimu/537.3");

        // Set proxy server
        curl_easy_setopt(curl, CURLOPT_PROXY, "190.6.23.219");

        // Set proxy port
        curl_easy_setopt(curl, CURLOPT_PROXYPORT, 999);

        // Manually input session or cookie
        string session;
        cout << "Masukkan Session atau Cookie: ";
        getline(cin, session);

        // Manually input expiration date
        string expirationDate;
        cout << "Masukkan Expiration Date (optional): ";
        getline(cin, expirationDate);

        // Set the session or cookie using CURLOPT_COOKIE
        curl_easy_setopt(curl, CURLOPT_COOKIE, session.c_str());

        // Set the expiration date using CURLOPT_COOKIESESSION
        if (!expirationDate.empty()) {
            curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1L);
        }

        // Lakukan permintaan GET
        res = curl_easy_perform(curl);

        // Cek apakah permintaan berhasil atau tidak
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            cout << "Response:\n" << responseData << endl;

        // Cleanup
        curl_easy_cleanup(curl);
    }

    // Cleanup global cURL state
    curl_global_cleanup();

    return 0;
}

