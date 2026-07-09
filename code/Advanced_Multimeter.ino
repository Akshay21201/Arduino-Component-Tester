#include <LiquidCrystal.h>

// *Initialize LCD: RS=12, E=11, D4=5, D5=4, D6=3, D7=2*
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// *Pin Assignments*
const int nextButton = 0;  // Next button (D0)
const int okButton = 10;    // OK/Cancel button (D1)

const int resistorPin = A0;
const int inductorPin = A1;
const int inductorCharge = 8;
const int capacitorPin = A2;
const int chargePin = 13;
const int dischargePin = 9;
const int diodePin = A3;
const int bjtBase = 6;
const int bjtCollector = A5;
const int bjtEmitter = A4;
const int nmosGate = 7;
const int pmosGate = 7;

// *Constants*
const float Vin = 5.0;
const float R1 = 100000; // Known resistor
const float inductorResistance = 1000.0;  // 1kΩ resistor
const float capacitorResistor = 10000.0;  // 10kΩ resistor

int mode = 0;  // Current test mode
bool testRunning = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  // Initialize digital pins
  pinMode(inductorCharge, OUTPUT);
  pinMode(chargePin, OUTPUT);
  pinMode(dischargePin, OUTPUT);
  pinMode(nmosGate, OUTPUT);
  pinMode(pmosGate, OUTPUT);
  pinMode(bjtBase, OUTPUT);

  digitalWrite(inductorCharge, LOW);
  digitalWrite(chargePin, LOW);
  digitalWrite(dischargePin, LOW);
  digitalWrite(nmosGate, LOW);
  digitalWrite(pmosGate, LOW);

  // *Initialize buttons with internal pull-up resistors*
  pinMode(nextButton, INPUT_PULLUP);
  pinMode(okButton, INPUT_PULLUP);

  showMenu();
}

void loop() {
  if (digitalRead(nextButton) == LOW){
    delay(300);  // Debounce
    mode = (mode + 1) % 8;  // Cycle through 6 modes
    showMenu();
  }

  if (digitalRead(okButton) == LOW) {
    delay(300);  // Debounce
    testRunning = !testRunning;  // Toggle test
    if (testRunning) {
      runTest();
    } else {
      showMenu();
    }
  }
}

// *Display Menu*
void showMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select Test:");
  lcd.setCursor(0, 1);
  switch (mode) {
    case 0: lcd.print("Resistor"); break;
    case 1: lcd.print("Inductor"); break;
    case 2: lcd.print("Capacitor"); break;
    case 3: lcd.print("Diode"); break;
    case 4: lcd.print("LED"); break;
    case 5: lcd.print("BJT"); break;
    case 6: lcd.print("Continuity"); break;
    case 7: lcd.print("LDR"); break;

  }
}

// *Run Selected Test*
void runTest() {
  switch (mode) {
    case 0: measureResistor(); break;
    case 1: measureInductor(); break;
    case 2: measureCapacitor(); break;
    case 3: measureDiode(); break;
    case 4: measureLED();break;
    case 5: measureBJT(); break;
    case 6: continuitytester(); break;
    case 7: measureLDR(); break;
  }
}

// *Resistor Measurement*
// *Resistor Measurement*
void measureResistor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Measuring...");
  delay(500);  // Wait for a short moment to show the message

  int raw = analogRead(resistorPin);
  float Vout = (raw * Vin) / 1024.0;
  float R2 = (Vout > 0) ? R1 * ((Vin / Vout) - 1) : 0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Resistance:");
  lcd.setCursor(0, 1);
  if (R2 > 0) {
    lcd.print(R2);
    lcd.print(" Ohm");
  } else {
    lcd.print("Disconnected");
  }
}

// *Inductor Measurement*
void measureInductor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Measuring...");
  delay(500);  // Wait for a short moment to show the message

  unsigned long startTime, endTime;
  digitalWrite(inductorCharge, HIGH);
  delayMicroseconds(5);
  startTime = micros();
  while (analogRead(inductorPin) < 512);
  endTime = micros();
  digitalWrite(inductorCharge, LOW);
  
  float timeSeconds = (endTime - startTime) / 1000000.0;
  float inductance = (inductorResistance * timeSeconds) / 0.693;  // Inductance in Henrys
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inductance:");
  lcd.setCursor(0, 1);
  if (inductance > 0) {
    lcd.print(inductance * 1000);  // Convert H to mH
    lcd.print(" mH");
  } else {
    lcd.print("Error");
  }
}

// *Capacitor Measurement*
void measureCapacitor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Measuring...");
  delay(500);  // Wait for a short moment to show the message

  unsigned long startTime, elapsedTime;
  float capacitance;

  // Ensure capacitor is discharged before measurement
  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);
  delay(500); // Allow full discharge
  pinMode(dischargePin, INPUT);

  // Start charging the capacitor
  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, HIGH);
  startTime = millis();

  // Wait for capacitor to charge to 63% of VCC (~3.16V)
  while (analogRead(capacitorPin) < 646) {}  

  elapsedTime = millis() - startTime;  // Calculate charging time

  // Stop charging
  digitalWrite(chargePin, LOW);
  pinMode(chargePin, INPUT);

  // Calculate capacitance (C = t / (R * ln(2)))
  capacitance = (float)elapsedTime / (capacitorResistor * 1000.0);

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  if (capacitance > 1e-6) {
    lcd.print("Capacitance:");
    lcd.setCursor(0, 1);
    lcd.print(capacitance * 1e6, 2);
    lcd.print(" uF");
  } else {
    lcd.print("Capacitance:");
    lcd.setCursor(0, 1);
    lcd.print(capacitance * 1e9, 2);
    lcd.print(" nF");
  }

  // Discharge capacitor
  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);
  delay(500);
  pinMode(dischargePin, INPUT);
}

