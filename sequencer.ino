/*
 * For each module (50,144,432,1296) there are 4 possibile states.
 *      on/off flip | PTT   |   LNA   | PA    |
 *    ---------------------------------------------
 *  1       OFF     | OFF   |   OFF   | OFF   | everything off
 *  2       OFF     | ON    |   OFF   | ON    | using PA but not LNA
 *  3       ON      | OFF   |   ON    | OFF   | using LNA, not on TX
 *  4       ON      | ON    |   OFF   | ON    | using LNA, on TX
 *  transitioning between states 3 and 4 requires sequencing
 *  
 */

  int debug = 0;
  
  // pin assignments
  int flip50 = A0;
  int flip144 = A1;
  int flip432 = A2;
  int flip1296 = A3;
  int lna50 = 3;
  int lna144 = 12;
  int lna432 = A5;
  int lna1296 = A4;
  int pttpin50 = 11;
  int pttpin144 = 10;
  int pttpin432 = 9;
  int pttpin1296 = 8;
  int pa50 = 4;
  int pa144 = 5;
  int pa432 = 6;
  int pa1296 = 7;

  // variables needed for each band
  bool sw50;          // status of on/off switch
  int tx50 = 0;  // status of PA
  int ptt50;         // status of PTT from radio
  int prev50 = 1;    // previous status
  int time50 = 10;   // switching delay
  
  bool sw144;
  bool tx144 = 0; 
  bool ptt144;
  bool prev144 = 1;
  int  time144 = 10;   // switching delay
  
  bool sw432;
  bool tx432 = 0;
  bool ptt432;
  bool prev432 = 1;
  int  time432 = 10;   // switching delay

  
  bool sw1296;
  bool tx1296 = 0;
  bool ptt1296;
  bool prev1296 = 1;
  int  time1296 = 10;   // switching delay


void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);

  //switch on off
  pinMode(flip50, INPUT_PULLUP); 
  pinMode(flip144, INPUT_PULLUP);
  pinMode(flip432, INPUT_PULLUP);
  pinMode(flip1296, INPUT_PULLUP);

  //rx led + LNA on
  pinMode(lna50, OUTPUT);
  pinMode(lna144, OUTPUT);
  pinMode(lna432, OUTPUT);
  pinMode(lna1296, OUTPUT);
  
  //PTT sense
  pinMode(pttpin50, INPUT_PULLUP);
  pinMode(pttpin144, INPUT_PULLUP);
  pinMode(pttpin432, INPUT_PULLUP);
  pinMode(pttpin1296, INPUT_PULLUP);  

  //PA control
  pinMode(pa50, OUTPUT);
  pinMode(pa144, OUTPUT);
  pinMode(pa432, OUTPUT); 
  pinMode(pa1296, OUTPUT);
}

