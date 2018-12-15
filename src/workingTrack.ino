#define CUSTOM_SETTINGS
#define INCLUDE_INTERNET_SHIELD
#define INCLUDE_GPS_SHIELD
#define INCLUDE_TERMINAL_SHIELD

#include <OneSheeld.h>

float latitude;
float longitude;

char charLatitude [12];
char charLongitude [12];

char readings [40];

char vehicleID [2] = "1";

HttpRequest request("https://jauc-ae38e.firebaseio.com/carTracking");

void setup() {
  OneSheeld.begin();
  OneSheeld.delay(2000);
  
}

void loop() {
  //get latitude and longitude from the GPS Shield
  latitude = GPS.getLatitude();
  longitude = GPS.getLongitude();
  //convert latitude and longitude to char
  dtostrf(latitude, 11, 7, charLatitude);
  dtostrf(longitude, 11, 7, charLongitude);
  //concatenate charLatitude and charLongitude to readings
  strcat(readings,"\"");
  strcat(readings,charLatitude);
  strcat(readings, ",");
  strcat(readings,charLongitude);
  strcat(readings, ",");
  strcat(readings,vehicleID);
  strcat(readings,"\"");
  Terminal.println(readings);
  // add the readings to the http request
  request.addRawData(readings);
  // perform post
  Internet.performPost(request);
  //clear readings
  memset(readings, 0, sizeof(readings));
  //wait 5 seconds
  OneSheeld.delay(5000);
}