
#include "DFRobot_DF2301Q.h"

#define Led 8
#define fan 9
//I2C communication
DFRobot_DF2301Q_I2C asr;

void setup() {
  Serial.begin(115200);
  pinMode(Led, OUTPUT);    //Init LED pin to output mode
  pinMode(fan, OUTPUT);    
  digitalWrite(fan, LOW);  
  digitalWrite(Led, LOW);  //Set LED pin to low 

  // Init the sensor
  while (!(asr.begin())) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  /**
   * @brief Set voice volume
   * @param voc - Volume value(1~7)
   */
  asr.setVolume(4);

  /**
     @brief Set mute mode
     @param mode - Mute mode; set value 1: mute, 0: unmute
  */
  asr.setMuteMode(0);

  /**
     @brief Set wake-up duration
     @param wakeTime - Wake-up duration (0-255)
  */
  asr.setWakeTime(20);

  /**
     @brief Get wake-up duration
     @return The currently-set wake-up period
  */
  uint8_t wakeTime = 0;
  wakeTime = asr.getWakeTime();
  Serial.print("wakeTime = ");
  Serial.println(wakeTime);

   asr.playByCMDID(1);   // Wake-up command

  /**
     @brief Play the corresponding reply audio according to the ID
     @param CMDID - command word ID
  */
  //asr.playByCMDID(23);  // Command word ID
}

void loop() {
  /**
     @brief Get the ID corresponding to the command word 
     @return Return the obtained command word ID, returning 0 means no valid ID is obtained
  */
  uint8_t CMDID = asr.getCMDID();
  switch (CMDID) {
    case 103:      //If the command is “Turn on the light”
      digitalWrite(Led, LOW);  //Turn on the LED
      Serial.println("received'Turn on the light',command flag'103'");  //Serial transmits "received"Turn on the light",command flag"103
      break;
    case 104:     //If the command is “Turn off the light”
      digitalWrite(Led, HIGH);  //Turn off the LED
      Serial.println("received'Turn off the light',command flag'104'");  //The serial transmits "received"Turn off the light",command flag"104""
      break;
    case 75:     //If the command is “Turn on the fan”
      digitalWrite(fan, HIGH);                                 
      Serial.println("received'Turn on the fan',command flag'75'");  
      break;
    case 76:    //If the command is “Turn off the fan”
      digitalWrite(fan, LOW);                            
      Serial.println("received'Turn off the fan',command flag'76'");  
      break;

   
    default:
      if (CMDID != 0) {
        Serial.print("CMDID = ");  //Printing command ID
        Serial.println(CMDID);
      }
  }
  delay(300);
}
