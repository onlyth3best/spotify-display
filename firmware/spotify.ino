//spotify thing
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <WiFi.h>
#include <SpotifyEsp32.h>
#include <SPI.h>

#define TFT_CS 1 // edit
#define TFT_RST 2
#define TFT_DC 3
#define TFT_SCLK 4
#define TFT_MOSI 5

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


char* SSID = "INSERT_SSID_HERE";
char* PASSWORD = "INSERT_PASSWORD_HERE";

const char* CLIENT_ID = "CLIENT_ID";
const char* CLIENT_SECRET = "CLIENT_SECRET";
Spotify sp(CLIENT_ID, CLIENT_SECRET);

// -  -  - -  -  - -  -  - -  -  - -  -  - -  -  - -  -  - -  -  - -  -  - -  -  - -  -  - //

void setup(){
  Serial.begin(115200)

  //initiate screen!
  tft.initR(INITR_BLACKTAB); // type of screeen
  tft.setRotation(1); // LANDSCAPE orientation. remove for portrait ori.
  Serial.println("TFT initialised!!";)
  tft.fillScreen(ST77XX_BLACK); // checking and making sure nothing is in buffer

    //WIFI SETUP!//
  Wifi.begin(SSID, PASSWORD); // try to connect to wifi
  Serial.print("Connecting to WiFi…"); // prints it into console
  while(WiFi.stasus() != WL_CONNECTED) // check if connected to wifi
  {
    delay(1000);
    Serial.print(" . ") // shows a loading dot every second, 1000 millis
  }
  Serial.printf("\nConnected!!") // wifi connected screen, printf

  tft.setCursor(0,0); // make the cursor at the top left
  tft.write(WiFi.localIP().toString().c_str()); // print out IP on the screen
  
  //spotify

  sp.begin();
  while(!sp.is_auth())
  {
    sp.handle_client(); // edited
  }
  Serial.println("Connected to Spotify!!")
}


// -  -  - -  -  - -  -  - -  -  - -  -  - -  -  - -  -  - -  -  - -  -  - -  -  - -  -  - //
void loop() {
  String currentArtist = sp.current_artist_names();
    String currentTrackname = sp.current_track_name();

    if (lastArtist != currentArtist && currentArtist != "Something went wrong" && !currentArtist.isEmpty()) {
        tft.fillScreen(ST77XX_BLACK);
        lastArtist = currentArtist;
        Serial.println("Artist: " + lastArtist);
        tft.setCursor(10,10);
        tft.write(lastArtist.c_str());
    }

    if (lastTrackname != currentTrackname && currentTrackname != "Something went wrong" && currentTrackname != "null") {
        lastTrackname = currentTrackname;
        Serial.println("Track: " + lastTrackname);
        tft.setCursor(10,40);
        tft.write(lastTrackname.c_str());
    }
    delay(2000);
}



/*
//general methods
  tft.write("STRING HERE");  // prints out the string
  tft.setCursor(x,y);        // the screen is 160x128! x,y grid
  tft.fillScreen(ST77XX_COLOR); // most of the main colors are here!
  tft.drawRect(Cursorx, Cursory, RectWidth, RectHeight, ST77XX_color); // draws rectangle
  tft.fillRect(Cursorx, Cursory, RectWidth, RectHeight, ST77XX_color); // fills in a rect
  tft.setTextSize(integer);  // try it out! Use 1,2,3, etc.

  tft.write(variable.toString().c_str());
*/