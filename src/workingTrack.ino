#define CUSTOM_SETTINGS
#define INCLUDE_GPS_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_INTERNET_SHIELD

#include <OneSheeld.h>
float lon;
float lat;

char charlat [10];
char charlon [10];

char readings [40];

HttpRequest myRequest("https://tracking-965ca.firebaseio.com/coordinates.json");

void setup() {
  // put your setup code here, to run once:
  OneSheeld.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  lat = GPS.getLatitude();
  dtostrf(lat, 8, 4, charlat);
  lon = GPS.getLongitude();
  dtostrf(lat, 7, 3, charlat); dtostrf(lon, 7, 3, charlon); 
  strcat (readings, "\"");
  strcat (readings,charlat);  
  strcat(readings,","); 
  strcat (readings,charlon);
  strcat (readings, "\"");
  Terminal.println(readings);
  myRequest.addRawData(readings);
  Internet.performPost(myRequest);
  memset(readings, 0, sizeof(readings));
  OneSheeld.delay(5000);
}
