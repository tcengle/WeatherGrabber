#include "xmlGet.h"

weatherGet::weatherGet() {
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
};



//write callback for writing data to string
static size_t write_callback(char *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
};



//gets weather data and returns path to saved data
std::string weatherGet::getLocationData(){
    //CURL *curl;
    
    CURLcode res;
    //char *temp;
  
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, locationURL.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
        locationData.clear();
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &locationData);
    
    res = curl_easy_perform(curl);
     
    if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
 
    curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return "Poop";
};

int weatherGet::writeToFile(){
    std::ofstream oss;

    oss.open(cityName + ".xml");

    oss << locationData;

    oss.close();

    return 1;

};