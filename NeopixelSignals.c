extern void send_one();
extern void send_zero();
extern void send_ret();

// Sends the color green to the neopixel
void green() {
  send_one();
  send_one();
  send_one();
  send_one();
  send_one();
  send_one();
  send_one();
  send_one();

  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();

  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_ret();
}

// Sends the color blue to the neopixel
void blue() {

  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();

  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();

  send_one();
  send_one();
  send_one();
  send_one();
  send_one();
  send_one();
  send_one();
  send_one();

  send_ret();
}

// Sends the color red to the neopixel
void red() {
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();

  send_one();
  send_one();
  send_one();
  send_one();
  send_one();
  send_one();
  send_one();
  send_one();

  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
}
// Doesn't send anything to the neopixel for 236 clock cycles
void zero() {
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();

  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();

  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();
  send_zero();

  send_ret();
}
 // Sends the ret signal
void ret() {

  send_ret();
  send_ret();
  send_ret();
  send_ret();
  send_ret();
  send_ret();
  send_ret();
  send_ret();

  send_ret();
  send_ret();
  send_ret();
  send_ret();
  send_ret();
  send_ret();
  send_ret();
  send_ret();

  send_ret();
  send_ret();
  send_ret();
  send_ret();
  send_ret();
  send_ret();
  send_ret();
  send_ret();
}