// *Diode Measurement*
void measureDiode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Measuring...");
  delay(500);  // Wait for a short moment to show the message

  int rawValue = analogRead(diodePin);  // Read from the correct pin
  float input_volt = (rawValue * 5.0) / 1023.0;  // Convert ADC value to voltage

  Serial.print("Raw ADC Value = ");
  Serial.println(rawValue);
  Serial.print("Voltage = ");
  Serial.println(input_volt, 2);  // Print voltage with 2 decimal places

  lcd.clear();
  lcd.setCursor(0, 0);

  // *Check if a diode is connected*
  if (input_volt > 0.2) {  // Ensure a diode is present
    lcd.print("Diode: ");
    
    if (input_volt < 0.4) {
      lcd.print("Ge");  // Germanium diode
    } 
    else if (input_volt < 0.8) {
      lcd.print("Si");  // Silicon diode
    } 
    else if (input_volt > 3.3) {
      lcd.print("Zener");  // Possible Zener diode
    } 
    else {
      lcd.print("Unknown");
    }

    lcd.setCursor(0, 1);
    lcd.print("Voltage: ");
    lcd.print(input_volt, 2);
    lcd.print(" V");
    
  } else {
    lcd.print("Diode: None");
    lcd.setCursor(0, 1);
    lcd.print("Not connected");
  }

  delay(2000);  // Short delay before returning to the menu
}

void continuitytester() { 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Measuring...");
  delay(500);  

  int rawValue = analogRead(diodePin);
  float input_volt = (rawValue * 5.0) / 1023.0;
  Serial.println(rawValue);
  Serial.println(input_volt, 2);  

  lcd.clear();
  lcd.setCursor(0, 0);

  // Check circuit continuity
  if (input_volt >= 4.9) {  
    lcd.print("Open Circuit");  // No connection
  } else {  
    lcd.print("Short Circuit");  // Very low voltage means direct connection
  }

  delay(2000);
}



void measureLED() {
  lcd.setCursor(0, 0);
  lcd.print("Measuring...   "); // Keep spacing to overwrite old text
  delay(500);

  int rawValue = analogRead(diodePin);
  float input_volt = (rawValue * 5.0) / 1023.0;

  Serial.print("Voltage = ");
  Serial.println(input_volt, 2);

  lcd.setCursor(0, 0);

  if (input_volt > 0.2) {  
    if (input_volt >= 1.7 && input_volt <= 2.0) {
      lcd.print("LED: Red      ");
    } else if (input_volt > 2.0 && input_volt <= 2.4) {
      lcd.print("LED: Yellow   ");
    } else if (input_volt > 2.4 && input_volt <= 3.5) {
      lcd.print("LED: Blue     ");
    } else {
      lcd.print("Unknown LED   ");
    }

    lcd.setCursor(0, 1);
    lcd.print("V: ");
    lcd.print(input_volt, 2);
    lcd.print("V      "); // Keep spacing to overwrite previous values

  } else {
    lcd.print("LED: None     ");
    lcd.setCursor(0, 1);
    lcd.print("Not connected ");
  }

  delay(2000);
}




// *BJT Measurement*
void measureBJT() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Testing...");
  delay(500);

  float Vb, Vc, Ib, Ic, hFE;

  // Power on test setup for NPN
  digitalWrite(nmosGate, HIGH);
  digitalWrite(pmosGate, HIGH);
  digitalWrite(bjtBase, HIGH);
  delay(100);

  Vb = analogRead(bjtEmitter) * (Vin / 1023.0);
  Vc = analogRead(bjtCollector) * (Vin / 1023.0);

  // Check for no connection (both voltages near zero)
  if (Vb < 0.2 && Vc < 0.2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BJT Status:");
    lcd.setCursor(0, 1);
    lcd.print("Not Connected");
    return;
  }

  Ib = (Vin - Vb) / 10000.0;
  Ic = (Vin - Vc) / 1000.0;
  hFE = Ic / Ib;

  if (hFE > 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BJT Type:");
    lcd.setCursor(0, 1);
    lcd.print("NPN Transistor");
  } else {
    // Switch for PNP Test
    digitalWrite(nmosGate, LOW);
    digitalWrite(pmosGate, LOW);
    digitalWrite(bjtBase, LOW);
    delay(100);

    Vb = analogRead(bjtEmitter) * (Vin / 1023.0);
    Vc = analogRead(bjtCollector) * (Vin / 1023.0);

    // Check again for NC in PNP mode
    if (Vb < 0.2 && Vc < 0.2) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BJT Status:");
      lcd.setCursor(0, 1);
      lcd.print("Not Connected");
      return;
    }

    Ib = (Vb) / 10000.0;
    Ic = (Vc) / 1000.0;
    hFE = Ic / Ib;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BJT Type:");
    lcd.setCursor(0, 1);
    lcd.print("PNP Transistor");
  }
}

void measureLDR() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LDR Resistance:");  // Print static text once

  delay(1000);  // Short delay for better readability

  while (digitalRead(nextButton) != LOW) {
    int raw = analogRead(resistorPin);
    float Vout = (raw * Vin) / 1024.0;
    float R2 = (Vout > 0) ? R1 * ((Vin / Vout) - 1) : 0;

    lcd.setCursor(0, 1); // Move to second row
    lcd.print("                "); // Clear entire row to prevent ghost characters
    lcd.setCursor(0, 1); // Reset cursor position
    
    if (R2 > 0) {
      lcd.print(R2, 1); // Limit to 1 decimal place for readability
      lcd.print(" Ohm");
    } else {
      lcd.print("Disconnected");
    }

    delay(500); // Small delay to stabilize readings
  }
}