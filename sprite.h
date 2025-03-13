#define HIGH 1
#define LOW 0

void spritex(uint8_t startx, uint8_t starty, uint8_t width, uint8_t bits)
{
  startx = startx + width - 1;
  while (bits) {
      uint8_t new_state = (bits & 1) ? HIGH : LOW;
      if (read(startx, starty) != new_state) 
      { // Only write if different
          write(startx, starty, new_state);
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
    spritex(posx, posy, sprite[0], sprite[spritey]);
    posy--;
  }
}



// new
#define HIGH 1
#define LOW 0

uint8_t prev_posx = 0;
uint8_t prev_posy = 0;

// Function to clear previous sprite pixels
void spriteclear(uint8_t posx, uint8_t posy, uint8_t sprite[])
{
  uint8_t spritey, posy_old;
  posy_old = posy;

  for (spritey = 2; spritey < sprite[1] + 2; spritey++)
  {
    spritex(posx, posy_old, sprite[0], 0b00000); // Clear pixels
    posy_old--;
  }
}

// Function to move the sprite efficiently
void spritemove(uint8_t new_posx, uint8_t new_posy, uint8_t sprite[])
{
  // Only clear if the position actually changed
  if (new_posx != prev_posx || new_posy != prev_posy)
  {
    spriteclear(prev_posx, prev_posy, sprite);
  }

  // Draw the sprite at the new position
  spritewrite(new_posx, sprite);

  // Update the previous position
  prev_posx = new_posx;
  prev_posy = new_posy;
}


/*
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
*/

uint8_t letter_TST[] = {7, 8,
  0b0000000,
  0b0000000,
  0b0000000,
  0b0011000,
  0b0000000,
  0b0000000,
  0b0000000,
  0b0000000
};

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