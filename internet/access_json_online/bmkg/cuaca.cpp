  #include <iostream>
  #include <algorithm>
  #include <cctype>
  #include <curl/curl.h>
  #include "jsoncpp.cpp"

  using namespace std;

  int main();

  size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
      size_t total_size = size * nmemb;
      output->append((char*)contents, total_size);
      return total_size;
  }

  int MainBmkg() {
      char opsi, pilihan;

      do {
          cout << "1.Yogyakarta\n";
          cout << "2.Bali\n";
          cout << "0.back\n";
          cout << "pilih Lokasi 1-2 :";
          cin >> pilihan;

          if (pilihan == '0') {
              return main();
          } else if (pilihan == '1' || pilihan == '2') {
              const char* url = (pilihan == '1') ? "https://aditiyasubakti.000webhostapp.com/Cuaca/Yogyakarta"
                                                : "https://aditiyasubakti.000webhostapp.com/Cuaca/Bali";
              CURL* curl = curl_easy_init();

              if (!curl) {
                  cerr << "Gagal Menggunakan Lib." << endl;
                  return 1;
              }

              curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
              curl_easy_setopt(curl, CURLOPT_URL, url);

              string responseData;
              curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
              curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

              CURLcode res = curl_easy_perform(curl);

              if (res == CURLE_OK) {
                  Json::CharReaderBuilder reader;
                  Json::Value jsonData;
                  Json::String errs;

                  istringstream responseStream(responseData);
                  Json::parseFromStream(reader, responseStream, &jsonData, &errs);

                  if (jsonData.isObject()) {
                      int i = 0;
                      auto memberNames = jsonData.getMemberNames();  // Store member names in a variable

                      for (const auto& city : memberNames) {
                          cout << i << ". Kabupaten " << city << endl;
                          i++;
                      }

                      int lokasi;
                      cout << "Masukkan pilihan anda: ";
                      cin >> lokasi;

                      if (lokasi >= 0 && lokasi < i) {
                          const auto& selectedCityName = memberNames[lokasi];  // Use the stored variable
                          const auto& selectedCity = jsonData[selectedCityName];

                          if (selectedCity.isArray()) {
                            string caritanggal;
                            cout << "Check Tanggal/Bulan/Tahun \n";
                            cout << "Contoh 10/12/2023  :";
                            cin.ignore(); 
                            getline(cin, caritanggal);
                            transform(caritanggal.begin(), caritanggal.end(), caritanggal.begin(), ::toupper);

                            for (const auto& data : selectedCity) {
                                string waktu = data["Waktu"].asString();
                                size_t found = waktu.find(caritanggal);

                                if (found != string::npos) {
                                    cout << "Waktu\t\t:" << data["Waktu"].asString() << endl;
                                    cout << "Cuaca\t\t:" << data["Cuaca"].asString() << endl;
                                    cout << "Suhu\t\t:" << data["Suhu_C"].asString() << "*C" << endl;
                                    cout << "\t\t" << data["Suhu_F"].asString() << "*F" << endl;
                                    cout << "Max_Suhu\t: " << data["Max_Suhu"].asString() << endl;
                                    cout << "Min_Suhu\t: " << data["Min_Suhu"].asString() << endl;
                                    cout << "Kelembaban\t: " << data["Kelembaban"].asString() << endl;
                                    cout << "Max_Kelembaban\t: " << data["Max_Kelembaban"].asString() << endl;
                                    cout << "Min_Kelembaban\t: " << data["Min_Kelembaban"].asString() << endl;
                                    cout << "Arah_Angin\t: " << data["Arah_Angin"].asString() << endl;
                                    cout << "Kecepatan_Angin_Kt: " << data["Kecepatan_Angin_Kt"].asString() << endl;
                                    cout << "Kecepatan_Angin_MPH: " << data["Kecepatan_Angin_MPH"].asString() << endl;
                                    cout << "Kecepatan_Angin_KPH: " << data["Kecepatan_Angin_KPH"].asString() << endl;
                                    cout << "Kecepatan_Angin_MS: " << data["Kecepatan_Angin_MS"].asString() << endl;
                                    cout << "\n============================\n";
                                } else {
                                    cout << "Data tidak ditemukan\n";
                                }
                            }
                          } else {
                              cerr << "Data for city " << selectedCityName << " is not an array." << endl;
                          }

                      } else {
                          cerr << "Invalid selection." << endl;
                      }
                  } else {
                      cerr << "JSON response is not an object." << endl;
                  }
              } else {
                  cerr << "Failed to perform cURL request." << endl;
              }

              curl_easy_cleanup(curl);
          } else {
              cerr << "Invalid selection." << endl;
          }

          cout << "Ketik Y untuk lanjut, N untuk berhenti: ";
          cin >> opsi;
          cin.ignore(); // Ignore the newline character from the previous input

          if (toupper(opsi) != 'Y') {
              cout << "Program dihentikan." << endl;
              break;
          }

          cout << "\033[H\033[J"; // Membersihkan layar dengan karakter khus

      } while (true);

      return 0;
  }

   int main() {
       MainBmkg();
       return 0;
   }

