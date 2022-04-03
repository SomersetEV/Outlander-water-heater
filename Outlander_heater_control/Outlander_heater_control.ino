int ThermistorPin = 18;
int Vo;
//int T;
float R1 = 100000;
float logR2, R2, T;
float o;
float c1 = 1.161003704 - 03, c2 = 1.616884180e-04, c3 = 3.151304262e-07;

//Control pins for heater
int temp1 = 5;
int temp2 = 6;
int temp3 = 7;
int tempcontrol = A0;
int tempValue = 0;
int heatsetting = 0;

void setup() {
  Serial.begin(9600);

  // setup pins
  pinMode(temp1, OUTPUT);
  pinMode(temp2, OUTPUT);
  pinMode(temp3, OUTPUT);

  pinMode(ThermistorPin, INPUT);
}

void gettemp() {

  o = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 273.15;
}

void getheatsetting() {
  tempValue = analogRead(tempcontrol);
  // decide on readings for 3 settings and return 1,2 or 3.
}


void tempsetting1() {
  gettemp();
  {
    if (T < 30) {
      digitalWrite(temp1, HIGH);
      digitalWrite(temp2, HIGH);
      digitalWrite(temp3, HIGH);
    }
    if (T > 30) {
      digitalWrite(temp1, HIGH);
      digitalWrite(temp2, HIGH);
      digitalWrite(temp3, LOW);
    }
    if (T > 35) {
      digitalWrite(temp1, HIGH);
      digitalWrite(temp2, LOW);
      digitalWrite(temp3, LOW);
    }
    if (T > 40) {
      digitalWrite(temp1, LOW);
      digitalWrite(temp2, LOW);
      digitalWrite(temp3, LOW);
    }
  }

  //  set heater to setting 2 until set temp hit, reduce heater setting to temp 1 unless it fals below temp
  //  if goes above something above set temp switch off heater.

}

void tempsetting2() {}
void tempsetting3() {}


void loop() {

  getheatsetting();
  if ( heatsetting == 1) {
    tempsetting1();
  }
  else if ( heatsetting == 2) {
    tempsetting2();
  }
  else if ( heatsetting == 3) {
    tempsetting3();
  }
  else
    digitalWrite(temp1, LOW);
  digitalWrite(temp2, LOW);
  digitalWrite(temp3, LOW);

  /*
    If on button input is on and temp 1 is on
    The run void tempsetting1
    else If on button input is on and temp 2 is on
    The run void tempsetting2
    else If on button input is on and temp 3 is on
    The run void tempsetting3
    else If on button input is on and temp 4 is on
    The run void tempsetting4
    Otherwise stay off, but only switch pump off when temp down to a set place.

    delay maybe

  */
}
