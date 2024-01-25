//import libraries
#include <LiquidCrystal.h>

//define object and pin utilized
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
}


void loop()
{
  while(Serial.available()>0){
    //receive from node-RED a string containing the alarmCode and the temperature
    String reading=Serial.readString();
    //generate two different substring for the two values
    int firstIndex = reading.indexOf("-");
    String firstSubstring = reading.substring(0, firstIndex);
    int alarmCode=firstSubstring.toInt();
    int secondIndex = reading.indexOf("-", firstIndex + 1);
    String temperature = reading.substring(firstIndex + 1, secondIndex);

    Serial.println(alarmCode);
    Serial.println(temperature);
    long starttime = millis(); //timer to utilize in the display
    long endtime = starttime;
    switch(alarmCode){ //based on the alarm code, different messages are displayed
      case 1:   //Abnormal Temperature      
        while ((endtime - starttime) <=5000){// do this loop for up to 5000mS
          lcd.print("    " + temperature + " " +  ((char)223) + "C" );          
          lcd.setCursor(0, 1);
          lcd.print("     ALARM!     ");     
          delay(500);     
          lcd.clear();
          delay(500);
          lcd.print("ABNORMAL");
          lcd.setCursor(0, 1);
          lcd.print("TEMPERATURE");
          delay(500);
          lcd.clear();
          delay(500);
          endtime = millis();
        }
        break;
      case 2:   //Increasing Temperature 
        while ((endtime - starttime) <=5000){// do this loop for up to 5000mS
          lcd.print("    " + temperature + " " +  ((char)223) + "C" );          
          lcd.setCursor(0, 1);
          lcd.print("     ALARM!     ");     
          delay(500);     
          lcd.clear();
          delay(500);
          lcd.print("INCREASING");
          lcd.setCursor(0, 1);
          lcd.print("TEMPERATURE");
          delay(500);
          lcd.clear();
          delay(500);
          endtime = millis();        
        }
        break;
      case 3:   //Spike of Temperature
        while ((endtime - starttime) <=5000){// do this loop for up to 5000mS
          lcd.print("    " + temperature + " " +  ((char)223) + "C" );          
          lcd.setCursor(0, 1);
          lcd.print("     ALARM!     ");     
          delay(500);     
          lcd.clear();
          delay(500);
          lcd.print("SPIKE OF");
          lcd.setCursor(0, 1);
          lcd.print("TEMPERATURE");
          delay(500);
          lcd.clear();
          delay(500);
          endtime = millis();
        }
        break;
      case 0:   //Normal reading with no alarm
        while ((endtime - starttime) <=2000){// do this loop for up to 2000mS
          lcd.print("    " + temperature + " " +  ((char)223) + "C" );          
          lcd.setCursor(0, 1);
          lcd.print("      !OK!    ");
          endtime = millis();
        }
        break;
    }
  }
  lcd.clear();  
}

