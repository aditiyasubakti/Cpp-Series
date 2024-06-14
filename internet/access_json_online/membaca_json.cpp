#include <iostream>
#include <algorithm>
#include <cctype>
#include <curl/curl.h>
#include "json/json.h"
#include "jsoncpp.cpp"
using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

int main() {
    const char* url = "http://localhost/smkn1gantar/data.php";
    CURL* curl = curl_easy_init();

    if (!curl) {
        cerr << "Gagal Mengunakan Lib." << endl;
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
        
		char opsi;
      	do{
		  
		cout<<"\n================================\n\t\tMencari\n================================\n";
 		string search;
 		cout<<"Searcing :";
 		getline(cin,search);
 		transform(search.begin(), search.end(), search.begin(), ::toupper);
 		
// 		for (char &c : searc) {
//        	 c = std::toupper(c);
//  	}
         cout<<"===================================\n";
        if (jsonData.isArray()) {
             for (const auto& Data : jsonData) {
             	string nama=Data["Nama"].asString();
             	 size_t found= nama.find(search);
             //	if(Data["Nama"].asString()==searc){
				 if(found != string::npos){
            		cout << "No Induk: " << Data["Induk"].asString() << endl;
               		cout << "Nama: " << Data["Nama"].asString() << endl;
               		cout << "No Peserta: " << Data["Peserta"].asString() << endl;
                	cout << "Jenis Kelamin: " << Data["Jenis_kelamin"].asString() << endl;
                	cout << "Kelas: " << Data["Kelas"].asString() << endl;
                	cout<<"\n\n=========================================================\n\n";
				}
            } 
        } else {
            cerr << "JSON response is not an array." << endl;
        }
    
        
        cout<<"ketik Y untuk lajut N untuk tidak :";
		 cin >> opsi;
        cin.ignore(); 

        if (toupper(opsi) != 'Y') {
            cout << "Program stopped." << endl;
            break;
        }
        system("cls");
		}while(true);			
     
    } 
//	else {
//        cerr << "Failed to retrieve JSON data from the server. Error: " << curl_easy_strerror(res) << endl;
//    }

 //  curl_easy_cleanup(curl);
 
 
	

            
    return 0;
}
