#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int _buffer [0];
//uint8_t _buffer [0] = {0};
uint8_t _width;
uint8_t _height;


void init(uint8_t width, uint8_t height)
{
  _width = width >= 8 ? 8 : width;
  _height = height >= 8 ? 8 : height;

  // for now, do nothing if this allocation fails.  methods that require it
  // should silently fail if _buffer is null.
  //_buffer = (uint8_t *) calloc(_height, 1);
}

void swrite(uint8_t x, uint8_t y, uint8_t value)
{
  //if (!_buffer) return;
  
  // uint8_t's can't be negative, so don't test for negative x and y.
  if (x >= _width || y >= _height) return;
  
  // we need to bitwise-or the value of the other pixels in the byte with
  // the new value, masked and shifted into the proper bits.
  _buffer[y] = (_buffer[y] & ~(0x01 << x)) | ((value & 0x01) << x);
}

void Sprite(uint8_t width, uint8_t height, uint8_t row, ...)
{
  init(width, height);
  
  //if (!_buffer) return;
  
  va_list ap;
  va_start(ap, row);

  int y = 0;
  for (y = 0; ; y++) {
    int x;
    for (x = 0; x < width && x < 8; x++)
      swrite(x, y, (row >> (width - x - 1)) & 0x01);
    
    if (y == height - 1)
      break;
      
    row = va_arg(ap, int); // using '...' promotes uint8_t to int
  }
  
  va_end(ap);
}

const uint8_t width()
{
  return _width;
}

const uint8_t height()
{
  return _height;
}

const uint8_t read(uint8_t x, uint8_t y)
{
  if (!_buffer) return 0;
  
  // uint8_t's can't be negative, so don't test for negative x and y.
  if (x >= _width || y >= _height) return 0;
  
  return (_buffer[y] >> x) & 0x01;
}