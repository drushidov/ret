# Robotics Entry Task
Implementation of the Ocado Robotics Accelerator 2022 entry task.

# Setup instructions

## Windows
### Prerequisites
- Visual Studio installed (preferably 2019)

### Steps
1. Open a Developer Command Prompt
2. Ensure current working directory is the `cpp` folder
3. Run `cmake -G "NMake Makefiles" -S . -B build`
4. Run `cd build`
5. Run `nmake`
6. Run `cd bin`
7. Copy the `input.bin` and `output.bin` files to the current directory
8. Run the executable file `red_eye_filtering.exe`

Tested with Visual Studio 2019 installed


## Linux
### Prerequisites
- g++ version 8+
- cmake version 3.13+

### Steps
1. Ensure current working directory is the `cpp` folder
2. Run `cmake -S . -B build`
3. Run `cd build`
4. Run `make`
5. Run `cd bin`
6. Copy the `input.bin` and `output.bin` files to the current directory
7. Run the executable file `red_eye_filtering`

Tested on Debian 10 with g++ 8.3.0 and cmake 3.13.4