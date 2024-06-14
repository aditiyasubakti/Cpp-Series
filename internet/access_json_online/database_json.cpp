#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <jsoncpp.cpp>

using namespace std;

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
	((string *)userp)->append((char *)contents, size * nmemb);
	return size * nmemb;
}

string getJSON(string URL)
{

	CURL *curl;
	CURLcode res;
	string readBuffer;

	curl = curl_easy_init();
	if (curl)
	{

		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true); // follow redirect
		// curl_easy_setopt(curl, CURLOPT_RETURNTRANSFER, true); // return as string
		curl_easy_setopt(curl, CURLOPT_HEADER, false);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);

		/* always cleanup */
		curl_easy_cleanup(curl);

		return readBuffer;
	}

	return 0;
}

int main()
{

	string data_indonesia = getJSON("https://jsonplaceholder.typicode.com/todos/1");
//	string data_tanggal = getJSON("https://data.covid19.go.id/public/api/update.json");

	data_indonesia.pop_back(); // removes last/back character from str
	data_indonesia.erase(data_indonesia.begin()); // removes first/front character from str

//	cout << "JSON Data: \n" << data_indonesia << endl;
//	cout << "JSON Data: \n" << data_tanggal << endl;

	Json::Reader reader;
    Json::Value obj;
    reader.parse(data_indonesia, obj);

	cout << "cetak" << endl;
	 cout << "UserId\t= " << obj["userId"].asString() << endl; 
    cout << "id\t= " << obj["id"].asString() << endl; 
    cout << "Title\t= " << obj["title"].asString() << endl; 
    cout << "Completed\t= " << obj["completed"].asString() << endl; 
	//cout << "Dirawat		= " << obj["dirawat"].asString() << endl;

	return 0;
}
