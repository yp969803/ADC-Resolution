void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // Data pins
 for (int i = 2; i <= 8; i++) {
    pinMode(i, INPUT);
  }
  // ADC D0 → Arduino D9
  pinMode(9, INPUT);


  // EOC pin
  pinMode(11, INPUT);

  // SOC pin
  pinMode(12, OUTPUT);

  // DAC Switch control
  pinMode(13, OUTPUT);


}

uint8_t readADC() {
  uint8_t value = 0;

  // LSB (bit 0) comes from D9
  value |= (digitalRead(9) << 0);

  // Bits 1–7 come from D2–D8
  for (int i = 1; i <= 7; i++) {
    value |= (digitalRead(i + 1) << i);  // D1→2, D2→3, … D7→8
  }

  return value;
}


void calculate() {

   Serial.println("Start of the calculation");
   // Open dac circuit

   digitalWrite(13, LOW);

   Serial.print("Pin 13 status:");
   Serial.println(digitalRead(13));

  // Trigger SOC
  digitalWrite(12, HIGH); // send SOC high

  Serial.print("Pin 12 status:");
  Serial.println(digitalRead(12));

  Serial.print("Pin 11 status:");
  Serial.println(digitalRead(11));

  delayMicroseconds(10); // small delay
  digitalWrite(12, LOW); // bring soc low

  Serial.print("Pin 12 status:");
  Serial.println(digitalRead(12));
  // wait until EOC (pin 11) goes HIGH
  while(digitalRead(11)==LOW){
     Serial.println("Inside while loop for checking eoc");
  }

  Serial.print("Pin 11 status:");
  Serial.println(digitalRead(11));
  // Get inital voltage
  uint8_t adc_data_initial = readADC();

    // Print the value in binary (to see pin states clearly)
  Serial.print("Inital voltage Binary: ");
  Serial.println(adc_data_initial, BIN);


  Serial.print("Pin 13 status:");
  Serial.println(digitalRead(13));

  // Close dac circuit
  digitalWrite(13, HIGH);

  Serial.println("After close of the circuit");

  Serial.print("Pin 13 status:");
  Serial.println(digitalRead(13));

   Serial.print("Pin 12 status:");
  Serial.println(digitalRead(12));
  // Trigger SOC
  digitalWrite(12, HIGH); // send SOC high

  Serial.print("Pin 12 status:");
  Serial.println(digitalRead(12));
  
  delayMicroseconds(10); // small delay
  digitalWrite(12, LOW); // bring soc low

  Serial.print("Pin 12 status:");
  Serial.println(digitalRead(12));

  Serial.print("Pin 11 status:");
  Serial.println(digitalRead(11));

  // wait until EOC (pin 11) goes HIGH
  while(digitalRead(11)==LOW){
     Serial.println("inside while loop after close of circuit");
  }

  // Get voltage after converting from dac
  uint8_t adc_data_after = readADC();

  // Print the value in binary (to see pin states clearly)
  Serial.print("Voltage after dac and comparator Binary: ");
  Serial.println(adc_data_after, BIN);

    // Open dac circuit
  digitalWrite(13, LOW);

  Serial.print("Pin 13 status:");
  Serial.println(digitalRead(13));

  delay(5000);

}

void loop() {
    calculate();
}
