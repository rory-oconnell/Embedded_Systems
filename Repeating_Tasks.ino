#include <Keyboard.h>

// Define key constants
char ctrlKey = KEY_LEFT_CTRL;
char altKey = KEY_LEFT_ALT;
char tabKey = KEY_TAB;
char enterKey = KEY_RETURN;
char backspaceKey = KEY_BACKSPACE;

void setup() {
  // Open the serial port at 9600 bps for debugging or future expansion
  Serial.begin(9600);

  // Initialize keyboard emulation
  Keyboard.begin();
}

void loop() {
  // Array of predefined strings to type
  char *myStrings[] = { 
    "Bonjour, /Cela sera traite. /Merci,",
    "Bonjour, /Cela a ete mis a jour. /Merci,",
    "Hi team, /Please process the below. /Thanks!",
    "Hi, /Please see the below and let me know if you have any questions!",
    "Hi team, /Please see the request below for processing. /Thank you!",
    "Hi team, /Please see the attached for processing. /Thanks!",
  };

  performDeleteAll();
  delay(random(2000, 5000)); // Random delay between actions

  int index = random(0, 6); // Randomly choose a string to type
  String str = myStrings[index];

  // Type the string character by character
  for (int j = 0; j < str.length(); j++) {
    if (str[j] == '/') {
      // Simulate pressing Enter
      simulateKeyPress(enterKey, 50);
      continue;
    } else {
      // Type the character and add a random delay
      Keyboard.write(str[j]);
      delay(random(30, 300));
    }
  }

  delay(random(3000, 8000)); // Random delay after typing
  performAltTab();           // Switch application
  delay(15000);              // Wait before the next loop iteration
}

void performAltTab() {
  // Function to perform Alt+Tab
  Keyboard.press(altKey);
  Keyboard.press(tabKey);
  delay(100); // Ensure the key press is registered
  Keyboard.releaseAll();
}

void performDeleteAll() {
  // Function to select all and delete text
  Keyboard.press(ctrlKey);
  delay(100);
  Keyboard.write('a'); // Select all
  delay(100);
  Keyboard.releaseAll();
  delay(150);
  Keyboard.write(backspaceKey); // Delete
  delay(100);
  Keyboard.releaseAll();
  delay(1000);
}

void simulateKeyPress(char key, int delayTime) {
  // Helper function to simulate key press
  Keyboard.press(key);
  delay(delayTime);
  Keyboard.release(key);
}
