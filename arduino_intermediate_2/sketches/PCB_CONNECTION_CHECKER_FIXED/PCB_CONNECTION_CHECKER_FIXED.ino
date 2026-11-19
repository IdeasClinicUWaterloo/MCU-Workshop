// SET UP PINS FOR TESTING
#define button_1 11
#define button_2 8
#define button_3 7
#define button_4 6
#define button_5 5
#define button_6 4
#define button_7 3
#define button_8 2

#define pot_1 A0
#define pot_2 A1
#define pot_3 A2
#define pot_4 A3
#define pot_5 A4


int pot_1_val, pot_2_val, pot_3_val, pot_4_val, pot_5_val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(button_3, INPUT_PULLUP);
  pinMode(button_4, INPUT_PULLUP);
  pinMode(button_5, INPUT_PULLUP);
  pinMode(button_6, INPUT_PULLUP);
  pinMode(button_7, INPUT_PULLUP);
  pinMode(button_8, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int button_1_state = digitalRead(button_1);
  int button_2_state = digitalRead(button_2);
  int button_3_state = digitalRead(button_3);
  int button_4_state = digitalRead(button_4);
  int button_5_state = digitalRead(button_5);
  int button_6_state = digitalRead(button_6);
  int button_7_state = digitalRead(button_7);
  int button_8_state = digitalRead(button_8);

  pot_1_val = analogRead(pot_1);
  pot_2_val = analogRead(pot_2);
  pot_3_val = analogRead(pot_3);
  pot_4_val = analogRead(pot_4);
  pot_5_val = analogRead(pot_5);
  
  
  // Serial.print("BUTTON STATES");
  Serial.print("Button 1 State: ");
  Serial.print(button_1_state);
  Serial.print(",");
  Serial.print("Button 2 State: ");
  Serial.print(button_2_state);
  Serial.print(",");
  Serial.print("Button 3 State: ");
  Serial.print(button_3_state);
  Serial.print(",");
  Serial.print("Button 4 State: ");
  Serial.print(button_4_state);
  Serial.print(",");
  Serial.print("Button 5 State: ");
  Serial.print(button_5_state);
  Serial.print(",");
  Serial.print("Button 6 State: ");
  Serial.print(button_6_state);
  Serial.print(",");
  Serial.print("Button 7 State: ");
  Serial.print(button_7_state);
  Serial.print(",");
  Serial.print("Button 8 State: ");
  Serial.print(button_8_state);
  Serial.print(",");
  // Serial.print("Pot Values");
  Serial.print("Pot 1 value: ");
  Serial.print(pot_1_val);
  Serial.print(",");
  Serial.print("Pot 2 value: ");
  Serial.print(pot_2_val);
  Serial.print(",");
  Serial.print("Pot 3 value: ");
  Serial.print(pot_3_val);
  Serial.print(",");
  Serial.print("Pot 4 value: ");
  Serial.print(pot_4_val);
  Serial.print(",");
  Serial.print("Pot 5 value: ");
  Serial.println(pot_5_val);

  delay(100);
}