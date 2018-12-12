#define HIGH 1
#define LOW 0

void spritex(uint8_t startx, uint8_t starty, uint8_t width, uint8_t bits){
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

void spritewrite(uint8_t posx, uint8_t sprite[]){
  uint8_t spritey, posy;
  posy = sprite[1] - 1;
  for (spritey=2; spritey<sprite[1] + 2; spritey++){
    spritex(posx,posy,sprite[0],sprite[spritey]);
    posy--;
  }
}