#include <iostream>
#include <curl/curl.h>
#include <json.hpp>
#include <string>
#include <cstdlib>

using json = nlohmann::json;

// Callback function to handle the response of the curl request
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main(int argc, char* argv[]) {
    // Print ASCII logo
    std::cout << R"(
      _______                    _______ __           ____ __         __
     |     __|.----.---.-.----- |_     _|  |--.-----.|    |  |.-----.|  |_
     |__     ||  __|  _  |     |  |   | |     |  -__||       ||  -__||   _|
     |_______||____|___._|__|__|  |___| |__|__|_____||__|____||_____||____|
    )" << std::endl;

    // Determine how many entries to display (default to max 100)
    int maxEntries = 100; // Default value

    if (argc > 1) {
        maxEntries = std::atoi(argv[1]); // Get user-defined value from command line
        if (maxEntries < 1 || maxEntries > 100) {
            std::cerr << "Please enter a number between 1 and 100." << std::endl;
            return 1; // Exit if the number is out of range
        }
    }

    // Initialize CURL
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();

    // Check if CURL was initialized successfully
    if (curl) {
        std::string readBuffer;

        // Set the URL for the API
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.scanthe.net/");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Parse the JSON data
            try {
                json jsonResponse = json::parse(readBuffer);

                // Accessing and printing relevant parts of the JSON
                int count = 0; // Counter for the entries displayed
                for (const auto& packet : jsonResponse["data"]) {
                    if (count >= maxEntries) break; // Stop if we reach the maximum entries
                    std::cout << "ID: " << packet["id"] << std::endl;
                    std::cout << "Timestamp: " << packet["timestamp"] << std::endl;
                    std::cout << "Source IP: " << packet["source_ip"] << std::endl;
                    std::cout << "Source Port: " << packet["source_port"] << std::endl;
                    std::cout << "Destination Port: " << packet["dest_port"] << std::endl;
                    std::cout << "Data: " << packet["data"] << std::endl;
                    std::cout << "----------" << std::endl;
                    count++;
                }

            } catch (json::parse_error& e) {
                // Output error from parsing
                std::cerr << "JSON parse error: " << e.what() << std::endl;
            }
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    return 0;
}
