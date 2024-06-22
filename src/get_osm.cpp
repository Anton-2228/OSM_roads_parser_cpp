#include <format>
#include <functional>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <curl/curl.h>

using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch(std::bad_alloc &e) {
        // handle memory problem
        return 0;
    }
    return newLength;
}

int main(int argc, char *argv[]) {
    timeval a,b;
    gettimeofday(&a, NULL);

    string minlat = "59.7961";
    string minlon = "30.5695";
    string maxlat = "60.1044";
    string maxlon = "30.1108";
    string file = "test.osm";

    // string minlat = argv[1];
    // string minlon = argv[2];
    // string maxlat = argv[3];
    // string maxlon = argv[4];
    // string file = argv[5];

    string query = format("[out:xml];"
    "way['highway']({},{},{},{});"
    "out body;"
    ">;"
    "out skel qt;", minlat, minlon, maxlat, maxlon);

    CURL* curl;
    CURLcode res;
    string responseString;

    // Инициализация libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://overpass-api.de/api/interpreter");

        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        else
            std::cout << "Response data: " << responseString << std::endl;

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();


    gettimeofday(&b, NULL);
}
