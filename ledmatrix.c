#include "ledmatrix.h"
//#include "sprite.h"
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
    for (x=0; x<13; x++) 
    {
      for (y=0; y<8; y++)
      {
        write(x, y, HIGH);
        //_delay_ms(20);
        //write(x, y, LOW);
      } 
    }
  }
}

void setBox(uint8_t SETBIT)
{
  uint8_t x=0, y=0;
    for (y=0; y<7; ++y)
    {
      write(x,y,SETBIT);
      _delay_ms(speed);
    }

    for (x=0; x<7; ++x)
    {
      write(x,y,SETBIT);
      _delay_ms(speed);
    }

    for (y=7; y>0; --y)
    {
      write(x,y,SETBIT);
      _delay_ms(speed);
    }

    for (x=7; x>0; --x)
    {
      write(x,y,SETBIT);
      _delay_ms(speed);
    }
}

void regTest(uint8_t REGBYTE)
{
  setRegister(0x01,REGBYTE);
  _delay_ms(speed);
  setRegister(0x02,REGBYTE);
  _delay_ms(speed);
  setRegister(0x03,REGBYTE);
  _delay_ms(speed);
  setRegister(0x04,REGBYTE);
  _delay_ms(speed);
  setRegister(0x05,REGBYTE);
  _delay_ms(speed);
  setRegister(0x06,REGBYTE);
  _delay_ms(speed);
  setRegister(0x07,REGBYTE);
  _delay_ms(speed);
  setRegister(0x08,REGBYTE);
  _delay_ms(speed);
}

void loadXY(void)
{
  uint8_t y=0, x=0;

  while (y<8)
  {
    write(0, y, HIGH);
    _delay_ms(speed);
    y++;
  }
  while (x<8)
  {
    write(x, 0, HIGH);
    _delay_ms(speed);
    x++;
  }
}

int main(void)
{
  setup();

  //swrite(0, 0, letter_L)

  //loadXY();
  pointtest();
  //regTest(0xff);

  //setBox(HIGH);
  //setBox(LOW);
  //_delay_ms(500);
  //write(0,0,HIGH);

  //setRegister(0x08,0b11111111);
  //uint8_t x=0, y=0;
  //write(0,0,HIGH);
  //_delay_ms(1000);
  //write(0,0,LOW);
  //while(1){
  //  setBox(HIGH);
  //  setBox(LOW);
  //}
  return 0;
}