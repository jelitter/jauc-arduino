#define CUSTOM_SETTINGS
#define INCLUDE_GPS_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_INTERNET_SHIELD

#include <OneSheeld.h>

float lat;
float lng;
char charlat [20];
char charlng [20];

char vehicleID [4] = "001";
char vehicleStatus [2] = "a";

char readings [80];

HttpRequest myRequest ("https://jauc-ae38e.firebaseio.com/carTracking.json");

void setup() {
  
    OneSheeld.begin();
}

void loop() {

    lat = GPS.getLatitude();
    lng = GPS.getLongitude();
    dtostrf(lat, 9, 5, charlat);
    dtostrf(lng, 9, 5, charlng);
    strcat(readings,"\"");
    strcat(readings, vehicleID);
    strcat(readings, ",");
    strcat(readings, vehicleStatus);
    strcat(readings, ",");
    strcat(readings, charlat);
    strcat(readings, ",");
    strcat(readings, charlng);
    strcat(readings, "\"");
    Terminal.println(readings);
    myRequest.addRawData(readings);
    Internet.performPost(myRequest);
    memset(readings, 0, sizeof(readings));
    OneSheeld.delay(5000);
    
}
