#include <TVout.h>
#include <fontALL.h>

TVout TV;
char inputBuffer[10]; // Buffer to store user input

void setup() {
  TV.begin(NTSC, 120, 96);
  TV.select_font(font6x8);
  TV.println("Masukkan angka kamu");

  // Initialize the serial communication
  Serial.begin(9600);
}

// Function to print text with green color
void printGreenText(const char* text) {
  TV.print_str(0, 0, text, 1); // Print text at (0,0) with green color
}

void loop() {
  // Check if there is any data available on the serial port
  if (Serial.available() > 0) {
    // Read the user input into the buffer
    int bytesRead = Serial.readBytesUntil('\n', inputBuffer, sizeof(inputBuffer) - 1);

    // Null-terminate the input string
    inputBuffer[bytesRead] = '\0';

    // Display the user input on the TV screen with green color
    TV.println("Kamu memasukkan: ");
    printGreenText(inputBuffer);
  }
}
