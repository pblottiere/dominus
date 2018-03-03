#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>

int main (int argc, char* argv[])
{
    // Will contain the parameters
    char* IP_address; 
    char* port;
    char* name;
    int ID_Sensor, Type_Sensor;

    char http_address[250]; // buffer for the http request


    // CURL Handlers
    CURL *curl;
    CURLcode res;


    // Check correct use and update parameters
    if (argc != 6)
    {
        printf("Use to create a sensor which type is included in the following list :\n \
                    \t1   -> Pressure (Bar)\n \
                    \t2   -> Percentage\n \
                    \t80  -> Temperature\n \
                    \t81  -> Humidity\n \
                    \t82  -> Temperature & Humidity\n \
                    \t84  -> Temperature & Humidity & Barometer\n \
                    \t85  -> Rain\n \
                    \t86  -> Wind\n \
                    \t87  -> UV\n \
                    \t113 -> RFXMeter\n \
                    \t90  -> Energy\n \
                    \t249 -> TypeAirQuality\n\n \
                Needed 5 arguments but %d given.\nUse this way -> ./create_sensor IP Port Sensor_type Sensor_name ID_Sensor\n", argc-1);
        return EXIT_FAILURE;
    } else {
        IP_address      = argv[1];                
        port            = argv[2];
        Type_Sensor     = atoi(argv[3]);
        name            = argv[4];
        ID_Sensor       = atoi(argv[5]);                
    }



    // Setting CURL Context
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl)
    {
        // Request 1 -> Add the requested device

        sprintf(http_address, "http://%s:%s/json.htm?type=createvirtualsensor&idx=%d&sensorname=%s&sensortype=%d", IP_address, port, ID_Sensor, name, Type_Sensor);
        curl_easy_setopt(curl, CURLOPT_URL, http_address);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                return EXIT_FAILURE;
        }
                
        // Request 2 -> List of all devices

        sprintf(http_address, "http://%s:%s/json.htm?type=devices&filter=all&used=true&order=Name", IP_address, port);
        curl_easy_setopt(curl, CURLOPT_URL, http_address);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                return EXIT_FAILURE;
        }

        // Cleaning curl context 

        curl_easy_cleanup(curl);
    } else {
        curl_global_cleanup();
        fprintf(stderr, "Failed to init CURL");
        return EXIT_FAILURE;
    }

    curl_global_cleanup();
    return EXIT_SUCCESS;  
}
