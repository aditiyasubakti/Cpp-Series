#include <iostream>
#include <string>
#include "lib/httplib.h"  // Include the httplib header

using namespace std;

int main() {
    httplib::Server svr;

    svr.Get("/.*", [&](const httplib::Request& req, httplib::Response& res) {
        // Set the destination URL
        string dest_url = "https://www.instagram.com" + req.path;

        // Create a new cURL handle
        CURL* curl = curl_easy_init();

        if (curl) {
            // Set URL to the destination
            curl_easy_setopt(curl, CURLOPT_URL, dest_url.c_str());

            // Set custom User-Agent
            curl_easy_setopt(curl, CURLOPT_USERAGENT, req.get_header_value("User-Agent").c_str());

            // Set proxy server
            curl_easy_setopt(curl, CURLOPT_PROXY, "http://190.6.23.219:999"); // Adjust the proxy details

            // Perform the request and get the response
            CURLcode res_curl = curl_easy_perform(curl);

            // Check if the request was successful
            if (res_curl != CURLE_OK) {
                cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res_curl) << endl;
                res.status = 500;  // Internal Server Error
            } else {
                // Get the response data
                string responseData;
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

                // Cleanup the cURL handle
                curl_easy_cleanup(curl);

                // Set the response data for the client
                res.set_content(responseData, "text/html");
            }
        } else {
            cerr << "Failed to initialize cURL" << endl;
            res.status = 500;  // Internal Server Error
        }
    });

    cout << "Server is running on port 8080" << endl;
    svr.listen("localhost", 8080);  // Adjust the server details

    return 0;
}

