byte Tapp1_IN_Pin = 2;
byte Tapp1_OUT_Pin_UP = 3;
byte Tapp1_OUT_Pin_DOWN = 4;
int Tapp1_UP_duration = 25000;
int Tapp1_DOWN_duration = 19000;

byte Tapp1_lastValue;
byte Tapp1_lastMode; // 0=STOP 1=UP  2=DOWN
long Tapp1_lastExec;

byte Tapp2_IN_Pin = 5;
byte Tapp2_OUT_Pin_UP = 6;
byte Tapp2_OUT_Pin_DOWN = 7;
int Tapp2_UP_duration = 15000;
int Tapp2_DOWN_duration = 11000;

byte Tapp2_lastValue;
byte Tapp2_lastMode; // 0=STOP 1=UP  2=DOWN
long Tapp2_lastExec;

byte LOW_OUT = HIGH;
byte HIGH_OUT = LOW;


int inverted_delay = 500;

void setup() {

  Serial.begin(9600);
  Serial.println("SETUP TAPP MODE");
  
  pinMode(Tapp1_IN_Pin, INPUT_PULLUP);
  pinMode(Tapp1_OUT_Pin_UP, OUTPUT);
  pinMode(Tapp1_OUT_Pin_DOWN, OUTPUT); 
  digitalWrite(Tapp1_OUT_Pin_UP, LOW_OUT);
  digitalWrite(Tapp1_OUT_Pin_DOWN, LOW_OUT);
  Tapp1_lastValue = HIGH;
  Tapp1_lastMode = 0;

  pinMode(Tapp2_IN_Pin, INPUT_PULLUP);
  pinMode(Tapp2_OUT_Pin_UP, OUTPUT);
  pinMode(Tapp2_OUT_Pin_DOWN, OUTPUT); 
  digitalWrite(Tapp2_OUT_Pin_UP, LOW_OUT);
  digitalWrite(Tapp2_OUT_Pin_DOWN, LOW_OUT);
  Tapp2_lastValue = HIGH;
  Tapp2_lastMode = 0;
  
  Serial.println("SETUP TAPP MODE");
}

void checkTAPP(byte Tapp_idx, byte IN_Pin, byte OUT_Pin_UP, byte OUT_Pin_DOWN,
byte &lastValue, byte &lastMode, long &lastExec,
int UP_duration, int DOWN_duration)
{
  byte currentValue = digitalRead(IN_Pin);
  Serial.print(F("TAPP"));
  Serial.print(Tapp_idx);
  Serial.print(F("_IN_VALUE: "));
  Serial.print(currentValue);
  Serial.print(F(" VS LAST_VALUE: "));
  Serial.println((byte)lastValue); 
  if (currentValue != lastValue)
  {
    lastValue = currentValue;

    if (currentValue == HIGH)
    {
      digitalWrite(OUT_Pin_DOWN, LOW_OUT);
      if (lastMode != 0)
      {
        delay(inverted_delay);
      }
      digitalWrite(OUT_Pin_UP, HIGH_OUT);
      lastMode = 1;
      Serial.print(F("START TAPP"));
      Serial.print(Tapp_idx);
      Serial.println(F(" UP"));
    }
    else if(currentValue == LOW)
    {
      digitalWrite(OUT_Pin_UP, LOW_OUT);
      if (lastMode != 0)
      {
        delay(inverted_delay);
      }
      digitalWrite(OUT_Pin_DOWN, HIGH_OUT );
      lastMode = 2;
      Serial.print(F("START TAPP"));
      Serial.print(Tapp_idx);
      Serial.println(F(" DOWN"));
    }
    lastExec = millis();
  }

  if ( (lastMode == 1 && millis() > lastExec + UP_duration ) ||  
       (lastMode == 2 && millis() > lastExec + DOWN_duration) )
  {
      digitalWrite(OUT_Pin_DOWN, LOW_OUT);
      digitalWrite(OUT_Pin_UP, LOW_OUT);
      lastMode = 0;
      
      Serial.print(F("STOP TAPP"));
      Serial.println(Tapp_idx);
  }
}

void loop() {

  checkTAPP(1, Tapp1_IN_Pin, Tapp1_OUT_Pin_UP, Tapp1_OUT_Pin_DOWN,
                Tapp1_lastValue, Tapp1_lastMode, Tapp1_lastExec,
                Tapp1_UP_duration, Tapp1_DOWN_duration);
                
  checkTAPP(2, Tapp2_IN_Pin, Tapp2_OUT_Pin_UP, Tapp2_OUT_Pin_DOWN,
               Tapp2_lastValue, Tapp2_lastMode, Tapp2_lastExec,
                Tapp2_UP_duration, Tapp2_DOWN_duration); 
}
