/*const int btnSelecionaveis[4][6] = {

                        {"A1", "A2", "A3", "A4", "A5", "A5" }, 
                        {"AA", "AB", "AC", "AD", "AE", "AF" }, 
                        {"B1", "B2", "B3", "B4", "B5", "B5" }, 
                        {"BA", "BB", "BC", "BD", "BE", "BF" } 
                      };
*/


const int efeitosMatrix[2][6] = {

                        {48, 49, 50, 51, 52 , 53 }, //A1 A2 A3 A4 A5 A6
                        {54, 55, 56, 57, 58 , 59 }  //B1 B2 B3 B4 B4 B6
                      };

void enviarControlChange(int controlNumber, int controlValue, int channel ){
  MIDI.sendControlChange(controlNumber, controlValue, channel); 
}

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
      lcd.clear();
      lcd.setCursor(0,1); 
      lcd.print(" "+String(aA1)+" "+String(aA2)+" "+String(aA3)+" "+String(aA4)+" "+String(aA5)+" "+String(aA6)+String(naoEhAouB == true ? "<" : " "));
      lcd.setCursor(0,2); 
      lcd.print(" "+String(bB1)+" "+String(bB2)+" "+String(bB3)+" "+String(bB4)+" "+String(bB5)+" "+String(bB6)+String(naoEhAouB != true ? "<" : " "));
     
     int sA1 = (btnA1 == true ? 64 : 63);
     int sA2 = (btnA2 == true ? 64 : 63);
     int sA3 = (btnA3 == true ? 64 : 63);
     int sA4 = (btnA4 == true ? 64 : 63);
     int sA5 = (btnA5 == true ? 64 : 63);
     int sA6 = (btnA6 == true ? 64 : 63);

     int sB1 = (btnB1 == true ? 64 : 63); 
     int sB2 = (btnB2 == true ? 64 : 63); 
     int sB3 = (btnB3 == true ? 64 : 63); 
     int sB4 = (btnB4 == true ? 64 : 63); 
     int sB5 = (btnB5 == true ? 64 : 63); 
     int sB6 = (btnB6 == true ? 64 : 63); 

/*
{48, 49, 50, 51, 52 , 53 }, //A1 A2 A3 A4 A5 A6
{54, 55, 56, 57, 58 , 59 }  //B1 B2 B3 B4 B4 B6
*/
     enviarControlChange(efeitosMatrix[0][0], sA1, 1);
     enviarControlChange(efeitosMatrix[0][1], sA2, 1);
     enviarControlChange(efeitosMatrix[0][2], sA3, 1);
     enviarControlChange(efeitosMatrix[0][3], sA4, 1);
     enviarControlChange(efeitosMatrix[0][4], sA5, 1);
     enviarControlChange(efeitosMatrix[0][5], sA6, 1);

     enviarControlChange(efeitosMatrix[1][0], sB1, 1);
     enviarControlChange(efeitosMatrix[1][1], sB2, 1);
     enviarControlChange(efeitosMatrix[1][2], sB3, 1);
     enviarControlChange(efeitosMatrix[1][3], sB4, 1);
     enviarControlChange(efeitosMatrix[1][4], sB5, 1);
     enviarControlChange(efeitosMatrix[1][5], sB6, 1);
}

