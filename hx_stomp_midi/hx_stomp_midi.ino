

#include <OneButton.h>
#include <MIDI.h>
#include <LiquidCrystal_I2C.h> // Biblioteca utilizada para fazer a comunicação com o display 20x4 

#define col 20 // Serve para definir o numero de colunas do display utilizado
#define lin  4 // Serve para definir o numero de linhas do display utilizado
#define ende  0x27 // Serve para definir o endereço do display.

LiquidCrystal_I2C lcd(ende,col,lin); // Chamada da funcação LiquidCrystal para ser usada com o I2C


// 48 ate 53 A   63 on 64 off
// 54 ate 59 B   63 on 64 off

/**  Button Config
      ---------
      | 1    2 |
      |        |
      |        |
      | 3    4 |
      ---------
*/

// configure buttons
OneButton button1(2, true, true);
OneButton button2(3, true, true);
OneButton button3(4, true, true);
OneButton button4(5, true, true);
OneButton button5(6, true, true);
OneButton button6(7, true, true);
OneButton button7(8, true, true);
OneButton button8(9, true, true);
// Create and bind the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();

boolean afinadorMode = false;
boolean stompMode = false;
boolean  modoAB = false;

const int efeitosMatrix[2][6] = {

                        {48, 49, 50, 51, 52 , 53 }, //A1 A2 A3 A4 A5 A6
                        {54, 55, 56, 57, 58 , 59 }  //B1 B2 B3 B4 B4 B6
                      };


boolean btnA1= true;
boolean btnA2= true;
boolean btnA3= true;
boolean btnA4= true;
boolean btnA5= true;
boolean btnA6= true;

boolean btnB1= true;
boolean btnB2= true;
boolean btnB3= true;
boolean btnB4= true;
boolean btnB5= true;
boolean btnB6= true;

void setup() {

  // button 1
  button1.attachClick(button1Press);
  button1.attachLongPressStart(button1LongPressStart);

  // button 2
  button2.attachClick(button2Press);
  button2.attachLongPressStart(button2LongPressStart);

  // button 3
  button3.attachClick(button3Press);
  button3.attachLongPressStart(button3LongPressStart);

  // button 4
  button4.attachClick(button4Press);
  button4.attachLongPressStart(button4LongPressStart);

  // button 5
  button5.attachClick(button5Press);
  button5.attachLongPressStart(button5LongPressStart);
  
  // button 6
  button6.attachClick(button6Press);
  button6.attachLongPressStart(button6LongPressStart);
  
  // button 7
  button7.attachClick(button7Press);
  button7.attachLongPressStart(button7LongPressStart);
  
  // button 8
  button8.attachClick(button8Press);
  button8.attachLongPressStart(button8LongPressStart);

  // MIDI setup
  MIDI.begin();

  lcd.init(); // Serve para iniciar a comunicação com o display já conectado
  lcd.backlight(); // Serve para ligar a luz do display
  lcd.clear(); // Serve para limpar a tela do display
}

void loop() {

  button1.tick();
  button2.tick();
  button3.tick();
  button4.tick();
  button5.tick();
  button6.tick();
  button7.tick();
  button8.tick();
  
}



void button1Press() {
  // banco +
   if(stompMode == false) {
      MIDI.sendControlChange(27, 0, 1);
   }else{
       if (modoAB == false){
        lcd.setCursor(0,3); 
        lcd.print("MOD-A");
           modoAB = true;
      }else{
        lcd.setCursor(0,3); 
        lcd.print("MOD-B");
           modoAB = false;
      }

   }
}

void button1LongPressStart() {
  // afinador
  if(stompMode == false) {
      if(afinadorMode == false){
        afinadorMode = true;
        lcd.setCursor(0,0); 
        lcd.print("AFIN");
        MIDI.sendControlChange(60, 64, 1);
      }else{
        afinadorMode = false;
        lcd.setCursor(0,0); 
        lcd.print("    ");
        MIDI.sendControlChange(60, 63, 1);
      }
      
   }else{

   
   }

  

  
}


void button2Press() {
  // banco -
   if(stompMode == false) {
    MIDI.sendControlChange(26, 0, 1);
   }else{
      if (modoAB == false){
        lcd.setCursor(0,3); 
        lcd.print("MOD-A");
           modoAB = true;
      }else{
        lcd.setCursor(0,3); 
        lcd.print("MOD-B");
           modoAB = false;
      }
   }

}

void button2LongPressStart() {
    if(stompMode == false){
      stompMode = true;
      lcd.setCursor(0,0); 
      lcd.print("STMP");
      lcd.setCursor(0,1); 
      lcd.print("A1 A2 A3 A4 A5 A6");
      lcd.setCursor(0,2); 
      lcd.print("B1 B2 B3 B4 B5 B6");
      //mudar tela para o mdo stomp
      MIDI.sendControlChange(28, 63, 1); 
    }else{
      stompMode = false;
      lcd.setCursor(0,0); 
      lcd.print("    ");
      MIDI.sendControlChange(28, 64, 1); 
    }
}

//{48, 49, 50, 51, 52 , 53 }, //A1 A2 A3 A4 A5 A6
//{54, 55, 56, 57, 58 , 59 }  //B1 B2 B3 B4 B4 B6

void button3Press() {
   
   if(stompMode==true && modoAB == false && btnA1 == true){
       lcd.setCursor(0,1); 
       lcd.print("A1 A2 A3 A4 A5 A6");
       btnA1 = false;
      MIDI.sendControlChange(48, 63, 1); 
   }else if (stompMode==true && modoAB == false && btnA1 == false){
      lcd.setCursor(0,1); 
      lcd.print("AA A2 A3 A4 A5 A6");
      btnA1 = true;
      MIDI.sendControlChange(48, 64, 1); 
   }
 
  if(stompMode==true && modoAB == true && btnB1 == true){
       lcd.setCursor(0,2); 
       lcd.print("B1 B2 B3 B4 B5 B6");
       btnB1 = false;
      MIDI.sendControlChange(54, 63, 1); 
   }else if (stompMode==true && modoAB == true && btnB1 == false){
      lcd.setCursor(0,2); 
      lcd.print("BB B2 B3 B4 B5 B6");
      btnB1 = true;
      MIDI.sendControlChange(54, 64, 1); 
   }
  

}

void button3LongPressStart() {

}

void button4Press() {
  
 //MIDI.sendControlChange(55, 64, 1); 
 //MIDI.sendControlChange(56, 64, 1); 
 //MIDI.sendControlChange(57, 64, 1); 
 //MIDI.sendControlChange(58, 64, 1); 
}

void button4LongPressStart() {

}



void button5Press() {
   //MIDI.sendControlChange(55, 63, 1); 
   //MIDI.sendControlChange(56, 63, 1); 
   //MIDI.sendControlChange(57, 63, 1); 
   //MIDI.sendControlChange(58, 63, 1); 

}

void button5LongPressStart() {
 

}

void button6Press() {
 
}

void button6LongPressStart() {
  
}


void button7Press() {
 
 
}

void button7LongPressStart() {
 

}

void button8Press() {
  
 
}

void button8LongPressStart() {
  

}

void pedalVolume(){

}

void pedalExpressao(){

}