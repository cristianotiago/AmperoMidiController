/*const int btnSelecionaveis[4][6] = {

                        {"A1", "A2", "A3", "A4", "A5", "A5" }, 
                        {"AA", "AB", "AC", "AD", "AE", "AF" }, 
                        {"B1", "B2", "B3", "B4", "B5", "B5" }, 
                        {"BA", "BB", "BC", "BD", "BE", "BF" } 
                      };
*/
void seletorStomp(
      boolean btnA1,
      boolean btnA2,
      boolean btnA3,
      boolean btnA4,
      boolean btnA5,
      boolean btnA6,
      boolean btnB1,
      boolean btnB2,
      boolean btnB3,
      boolean btnB4,
      boolean btnB5,
      boolean btnB6,
      boolean naoEhAouB){

      String aA1 = (btnA1 == true ? "AA" : "A1"); 
      String aA2 = (btnA2 == true ? "AB" : "A2"); 
      String aA3 = (btnA3 == true ? "AC" : "A3"); 
      String aA4 = (btnA4 == true ? "AD" : "A4"); 
      String aA5 = (btnA5 == true ? "AE" : "A5"); 
      String aA6 = (btnA6 == true ? "AF" : "A6"); 

      String bB1 = (btnB1 == true ? "BA" : "B1"); 
      String bB2 = (btnB2 == true ? "BB" : "B2"); 
      String bB3 = (btnB3 == true ? "BC" : "B3"); 
      String bB4 = (btnB4 == true ? "BD" : "B4"); 
      String bB5 = (btnB5 == true ? "BE" : "B5"); 
      String bB6 = (btnB6 == true ? "BF" : "B6"); 
      
      lcd.setCursor(0,1); 
      lcd.print(" "+String(aA1)+" "+String(aA2)+" "+String(aA3)+" "+String(aA4)+" "+String(aA5)+" "+String(aA6)+String(naoEhAouB == true ? "<" : " "));
      lcd.setCursor(0,2); 
      lcd.print(" "+String(bB1)+" "+String(bB2)+" "+String(bB3)+" "+String(bB4)+" "+String(bB5)+" "+String(bB6)+String(naoEhAouB != true ? "<" : " "));
     
}

void enviarControlChange(int controlNumber, int controlValue, int channel ){
  MIDI.sendControlChange(controlNumber, controlValue, channel); 
}