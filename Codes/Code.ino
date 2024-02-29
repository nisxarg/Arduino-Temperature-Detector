#define DHT11PIN 4

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println();

  // Variables to store humidity and temperature data
  int humidity = 0;
  int temperature = 0;

  // Read data from DHT11 sensor
  int data[5];
  for (int i = 0; i < 5; ++i) {
    data[i] = 0;
  }

  // Start signal
  pinMode(DHT11PIN, OUTPUT);
  digitalWrite(DHT11PIN, LOW);
  delay(18);

  // DHT11 response
  digitalWrite(DHT11PIN, HIGH);
  delayMicroseconds(30);
  pinMode(DHT11PIN, INPUT);

  // Acknowledge signal
  if (digitalRead(DHT11PIN) == LOW) {
    // Wait for DHT11 to pull bus low for 80us
    while (digitalRead(DHT11PIN) == LOW);
    
    // Wait for DHT11 to pull bus high for 80us
    while (digitalRead(DHT11PIN) == HIGH);

    // Read data (40 bits)
    for (int i = 0; i < 40; ++i) {
      // Wait for sensor to pull the line low for 50us
      while (digitalRead(DHT11PIN) == LOW);

      // Measure duration of the high pulse
      unsigned long startTime = micros();
      while (digitalRead(DHT11PIN) == HIGH);
      unsigned long duration = micros() - startTime;

      // Store data bit
      data[i / 8] <<= 1;
      if (duration > 40) {
        data[i / 8] |= 1;
      }
    }

    // Checksum validation
    if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
      humidity = data[0];
      temperature = data[2];
    }
  }

  // Display readings
  Serial.print("Humidity (%): ");
  Serial.println(humidity);
  Serial.print("Temperature (C): ");
  Serial.println(temperature);

  delay(2000);
}
