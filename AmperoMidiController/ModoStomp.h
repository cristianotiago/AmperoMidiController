const int btnSelecionaveis[4][6] = {

                        {"A1", "A2", "A3", "A4", "A5", "A5" }, 
                        {"AA", "AB", "AC", "AD", "AE", "AF" }, 
                        {"B1", "B2", "B3", "B4", "B5", "B5" }, 
                        {"BA", "BB", "BC", "BD", "BE", "BF" } 
                      };

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
      boolean btnB6){
      String A = (btnA1 == true ? "AA" : "A1"); 
      //String B = (btnB1 == true ? "BA" : "B1"); 
       lcd.setCursor(0,1); 
       lcd.print(" "+String(A)+" A2 A3 A4 A5 A6");
       //lcd.setCursor(0,2); 
       //lcd.print(" "+String(B)+" B2 B3 B4 B5 B6");
     
}