// Quick exercise to brush up on bitfields.
// Relatively space efficient morse code generator.

struct MC {
  unsigned char len : 3;
  unsigned char bits : 5;
};

MC code[64] = {
  { 2, 0b01000 },  // A .-
  { 4, 0b10000 },  // B -...
  { 4, 0b10100 },  // C -.-.
  { 3, 0b10000 },  // D -..
  { 1, 0b00000 },  // E .
  { 4, 0b00100 },  // F ..-.
  { 3, 0b11000 },  // G --.
  { 4, 0b00000 },  // H ....
  { 2, 0b00000 },  // I ..
  { 4, 0b01110 },  // J .---
  { 3, 0b10100 },  // K -.-
  { 4, 0b01000 },  // L .-..
  { 2, 0b11000 },  // M --
  { 2, 0b10000 },  // N -.
  { 3, 0b11100 },  // O ---
  { 4, 0b01100 },  // P .--.
  { 4, 0b11010 },  // Q --.-
  { 3, 0b01000 },  // R .-.
  { 3, 0b00000 },  // S ...
  { 1, 0b10000 },  // T -
  { 3, 0b00100 },  // U ..-
  { 4, 0b00010 },  // V ...-
  { 3, 0b01100 },  // W .--
  { 4, 0b10010 },  // X -..-
  { 4, 0b10110 },  // Y -.--
  { 4, 0b11000 },  // Z --..
  { 5, 0b11111 },  // 0 -----
  { 5, 0b01111 },  // 1 .----
  { 5, 0b00111 },  // 2 ..---
  { 5, 0b00011 },  // 3 ...--
  { 5, 0b00001 },  // 4 ....-
  { 5, 0b00000 },  // 5 .....
  { 5, 0b10000 },  // 6 -....
  { 5, 0b11000 },  // 7 --...
  { 5, 0b11100 },  // 8 ---..
  { 5, 0b11110 }   // 9 ----.
};

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int i = 0;
  int index = 0;
  int mask = 0;
  int last_c = 0;
  char *msg = "nobody does not like dolly madison";
  for (char *ptr = msg; *ptr != '\0'; ptr++) {

    // Set bit 5 of current character so always lower case.

    i = *ptr | 0b00100000;  // Switch to lower case

    // Skip if not a digit or a lower case character

    if ((*ptr >= '0' && *ptr <= '9') || (i >= 'a' && i <= 'z')) {

      // delay between words

      if (last_c && last_c == ' ' && *ptr != ' ') {
        delay(700);
      }
      last_c = i;
      if (i >= 97) {
        index = i - 'a';
      } else {
        index = i - '0' + 26;
      }

      // Check each bit to see if dash (long) or dot (short)

      for (int n = 0; n < code[index].len; n++) {
        mask = 1 << (4 - n);
        digitalWrite(LED_BUILTIN, HIGH);
        if (code[index].bits & mask) {
          delay(300);
        } else {
          delay(100);
        }
        digitalWrite(LED_BUILTIN, LOW);
      }

      // Delay between letters

      delay(300);
    }
  }
}
