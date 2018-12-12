#include "ledmatrix.h"
#include "sprite.h"
#include <util/delay.h>

// Bit
#define HIGH 1
#define LOW 0
#define speed 10

void pointtest (void)
{
  uint8_t x, y;
  y=0;
  x=0;

  while(1)
  {
  // light one LED at a time, scanning left to right
  // and top to bottom... useful for testing the matrix
  //32
    for (x=0; x<32; x++) 
    {
      for (y=0; y<8; y++)
      {
        write(x, y, HIGH);
        _delay_ms(20);
        write(x, y, LOW);
      } 
    }
  }
}

int main(void)
{
  setup();
  uint8_t letter_L[] = {5, 8,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11111,
    0b11111
  };
  
  uint8_t letter_E[] = {5, 8,
    0b11111,
    0b11111,
    0b11000,
    0b11110,
    0b11110,
    0b11000,
    0b11111,
    0b11111
  };

  uint8_t letter_D[] = {6, 8,
    0b111100,
    0b111110,
    0b110111,
    0b110011,
    0b110011,
    0b110111,
    0b111110,
    0b111100
  };

  uint8_t letter_S[] = {5, 8,
    0b01110,
    0b11111,
    0b11000,
    0b11110,
    0b01111,
    0b00011,
    0b11111,
    0b01110
  };
  
  spritewrite(0,letter_L);
  spritewrite(6,letter_E);
  spritewrite(12,letter_D);
  spritewrite(19,letter_S);

  //pointtest();
  //regTest(0xff);
  //write(0,0,HIGH);
  //_delay_ms(1000);
  //write(0,0,LOW);
  //setRegister(0x08,0b11111111);
  return 0;
}