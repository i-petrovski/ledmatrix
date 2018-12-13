#define HIGH 1
#define LOW 0

void spritex(uint8_t startx, uint8_t starty, uint8_t width, uint8_t bits)
{
  startx = startx + width - 1;
  while (bits) {
      if (bits & 1) {
          write(startx,starty,HIGH);
      } else {
          write(startx,starty,LOW);
      }
      startx--;
      bits >>= 1;
  }
}

void spritewrite(uint8_t posx, uint8_t sprite[])
{
  uint8_t spritey, posy;
  posy = sprite[1] - 1;
  for (spritey=2; spritey<sprite[1] + 2; spritey++)
  {
    spritex(posx,posy,sprite[0],sprite[spritey]);
    posy--;
  }
}

uint8_t letter_C[] = {5, 8,
  0b01110,
  0b11111,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11111,
  0b01110
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

uint8_t letter_O[] = {6, 8,
  0b001100,
  0b011110,
  0b110011,
  0b110011,
  0b110011,
  0b110011,
  0b011110,
  0b001100
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

uint8_t letter_U[] = {6, 8,
  0b110011,
  0b110011,
  0b110011,
  0b110011,
  0b110011,
  0b110011,
  0b011110,
  0b001100
};