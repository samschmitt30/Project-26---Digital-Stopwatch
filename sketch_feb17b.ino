// Project 26 – Digital Stopwatch 
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);        // select the pins used on the LCD panel
long ms;
int Sec = 0;
int Min = 0;
long msr=0;
int lcd_key     = 0;
int adc_key_in  = 0;
int bright = 255;
bool Held=0;

#define btnUP     1
#define btnDOWN   2
#define btnNONE   5

void setup()
{
  lcd.begin(16, 2);                       // start the library
  //msr=millis();
  lcd.clear();
  pinMode(10,OUTPUT);
  msr=millis();
}

int readButtons()
{
  adc_key_in = analogRead(0);       // read the value from the sensor
  if (adc_key_in < 250 && adc_key_in > 144 )  return btnUP;
  else if (adc_key_in < 450 && adc_key_in > 251)  return btnDOWN;
  else return btnNONE;
}

void loop(){
   analogWrite(10,150);
  lcd.home();
  lcd.print(String(Min)+":"+String(Sec)+":"+String(millis()-msr)+"  ");
  //lcd.print(msr);
  if(millis()-msr>1000){
    msr+=1000;
    Sec++;
  }
  if(Sec>=60){
    Sec=0;
    Min++;
  }
  
  {
  if(analogRead(0)<900&!analogRead(0)<700&!Held){
    Held=1;
    lcd.setCursor(0,1);
    lcd.print(String(Min)+":"+String(Sec)+":"+String(millis()-msr)+" ");
  }
  
  {
  if(!(analogRead(0)<900&!analogRead(0)<700&Held)){
    Held=0;
  }
}
  
            // print the results to the lcd
            //lcd.print(":");
            // lcd.print(Minutes);
            //lcd.print(":");
            //lcd.print(S);
            //lcd.print(":");
            //lcd.print(millis()-msr);
     

  

  lcd_key = readButtons();

  switch (lcd_key)
  {

    case btnDOWN:{        //Down button is pressed to dim screen
      if (bright > 0)     //Sets minimum brightness
      {
        bright--;
      }  
      break;
    }
    case btnUP:{        //Up button is pressed to brighten screen
      if (bright < 255) //Sets maximum brightness
      {
        bright++;
      }
      break;
    }
    case btnNONE:{
      break;
    }
  }
  }
}
    
  
