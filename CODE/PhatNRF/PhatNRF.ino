
#include <Keypad.h>
#include <Wire.h>;
#include <SPI.h>

#include "RF24.h"


const uint64_t pipes[2] = {0x10F0FAF0E1LL, 0x50F0C0F0D2LL };
RF24 radio(9,10);

#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C lcd(0x3F,16,2);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A3, A2, A1, A0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


uint8_t out, gohome;


String getString(int Length, char EscapeChar) {    // hàm này dùng để đọc số nhập vào                 
   String currentString="";                                                                       
  int count = 0;                                                                        
  char currentKey;
  while (customKeypad.getKey() != EscapeChar){                                              
    delay(100);                                                                  
  //if( matrix.keyStateChanged() )        
    currentKey = customKeypad.getKey();
    if( currentKey == 'D') {out =1; break;}
    if( currentKey == 'B') {gohome =1; break;}
    if( currentKey != NO_KEY){                                              
        if (currentKey != EscapeChar)
        {   
          lcd.print(currentKey);                               
          currentString += currentKey;                                    
         count ++;
         delay(200);                                                          
        if (count >= Length)
        {      
                                              
        return currentString;                                   
        }                                                                     
    }                                                                       
    else {       
      //added this line 4-20-2012 RW
      return currentString;                                          
    }                                                                               
    }                                                                              
  }                                                                                      
} 


void setup() {
  // put your setup code here, to run once:
  lcd.init();       //Khởi động màn hình. Bắt đầu cho phép Arduino sử dụng màn hình
  lcd.backlight();   //Bật đèn nền 
  radio.begin();
  radio.setChannel(1);               // Đặt kênh
  radio.setAutoAck(1);  
  radio.setRetries(1,1);
  radio.setDataRate(RF24_1MBPS);    // Tốc độ truyền
  radio.setPALevel(RF24_PA_MAX);      // Dung lượng tối đa 
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  Serial.begin(9600);
  lcd.setCursor(0,1);
  lcd.print("Bam A de nhap MK");
  lcd.setCursor(0,0);
  lcd.print(" DIEU KHIEN RF  ");

}

uint32_t pass=0, re_pass;

uint32_t ping=0, count;

void loop() {
  // put your main code here, to run repeatedly:

  char customKey = customKeypad.getKey();
  
  if(customKey=='A')
  {
    check:
    customKey = 0;
    lcd.setCursor(0,0);
    lcd.print("Nhap MK:        ");
    lcd.setCursor(0,1);
    lcd.print("press # finish  ");
    lcd.setCursor(8,0); 
    String test = getString(9,'#');
    if(gohome==1) 
    {
      gohome =0;
      goto tohome;
    }
    if(out==0)
    {
    uint8_t time_out=10;
    lcd.setCursor(0,0);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("Dang Gui...      ");
   
    //radio.write(&pass, sizeof(pass));
    
    Serial.print("#");
    Serial.println(test);
    delay(200);
    //send nrf
    tohome:
    lcd.setCursor(0,1);
    lcd.print("Bam A de nhap MK");
    lcd.setCursor(0,0);
    lcd.print(" DIEU KHIEN NRF");
    customKey = 0;
    }
    else
    { 
    out=0;
    goto check;
    }
    }


  
}
