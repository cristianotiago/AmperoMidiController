#include <OneButton.h>
#include <MIDI.h>
#include <LiquidCrystal_I2C.h>  // Biblioteca utilizada para fazer a comunicação com o display 20x4


int expPin1 = 0;
int currentVal1 = 0;
int lastVal1 = 0;

/*
int expPin2 = 0;
int currentVal2 = 0;
int lastVal2 = 0;
*/

#define colunas 20     // Serve para definir o numero de colunas do display utilizado
#define linhas 4       // Serve para definir o numero de linhas do display utilizado
#define endereco 0x27  // Serve para definir o endereço do display.

LiquidCrystal_I2C lcd(endereco, colunas, linhas);  // Chamada da funcação LiquidCrystal para ser usada com o I2C


// 48 ate 53 A   63 on 64 off
// 54 ate 59 B   63 on 64 off

/**  Button Config
      ------------------
      | 1    2   3   4 |
      |                |
      |                |
      | 3    4   5   6 |
      ------------------
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
boolean naoEhAouB = true;
/*
boolean modoAB = false;

boolean isStompMode = true;
*/


boolean btnA1 = true;
boolean btnA2 = true;
boolean btnA3 = true;
boolean btnA4 = true;
boolean btnA5 = true;
boolean btnA6 = true;

boolean btnB1 = true;
boolean btnB2 = true;
boolean btnB3 = true;
boolean btnB4 = true;
boolean btnB5 = true;
boolean btnB6 = true;



#include "ModoStomp.h"
#include "LargeFonts.h"



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

  lcd.init();       // Serve para iniciar a comunicação com o display já conectado
  lcd.backlight();  // Serve para ligar a luz do display
  lcd.clear();      // Serve para limpar a tela do display

  for (nb = 0; nb < 8; nb++) {  // create 8 custom characters
    for (bc = 0; bc < 8; bc++) bb[bc] = pgm_read_byte(&custom[nb][bc]);
    lcd.createChar(nb + 1, bb);
  }
  telaStart();
  seletorStomp(true, true, true, true, true, true, true, true, true, true, true, true, true);
}

void telaStart() {

  writeBigString("A M P E 2", 0, 0);
  writeBigString("  M I D I", 0, 2);
  delay(2000);
  lcd.clear();
}

void isStomp(boolean valor) {
  stompMode = valor;
}

void ativarStomp(boolean valor) {
  if (stompMode == false) {
    MIDI.sendControlChange(28, 63, 1);
    isStomp(valor);
  } else if (stompMode == true) {
    MIDI.sendControlChange(28, 64, 1);
    isStomp(valor);
  }
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
  pedalExpressao();
  //pedalVolume();
}

void pedalExpressao() {
  currentVal1 = analogRead(expPin1);
  currentVal1 = map(currentVal1, 0, 1023, 0, 127);
  currentVal1 = constrain(currentVal1, 0, 127);
  if (abs(currentVal1 - lastVal1) > 1) {
    MIDI.sendControlChange(11, currentVal1, 1);
  }

  lastVal1 = currentVal1;
  delay(5);
}
/*
void pedalVolume() {
  currentVal2 = analogRead(expPin2);
  currentVal2 = map(currentVal2, 0, 1023, 0, 100);
  currentVal2 = constrain(currentVal2, 0, 100);
  if (abs(currentVal2 - lastVal2) > 1) {
    MIDI.sendControlChange(7, currentVal2, 1);
  }

  lastVal2 = currentVal2;
  delay(5);
}
*/

void button1Press() {
  //banco para cima
  lcd.clear();

  writeBigString("  B A N K", 0, 0);
  writeBigString("      U P", 0, 2);
  enviarControlChange(27, 0, 1);
}

void button1LongPressStart() {
  if (naoEhAouB == true) {
    naoEhAouB = false;
    seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
  } else {
    naoEhAouB = true;
    seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
  }
}


void button2Press() {
  //banco para baixo
  lcd.clear();

  writeBigString("  B A N K", 0, 0);
  writeBigString("      D N", 0, 2);
  enviarControlChange(26, 0, 1);
}

void button2LongPressStart() {
  //afinador
  if (afinadorMode == false) {
    isAfinador(true);
    lcd.clear();
    writeBigString("T U N E R", 0, 1);
    enviarControlChange(60, 64, 1);
  } else if (afinadorMode == true) {
    isAfinador(false);
    lcd.clear();
    writeBigString("         ", 0, 1);
    seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    enviarControlChange(60, 63, 1);
  }
}

void isAfinador(boolean valor) {
  afinadorMode = valor;
}
//{48, 49, 50, 51, 52 , 53 }, //A1 A2 A3 A4 A5 A6
//{54, 55, 56, 57, 58 , 59 }  //B1 B2 B3 B4 B4 B6

void button3Press() {
  if (naoEhAouB == true) {
    if (btnA1 == true) {
      btnA1 = false;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    } else if (btnA1 == false) {
      btnA1 = true;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    }
  } else if (naoEhAouB == false) {
    if (btnB1 == true) {
      btnB1 = false;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    } else if (btnB1 == false) {
      btnB1 = true;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    }
  }
}

void button3LongPressStart() {


  if (stompMode == false) {
    ativarStomp(true);
    lcd.clear();
    writeBigString("S T O M P", 0, 1);
  }else if(stompMode ==true){
    ativarStomp(false);
    lcd.clear();
    writeBigString("P A T C H", 0, 1);
  }
}

void button4Press() {
  if (naoEhAouB == true) {
    if (btnA2 == true) {
      btnA2 = false;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    } else if (btnA2 == false) {
      btnA2 = true;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    }
  } else if (naoEhAouB == false) {
    if (btnB2 == true) {
      btnB2 = false;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    } else if (btnB2 == false) {
      btnB2 = true;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    }
  }
}

void button4LongPressStart() {
}


void button5Press() {
  if (naoEhAouB == true) {
    if (btnA3 == true) {
      btnA3 = false;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    } else if (btnA3 == false) {
      btnA3 = true;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    }
  } else if (naoEhAouB == false) {
    if (btnB3 == true) {
      btnB3 = false;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    } else if (btnB3 == false) {
      btnB3 = true;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    }
  }
}

void button5LongPressStart() {
}

void button6Press() {
  if (naoEhAouB == true) {
    if (btnA4 == true) {
      btnA4 = false;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    } else if (btnA4 == false) {
      btnA4 = true;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    }
  } else if (naoEhAouB == false) {
    if (btnB4 == true) {
      btnB4 = false;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    } else if (btnB4 == false) {
      btnB4 = true;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    }
  }
}

void button6LongPressStart() {
}


void button7Press() {
  if (naoEhAouB == true) {
    if (btnA5 == true) {
      btnA5 = false;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    } else if (btnA5 == false) {
      btnA5 = true;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    }
  } else if (naoEhAouB == false) {
    if (btnB5 == true) {
      btnB5 = false;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    } else if (btnB5 == false) {
      btnB5 = true;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    }
  }
}

void button7LongPressStart() {
}

void button8Press() {
  if (naoEhAouB == true) {
    if (btnA6 == true) {
      btnA6 = false;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    } else if (btnA6 == false) {
      btnA6 = true;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    }
  } else if (naoEhAouB == false) {
    if (btnB6 == true) {
      btnB6 = false;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    } else if (btnB6 == false) {
      btnB6 = true;
      seletorStomp(btnA1, btnA2, btnA3, btnA4, btnA5, btnA6, btnB1, btnB2, btnB3, btnB4, btnB5, btnB6, naoEhAouB);
    }
  }
}


void button8LongPressStart() {
}
