#include <avr/io.h>
#include <util/delay.h>

// Load Pin high and low 
#define clockLow  PORTB &= ~(1 << 1)
#define clockHigh PORTB |= (1 << 1)
#define dinLow    PORTB &= ~(1 << 0)
#define dinHigh   PORTB |= (1 << 0)
#define loadLow   PORTB &= ~(1 << 2)
#define loadHigh  PORTB |= (1 << 2)

// Screen Count
// #define screenCount 1;
#define screenCount 4
#define _maximumX 32

// Matrix registers
#define REG_NOOP   0x00
#define REG_DIGIT0 0x01
#define REG_DIGIT1 0x02
#define REG_DIGIT2 0x03
#define REG_DIGIT3 0x04
#define REG_DIGIT4 0x05
#define REG_DIGIT5 0x06
#define REG_DIGIT6 0x07
#define REG_DIGIT7 0x08
#define REG_DECODEMODE  0x09
#define REG_INTENSITY   0x0A
#define REG_SCANLIMIT   0x0B
#define REG_SHUTDOWN    0x0C
#define REG_DISPLAYTEST 0x0F

//uint8_t _buffer [7] = {0};
uint8_t _buffer [0];

void setByte(uint8_t data)
{
  uint8_t i = 8;
  uint8_t mask;
  while(i > 0) {
    mask = 0x01 << (i - 1);         // get bitmask
    clockLow;                       // tick
    //_delay_ms(10);
    if (data & mask){               // choose bit
      dinHigh;                      // set to 1
    }
    else{
      dinLow;                       // set to 0
    }
    clockHigh;                      // tock
    //_delay_ms(10);
    --i;                            // move to lesser bit
  }
}

void setRegister(uint8_t reg, uint8_t data)
{
  uint8_t i;
  loadLow;             // begin
  for(i = 0; i < screenCount; ++i)
  {
    setByte(reg);     // Send the register data to the ic.
    setByte(data);    // Send the data to the ic
  }
  // latch in data
  loadHigh;
  loadLow;
}

void buffer(uint8_t x, uint8_t y, uint8_t value)
{
  //if (!_buffer) return;
  
  // uint8_t's can't be negative, so don't test for negative x and y.
  if (x >= _maximumX || y >= 8) return;

  uint8_t offset = x; // record x
  x %= 8;             // make x relative to a single matrix
  offset -= x;        // calculate buffer offset

  // wrap shift relative x for nexus module layout
  if (x == 0)
  {
    x = 8;
  }
  --x;
  //y = y + 1;
  // record value in buffer
  if(value)
  {
    _buffer[y + offset] |= 0x01 << x;
  }
  else
  {
    _buffer[y + offset] &= ~(0x01 << x);
  }
}

// syncs row of display with buffer
void syncRow(uint8_t row)
{
  uint8_t i;
  //if (!_buffer) return;
  
  //row = row + 1;
  
  // uint8_t's can't be negative, so don't test for negative row
  if (row >= 8) return;
  loadLow;
  for(i = 0; i < screenCount; ++i)
  {
    setByte(8 - row);                // specify register
    //setByte(row);
    setByte(_buffer[row + (8 * i)]); // send data
  }
  // latch in data
  loadHigh;
  // end
  loadLow;
}

void setBrightness(uint8_t value)
{
  setRegister(REG_INTENSITY, value & 0x0F);
}

// sets how many digits are displayed
void setScanLimit(uint8_t value)
{
  setRegister(REG_SCANLIMIT, value & 0x07);
}

void clearScreen(void)
{
  //if (!_buffer) return;

  // clear buffer
  uint8_t i;
  for(i = 0; i < 8; ++i)
  {
    uint8_t j;
    for(j = 0; j < screenCount; ++j)
    {
      _buffer[i + (8 * j)] = 0x00;
    }
  }

  // clear registers
  for(i = 0; i < 8; ++i)
  {
    syncRow(i);
  }
}

void write(uint8_t x, uint8_t y, uint8_t value)
{
  buffer(x, y, value);
  // update affected row
  syncRow(y);
}

void setup(void)
{
  // B1=Clock B2=DIN B3=Load Date
  // Enable ports B1,B2,B3
  DDRB |= (1 << 0) | (1 << 1) | (1 << 2);

  // Start Pins low
  clockLow;
  dinLow;
  loadLow;

  // initialize registers
  clearScreen();                      // clear display
  setScanLimit(0x07);                 // use all rows/digits 1:0x00 - 8:0x07
  setBrightness(0x0A);                // maximum brightness 0x00 - 0x0F (290ma for 104led max power)
  setRegister(REG_SHUTDOWN, 0x01);    // normal operation Disabled:0x00 
  setRegister(REG_DECODEMODE, 0x00);  // no decode 0x00 0x00-0xFF
  setRegister(REG_DISPLAYTEST, 0x00); // not in test mode
}