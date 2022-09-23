#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
int OBS = A1;
int LED = 12;
#define PIN        12 
#define NUMPIXELS 16*16
int y_gauche = 5;
int y_droit = 5;
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
    
   



}

void loop() {

   val = digitalRead(OBS);   // lecture de la valeur du signal
   Serial.print("Avoid Sensor - ");
   Serial.println(val);


   if(val == 0)
   {
      pixels.clear();
      y_droit -- ;
      y_gauche ++;
      OnLigne(0,y_gauche,0,y_gauche+5);
      OnLigne(15,y_droit,15,y_droit+5);
      delay(100);
      OnLigne(0,y_gauche,0,y_gauche+5);
      OnLigne(15,y_droit,15,y_droit+5);
   }else{
      y_droit = 5;
      y_gauche = 5;
      OnLigne(0,5,0,10);
      OnLigne(15,5,15,10);
      pixels.clear();
   }

   
 
   
  

   

   
   
}