void loop() {
  // ====== 50MHz ======
  sw50 = digitalRead(flip50);
  ptt50 = digitalRead(pttpin50);
  if (debug==2){
    Serial.print("PTT 50 - ");
    Serial.println(ptt50);}
  
  // status 3 and 4
  if (sw50 == 1){
    //RX to TX
    if ((ptt50 == 0) && (prev50 == 1)){
      digitalWrite(lna50,LOW); //switch off LNA
      delay(time50);
      digitalWrite(pa50,HIGH); //switch on PA
      prev50 = 0;
      if (debug==1){Serial.println("LNA - RX to TX 50");}
      }
    //TX to RX
    if((ptt50 == 1) && (prev50 == 0)){
      digitalWrite(pa50,LOW); //switch off PA
      delay(time50);
      digitalWrite(lna50,HIGH); //switch on LNA
      prev50 = 1;
      if (debug==1){
        Serial.print("LNA - TX to RX 50 - prev ");
        Serial.print(prev50);
        }
      }
    //standby with LNA on if switched
    if ((ptt50 == 1) && (prev50 == 1)){
      digitalWrite(lna50,HIGH); //switch on LNA
      if (debug==1){Serial.println("LNA - 50");}
      }
    } 
    // status 1 and 2
    if (sw50 == 0){
      digitalWrite(lna50,LOW); //switch off LNA
      if (ptt50 == 0){digitalWrite(pa50, HIGH);} else {digitalWrite(pa50, LOW);}
      if (debug==1){Serial.println("noLNA - RX to TX 50");}

  }
  
  // ====== 144MHz ======
  sw144 = digitalRead(flip144);
  ptt144 = digitalRead(pttpin144);
  if (debug==2){
    Serial.print("PTT 144 - ");
    Serial.println(ptt144);}
  // status 3 and 4
  if (sw144 == 1){
    //RX to TX
    if ((ptt144 == 0) && (prev144 == 1)){
      digitalWrite(lna144,LOW); //switch off LNA
      delay(time144);
      digitalWrite(pa144,HIGH); //switch on PA
      prev144 = 0;
      }
    //TX to RX
    if((ptt144 == 1) && (prev144 == 0)){
      digitalWrite(pa144,LOW); //switch off PA
      delay(time144);
      digitalWrite(lna144,HIGH); //switch on LNA
      prev144 = 1;
      }
    //standby with LNA on if switched
    if ((ptt144 == 1) && (prev144 == 1)){
      digitalWrite(lna144,HIGH); //switch on LNA
      }
    } 
    // status 1 and 2
    else if (sw144 == 0){
      digitalWrite(lna144,LOW); //switch off LNA
      if (ptt144 == 0){digitalWrite(pa144, HIGH);} else {digitalWrite(pa144, LOW);}
  }

  // ====== 432MHz ======
  sw432 = digitalRead(flip432);
  ptt432 = digitalRead(pttpin432);
  if (debug==2){
    Serial.print("PTT 432 - ");
    Serial.println(ptt432);}
  // status 3 and 4
  if (sw432 == 1){
    //RX to TX
    if ((ptt432 == 0) && (prev432 == 1)){
      digitalWrite(lna432,LOW); //switch off LNA
      delay(time432);
      digitalWrite(pa432,HIGH); //switch on PA
      prev432 = 0;
      }
    //TX to RX
    if((ptt432 == 1) && (prev432 == 0)){
      digitalWrite(pa432,LOW); //switch off PA
      delay(time432);
      digitalWrite(lna432,HIGH); //switch on LNA
      prev432 = 1;
      }
    //standby with LNA on if switched
    if ((ptt432 == 1) && (prev432 == 1)){
      digitalWrite(lna432,HIGH); //switch on LNA
      }
    } 
    // status 1 and 2
    else if (sw432 == 0){
      digitalWrite(lna432,LOW); //switch off LNA
      if (ptt432 == 0){digitalWrite(pa432, HIGH);} else {digitalWrite(pa432, LOW);}
  }

  // ====== 1296MHz ======
  sw1296 = digitalRead(flip1296);
  ptt1296 = digitalRead(pttpin1296);
  if (debug==2){
    Serial.print("PTT 1296 - ");
    Serial.println(ptt1296);}
  // status 3 and 4
  if (sw1296 == 1){
    //RX to TX
    if ((ptt1296 == 0) && (prev1296 == 1)){
      digitalWrite(lna1296,LOW); //switch off LNA
      delay(time1296);
      digitalWrite(pa1296,HIGH); //switch on PA
      prev1296 = 0;
      }
    //TX to RX
    if((ptt1296 == 1) && (prev1296 == 0)){
      digitalWrite(pa1296,LOW); //switch off PA
      delay(time1296);
      digitalWrite(lna1296,HIGH); //switch on LNA
      prev1296 = 1;
      }
    //standby with LNA on if switched
    if ((ptt1296 == 1) && (prev1296 == 1)){
      digitalWrite(lna1296,HIGH); //switch on LNA
      }
    } 
    // status 1 and 2
    else if (sw1296 == 0){
      digitalWrite(lna1296,LOW); //switch off LNA
      if (ptt1296 == 0){digitalWrite(pa1296, HIGH);} else {digitalWrite(pa1296, LOW);}
  }

  //delay(500);

  }
