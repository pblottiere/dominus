#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <iostream>


int parseJSONString(std::string s){
    Json::Value json;   
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(s.c_str(), json);     //parse process
    if (!parsingSuccessful){
        std::cout << "Failed to parse" << reader.getFormattedErrorMessages();
        return 0;
    }
    int idx = atoi(json.get("idx", "1" ).asString().c_str());
    return idx;
}



size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s){
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    try{
        s->resize(oldLength + newLength);
    }
    catch(std::bad_alloc &e){
        //handle memory problem
        return 0;
    }

    std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
    return size*nmemb;
}

int main (int argc, char* argv[]){

  if (argc < 2){

        printf("Error, missing arguments\n");
        printf("Convention: \n");
        printf("./domoticz_create_assign ID_Sensor Temperature\n");
        return EXIT_SUCCESS;

  }else{

        CURL *curl_CreateSensor, *curl_UpdateSensor;
        CURLcode res1, res2;
        char* id = argv[1];
        char* temp = argv[2];
        char request1[256];
        char request2[256];
        std::string s;
        sprintf(request1, "http://localhost:8080/json.htm?type=createvirtualsensor&idx=%s&sensorname=TemperatureSensor&sensortype=80", id);
        

        curl_global_init(CURL_GLOBAL_ALL);

        // get a curl handle
        curl_CreateSensor = curl_easy_init();
        curl_UpdateSensor = curl_easy_init();
        if(curl_CreateSensor && curl_UpdateSensor) {
            
            curl_easy_setopt(curl_CreateSensor, CURLOPT_URL, request1);
            curl_easy_setopt(curl_CreateSensor, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString); 
            curl_easy_setopt(curl_CreateSensor, CURLOPT_WRITEDATA, &s);
            
            // Perform the requests, res1, res2 will get the returns code  
            res1 = curl_easy_perform(curl_CreateSensor);

            // Request 2 with good idx
            sprintf(request2, "http://localhost:8080/json.htm?type=command&param=udevice&idx=%d&nvalue=0&svalue=%s", parseJSONString(s), temp);
            curl_easy_setopt(curl_UpdateSensor, CURLOPT_URL, request2);
            res2 = curl_easy_perform(curl_UpdateSensor);

            // Check for errors 
            if(res1 != CURLE_OK){
                fprintf(stderr, "curl_easy_perform() Create Sensor failed: %s\n",
                curl_easy_strerror(res1));
            }
            if(res2 != CURLE_OK){
                fprintf(stderr, "curl_easy_perform() Update Sensor failed: %s\n",
                curl_easy_strerror(res2));
            }

            curl_easy_cleanup(curl_CreateSensor);
            curl_easy_cleanup(curl_UpdateSensor);
            
        }
        curl_global_cleanup();
        return EXIT_SUCCESS;
    }
  
}


