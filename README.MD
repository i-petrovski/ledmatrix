# Compile Program in Windows

- Download "AVR 8-Bit Toolchain (Windows)"
(https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers)

- Copy AVR toolchain to program files C:\Program Files\avr8\bin

- Set windows path to "C:\Program Files\avr8\bin" 

- Make sure avr-gcc is in the bin folder

- Comile code:
```
make program
```

# Compile in MACOS

- Install Homebrew
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

- Add the AVR tap
```
brew tap osx-cross/avr
```

- Install the toolchain
```
brew install avr-gcc
```