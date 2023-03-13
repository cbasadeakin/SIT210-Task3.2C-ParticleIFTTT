// This allows the code to run before the cloud is connected.
SYSTEM_THREAD(ENABLED);

// This uses the USB serial port for debugging logs.
SerialLogHandler logHandler;

// This is where the photoresistor or phototransistor is plugged in.
const pin_t SENSOR_PIN = A0;

// Here we are declaring the integer variable light, which we will
// use later to store the value of the photoresistor or phototransistor.
int light;

void setup()
{
    // We are going to declare a Particle.variable() here so that we can
    // access the value of the photosensor from the cloud.
    Particle.variable("light", light);
    
    pinMode(A0, INPUT);
}

void loop()
{
    // Check to see what the value of the photoresistor or phototransistor is
    // and store it in the int variable light
    light = analogRead(SENSOR_PIN);

    Particle.publish("light", String(light), PRIVATE);
    
    // This sends a publish when the light intensity is greater than zero.
    if (analogRead(SENSOR_PIN) > 0) {
      Particle.publish("sunlight_detected", PRIVATE);
    }
    else {
      Particle.publish("sunlight_not_detected", PRIVATE);
    }
    
    // This delay is just to prevent overflowing the serial buffer, plus we
    // really don't need to read the sensor more than
    // 10 times per second (5 minute delay)
    delay(300s); 
}