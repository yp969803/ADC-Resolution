void setup() {
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

  calculate();
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
  digitalWrite(13, LOW);


  // Trigger SOC
  digitalWrite(12, HIGH);
  delayMicroseconds(10);
  digitalWrite(12, LOW);


  // Wait until EOC goes HIGH
  Serial.println("i");
  while (digitalRead(11) == LOW) {
  }


  // Get initial reading
  uint8_t adc_data_initial = readADC();
  Serial.println((double)adc_data_initial, 4);

  // Close DAC circuit
  digitalWrite(13, HIGH);
  while (digitalRead(13) == LOW) {
  }

  // Trigger SOC
  digitalWrite(12, HIGH);
  delayMicroseconds(10);
  digitalWrite(12, LOW);

  Serial.println("i");
  while (digitalRead(11) == LOW) {
  }

  // Get DAC-converted reading
  uint8_t adc_data_after = readADC();
  Serial.println((double)adc_data_after, 4);


  // Final calculation (explicit casting to double)
  double ans = (((double)adc_data_initial * 248.0) + (double)adc_data_after) * 5.0 / (248.0 * 256.0);

  Serial.println("F");
  Serial.println(ans, 4);
}

void loop() {
}
