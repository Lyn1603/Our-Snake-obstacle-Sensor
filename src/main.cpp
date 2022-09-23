#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
int OBS = A1;
int LED = 12;
#define PIN        12 
#define NUMPIXELS 16*16
int val ;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



int convert (int x , int y ){
   if (y%2 == 0)
         return(y*16+15-x);
      else
         return(y*16+x);
}


void OnLigne(int x,int y , int xbis, int ybis){
   while(x != xbis||y!=ybis){
      pixels.setPixelColor(convert(x,y),pixels.Color(150,0,0));
      if(x<xbis) x++;
      if(x>xbis) x--;
      if(y<ybis) y++;
      if(y>ybis) y--;
   }
   pixels.setPixelColor(convert(x,y),pixels.Color(150,0,0));
   pixels.show();

}

void setup() {
   Serial.begin(9600);
   pixels.begin();
   pinMode(OBS, INPUT);
   pixels.clear();
   pixels.setBrightness(10);
   /*for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();   
    delay(50);
  }*/
   pixels.clear();
    pixels.show(); 
    OnLigne(0,5,0,10);
    OnLigne(15,5,15,10);
    delay(120);
    OnLigne(5,0,10,0);
    OnLigne(5,15,10,15);



}

void loop() {

   val = digitalRead(OBS);   // lecture de la valeur du signal
   Serial.print("Avoid Sensor - ");
   Serial.println(val);


   if(val == 0)
   {
      pixels.clear();

      OnLigne(0,0,0,6);
      OnLigne(15,9,15,15);
      delay(100);
      OnLigne(0,0,6,0);
      OnLigne(9,15,15,15);
     

   }else{
      OnLigne(0,5,0,10);
      OnLigne(15,5,15,10);
      pixels.clear();
   }

   
 
   
  

   

   
   
}


