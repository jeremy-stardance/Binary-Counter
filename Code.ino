/**
 * Binary Counter for Arduino
 * Credit to Dave Hall
 */

int ledPin[] = {15, 16, 17, 18, 19, 20};

int numLeds = (sizeof(ledPin) / sizeof(int));

int buttonPin = 7;

byte counter = 0;

int maxValue = (1 << numLeds);

/**
 * Perform the initial setup of our device.
 */
void setup()
{
  // Tell the arduino to listen for input from the button.
  pinMode(buttonPin, INPUT_PULLUP);

  // Tell the arduino to expect output
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPin[i], OUTPUT);
  }

  // Blink each of the LEDs to confirm the circuit is correct.
  fastBlink();
}

/**
 * What to do continuously until stopped.
 */
void loop()
{
  // Check if our button is being pressed
  if (digitalRead(buttonPin) == LOW) {
    // Increment the counter.
    counter++;
    // Wait half a second so we don't double count presses.
    delay(250);
    // Update our display.
    displayBinary(counter);
  }

  // Make sure we don't go past our maximum allowed value.
  if (counter >= maxValue) {
    // Make sure the user sees all the LEDs lit up.
    delay(1000);
    // Clear the LEDs, ready to start again.
    fastBlink();
    // Reset our counter.
    counter = 0;
  }
}

/**
 * Displays the value as a binary number using an array of LEDs.
 *
 * Derived from work by M Atkinson.
 * http://www.multiwingspan.co.uk/arduino.php?page=led5
 */
void displayBinary(byte numToShow)
{
  // Check each of the bits in our number.
  for (int i = 0; i < numLeds; i++)
  {
    // Is the bit "on"?
    if (bitRead(numToShow, i) == 1)
    {
      // Turn the LED on.
      digitalWrite(ledPin[i], HIGH);
    }
    else
    {
      // Turn the LED off.
      digitalWrite(ledPin[i], LOW);
    }
  }
}

/**
 * Quickly blink each of the LEDs in order.
 */
void fastBlink() {
  // Loop through our LEDs in reverse order.
  for (int i = (numLeds - 1); i >= 0; i--) {
    // Turn the LED on.
    digitalWrite(ledPin[i], HIGH);
    // Wait 50ms.
    delay(50);
    // Turn the LED off.
    digitalWrite(ledPin[i], LOW);
  }
}