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
  
  /*
  spritewrite(0,letter_C);
  spritewrite(6,letter_L);
  spritewrite(12,letter_O);
  spritewrite(19,letter_U);
  spritewrite(26,letter_D);
  */
  
  uint8_t movex;
  movex = 0;
  while(200)
  {  
    spritewrite(0 + movex,letter_C);
    spritewrite(6 + movex,letter_L);
    spritewrite(12 + movex,letter_O);
    spritewrite(19 + movex,letter_U);
    spritewrite(26 + movex,letter_D);
    _delay_ms(100);
    clearScreen();
    movex++;
    if (movex > 32) {
      movex = 0;
    }
  }
  

  //pointtest();
  //regTest(0xff);
  //write(0,0,HIGH);
  //_delay_ms(1000);
  //write(0,0,LOW);
  //setRegister(0x08,0b11111111);
  return 0;
}