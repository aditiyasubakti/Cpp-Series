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
        // Set URL tujuan (action pada formulir register)
        curl_easy_setopt(curl, CURLOPT_URL, "https://aditiyasubakti.000webhostapp.com/register.php");

        // Meminta pengguna memasukkan informasi registrasi
        string fullName, email, username, password1, password2, gender, phone;
        bool jk;
        cout << "Masukkan nama lengkap: ";
        getline(cin, fullName); // Menggunakan getline untuk menangani spasi pada nama lengkap
        cout << "Masukkan email: ";
        cin >> email;
        cout << "Masukkan username: ";
        cin >> username;
        cout << "Masukkan password: ";
        cin >> password1;
        cout << "Verifikasi password: ";
        cin >> password2;
        back:
        cout << "Masukkan jenis kelamin (1.Laki-laki/0.Perempuan): ";
        cin >> jk;
        if(jk==1){
        	gender="Laki-Laki";
		}
		else if(jk==0){
			gender="Perempuan";
		}
		else{
			goto back;
		}
        cout << "Masukkan nomor HP: ";
        cin >> phone;

        // Verifikasi bahwa kedua password cocok
        if (password1 != password2) {
            cout << "Password tidak cocok. Registrasi gagal." << endl;
            return 0;
        }

        // Set data formulir register
        string postData = "NamaRegister=" + fullName + "&EmailRegister=" + email + "&UsernameRegister=" + username +
                               "&PasswordRegister1=" + password1 + "&PasswordRegister2=" + password2 + "&GenderRegister=" +
                               gender + "&PhoneRegister=" + phone;
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
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
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

