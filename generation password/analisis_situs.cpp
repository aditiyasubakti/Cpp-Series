#include <iostream>
#include <windows.h> // Library untuk menggunakan fungsi Sleep()

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
    string link;
  	string garis="|===============================================================|\n";
		cout<<garis;
		cout<<"|\t\tSelamat Data di Analisi \t\t\t|\n";
		cout<<"|\t\t\t\t\t\t\t\t|\n";
				cout<<"|\t\t\tInstagram:aditiya.subakti\t\t|\n";
				cout<<"|\t\t\tFacebook :aditiya.subakti\t\t|\n";
				cout<<"|\t\t\tGithub   :aditiya.subakti\t\t|\n";
				cout<<"|\t\t\tLinked   :aditiya.subakti\t\t|\n";
				cout<<"|\t\t\tWebsite  :AditiyaSubakti.com\t\t|\n";
		cout<<"|\t\t\t\t\t\t\t\t|\n";
		cout<<"|\t\t*dibuat Oleh Aditiya Subakti\t\t\t|\n";
		cout<<garis;

    // Meminta pengguna untuk memasukkan URL
    cout << "Masukkan URL yang ingin Anda akses: ";
    getline(cin, link);
	cout<<"\n|=============================hasil=============================|\n\n";
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

        // Set user agent
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3");

        // Matikan verifikasi sertifikat (Hanya untuk pengembangan)
        // Secara aman, Anda seharusnya tidak menggunakan opsi ini di produksi
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Aktifkan opsi untuk mengikuti redireksi
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Lakukan permintaan GET
        res = curl_easy_perform(curl);

        // Cek apakah permintaan berhasil atau tidak
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Periksa kode status HTTP
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            cout << "HTTP Status Code: " << http_code << endl;

            // Tampilkan informasi
            cout << "penangkapan link \n";
            cout << "link :" << link;
            cout << endl;
            cout << "Response size: " << responseData.size() << " bytes\n";
            cout << "Response:\n" << responseData << endl;
            Sleep(10000);

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

