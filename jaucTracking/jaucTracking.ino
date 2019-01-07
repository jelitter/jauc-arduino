#define CUSTOM_SETTINGS
#define INCLUDE_INTERNET_SHIELD
#define INCLUDE_GPS_SHIELD
#define INCLUDE_TERMINAL_SHIELD

#include <OneSheeld.h>
HttpRequest request("https://jauc-ae38e.firebaseio.com/cars/-LUtgVxScypNF-KFeqGZ.json"); // This URL is specific for car -LUtgVxScypNF-KFeqGZ. Change the URL to track another car

int cadency = 5000;

float latitude;
float longitude;

char charLatitude [12];
char charLongitude [12];

char readings [50];

void setup() {
  OneSheeld.begin();
  OneSheeld.delay(2000);

}

void loop() {
  getCoordinates();
  readingsCreator();
  toFirebase();
  OneSheeld.delay(cadency);
}

void getCoordinates() {
  latitude = GPS.getLatitude();
  longitude = GPS.getLongitude();
}

void toFirebase() {
  request.addRawData(readings);
  Internet.performPut(request);
  Terminal.println(readings);
  memset(readings, 0, sizeof(readings));
}

void readingsCreator(){
  dtostrf(latitude, 11, 7, charLatitude);
  dtostrf(longitude, 11, 7, charLongitude);
  strcat(readings, "{\"location\":{\"lat\": ");
  strcat(readings, charLatitude);
  strcat(readings, ",\"lon\": ");
  strcat(readings, charLongitude);
  strcat(readings, "}}");
}
