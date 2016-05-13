#include <LiquidCrystal.h> //Includes the file required for LCD.
//#include <time.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Pins used by the LCD.


  //--REFLECTED NUMBERS-- //

//0
byte newChar[8] = {
        B01110,
        B10001,
        B11001,
        B10101,
        B10011,
        B10001,
        B01110,
        B00000
};


//1
byte newChar1[8] = {
        B00100,
        B00110,
        B00100,
        B00100,
        B00100,
        B00100,
        B01110,
        B00000
};

//2
byte newChar2[8] = {
        B01110,
        B10001,
        B10000,
        B01000,
        B00100,
        B00010,
        B11111,
        B00000
};

//3
byte newChar3[8] = {
        B11111,
        B01000,
        B00100,
        B01000,
        B10000,
        B10001,
        B01110,
        B00000
};

//4
byte newChar4[8] = {
        B01100,
        B01010,
        B01001,
        B11111,
        B01000,
        B01000,
        B01000,
        B00000
};

//5
byte newChar5[8] = {
        B11111,
        B00001,
        B01111,
        B10000,
        B10000,
        B10001,
        B01110,
        B00000
};

//6

byte newChar6[8] = {
        B01100,
        B00010,
        B00001,
        B01111,
        B10001,
        B10001,
        B01110,
        B00000
};

//7
byte newChar7[8] = {
        B11111,
        B10000,
        B01000,
        B00100,
        B00010,
        B00010,
        B00010,
        B00000
};
//9
byte newChar9[8] = {
        B01110,
        B10001,
        B10001,
        B11110,
        B10000,
        B01000,
        B00110,
        B00000
};



int state = 0, //Bluetooth -
    flag  = 0, // -> Definitions
    tempPin = 0; //Pin used by the temp sensor.

char reset, //un-used for now. 
     redoTemp, //Un-used for now.
     hour, 
     minute,
     second;
    
void setup() {
  Serial.begin(9600);
    lcd.begin(16, 2); //Activates 16 rows and the 2 columns on the LCD

        
   //lcd.createChar(0, newChar); 
  /* lcd.createChar(1, newChar1);
   lcd.createChar(2, newChar2);  
   lcd.createChar(3, newChar3); 
   lcd.createChar(4, newChar4);
   lcd.createChar(5, newChar5); 
   lcd.createChar(6, newChar6);
   lcd.createChar(7, newChar7); 
   lcd.createChar(8, newChar9);*/ //THIS IS NUMBER 9
   
   /* lcd.begin(16, 2); 
     //lcd.print("hello");
      
    //lcd.write(0);
    lcd.write((uint8_t)1);
    lcd.write(2);
    lcd.write(3);
    lcd.write(4);
    lcd.write(5);
    lcd.write(6);
    lcd.write(7);
    
    lcd.write(8);*/
    
  lcd.clear();
    
    //lcd.print("0123456789"); //Start up message on LCD
    delay(5000); //Keeps the start up message up for 5 seconds.
   // lcd.clear(); //Clears the LCD after the 5 seconds
}

/*void timer() {
  for (hour = 0; hour < 13; hour++) {
    lcd.print("testing");
    delay(3000);
  }
    for (minute = 0; minute < 60; minute++){
      lcd.print("test2");
      delay(2000);
    }
    for (second = 0; second < 60; second++){
      lcd.print("test3");
      delay(1000);
    }
    lcd.print(hour); lcd.print(minute); lcd.print(second);
    
}*/


void inputStart() { //Start custom inputs
int i = 0; //defining i for while loop
char commandbuffer[100];
    if(Serial.available()){ 
     delay(100);
     while( Serial.available() && i< 99) {
        commandbuffer[i++] = Serial.read(); //Reads from bluetooth input
     }
     commandbuffer[i++]='\0';
  }

  if(i>0)

     Serial.println((char*)commandbuffer); //Prints onto Serial Monitor
     lcd.print((char*)commandbuffer); //Prints custom input onto LCD
     delay(10000); //Leaves custom input on LCD for 10 seconds
     lcd.clear(); //Clears after 10 seconds.
}
int temp() { //Temp Start
int reading = analogRead(tempPin); //defines the analog Pin
float voltage = reading * 5.0; //Converting to voltage
voltage /= 1024.0;
//Serial.print(voltage); Serial.println("V");
//delay(5000);
float tempC = (voltage - 0.5) * 100; //Converts to Celcius
float tempF = (tempC * 9.0 / 5.0) + 32.0; // Converts C to F
return tempF; //Returns the value back into the loop function.
//END TEMP
}
void loop() {

  if(Serial.available() > 0){ 
    state = Serial.read();
    flag=0; //Checks for flag reading.
    }
   
 //reset:
  if(state == '1') { //Command 1
    if(flag == 0) {
      //redoTemp:
      lcd.clear();
      lcd.begin(16, 2);
      lcd.print("erutarepmeT "); mirrorprint(temp()); 
      lcd.print("F"); //Temperature display
      //delay(5000);
      flag = 1;
      /*if(state != '1') {
        goto reset;
      } else {
      goto redoTemp;
    }*/
    }
  } else if(state == '2') { //Custom Input
    if(flag == 0) {
      lcd.clear();
      inputStart(); //Calls in the inputStart function
      flag = 1;
    }
  } else if(state == '3') { //Custom Timer (STILL TO BE COMPLETED)
    lcd.clear();
    if(flag == 0) {
        lcd.clear();
       /* for (int minute = 30; minute < 60; minute++) {
          int hour = 00;
          lcd.print(hour); lcd.print(":"); lcd.print(minute);
          delay(1000);
          lcd.clear();
        }*/
        lcd.print("test");
        lcd.setCursor(2, 0);
        lcd.cursor();
        flag = 1;
      }
      
    }
    else if(state == '4') { //Custom Timer (STILL TO BE COMPLETED)
    lcd.clear();
    if(flag == 0) {
        lcd.clear();

        for(int i=0;i <= 999; i++)
        {
          mirrorprint(i);
          delay(300);
          lcd.clear();
        }
        
        lcd.print("test");
        lcd.setCursor(2, 0);
        lcd.cursor();
        flag = 1;
      }
      
    }
  }



  char dig1, dig2, dig3, dig4;
  void mirrorprint(int num)
{
  String newnum = String(num);
  
  for (int i=0; i < 4; i++)
  {
    
    if (newnum[i]=='0') 
    lcd.print(0);   
    else if (newnum[i]=='1') lcd.write(1);
    else if (newnum[i]=='2') lcd.write(2);
    else if (newnum[i]=='3') lcd.write(3);
    else if (newnum[i]=='4') lcd.write(4);
    else if (newnum[i]=='5') lcd.write(5);
    else if (newnum[i]=='6') lcd.write(6);
    else if (newnum[i]=='7') lcd.write(7);
    else if (newnum[i]=='8') lcd.print(8);
    else if (newnum[i]=='9') lcd.write(8);
    
  }
}
