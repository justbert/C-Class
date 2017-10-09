/*******************************************************************************

   PURPOSE: Model a primitive system of life.
   
   HISTORY: Created Justin Bertrand, February 20th, 2015

   INPUTS: Enter x to exit the simulation, any other character to proceed.

   OUTPUTS: A grid displaying the model. An X is a live cell, a space is a dead
            cell.

   ALGORITHM(S): 
      Call to initializeOldGrid()
		Do the following loop until stopped:
		    
		Continue Loop
*******************************************************************************/


/*******************************************************************************
   Begin #include statements
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>


/*******************************************************************************
   Begin #define statements
*******************************************************************************/

#define LBITMASK 0x8000000000000000
#define RBITMASK 0x0000000000000001
#define ALIVE 1
#define ZOMBIE 0
#define TOP 0
#define BOT 1
#define LFT 2
#define RGT 3
#define TLF 4
#define TRT 5
#define BLF 6
#define BRT 7
#define ARSZ 32


/*******************************************************************************
   Begin declarations
*******************************************************************************/

typedef unsigned long long int uLLInt;
uLLInt oldGrid[ARSZ] = {0};
uLLInt newGrid[ARSZ] = {0};

void initializeOldGrid();
uLLInt T(int, short);
uLLInt B(int, short);
uLLInt R(int, short);
uLLInt L(int, short);
uLLInt TL(int, short);
uLLInt TR(int, short);
uLLInt BL(int, short);
uLLInt BR(int, short);
uLLInt sumNeighbours(int, short);
void displayBinary(uLLInt);


/*******************************************************************************
   Begin main()
*******************************************************************************/

int main(void) {

   char ch;
   initializeOldGrid();

   do {
      system("clear"); //clear the terminal window

      for(unsigned int index = 0; index < ARSZ; index++) {
         newGrid[index] = sumNeighbours(index, ALIVE) | sumNeighbours(index, ZOMBIE);
         displayBinary(newGrid[index]);
      }

      for(int index = 0; index < ARSZ; ++index) {
         oldGrid[index] = newGrid[index];
      }

      ch = getchar(); //get user input to continue or end program
      
   } while(ch != 'x' && ch != 'X');
}


/*******************************************************************************

   PURPOSE: Initialize an array of with random 64bit numbers.
   
   HISTORY: Created D. Houtman, February 20th, 2015

   INPUTS: None. Acts upon global array, oldGrid[].

   OUTPUTS: None.

   ALGORITHM(S): 
      Do the following for every index in the array
         init64 <- 0
		   init64 <- Get random number
         Bitshit init64 twice to the left
         init64 <- init64 bitwiseOR (0x00000003 bitwiseAND random number)
         bitshift init64 31 time to the left
         init64 <- init64 bitwiseOR and a random number
         oldGrid[index] <- init64;
		End Loop
*******************************************************************************/

void initializeOldGrid(void) {

   uLLInt init64;
   srand(time(NULL));

   for(short index = 0; index < ARSZ; ++index) {
      init64 = 0;
      init64 = rand();
      init64 <<= 2;
      init64 |= (0x00000003 & rand());
      init64 <<= 31;
      init64 |= rand();
      oldGrid[index] = init64;
   }
}


/*******************************************************************************

   PURPOSE: Get a binary number representing live neighbours to the top
            row of a cell.
   
  HISTORY: Coded by Justin Bertrand, based on documentation by D. Houtman 
            February 20th, 2015

   INPUTS:  Row, the row number in the grid to be affected
            Type, the type of cell to be acted upon, ALIVE or ZOMBIE

   OUTPUTS: A 64bit number representing the live neighbours to the top

   ALGORITHM(S): 
               topRow <- (row + ARSZ - 1) % ARSZ
               IF type > 0
                  return oldGrid[topRow] bitwiseAND oldGrid[row]
               ELSE
                  return oldGrid[topRow] bitwiseAND ONESCOMPLEMENT(oldGrid[row])
               ENDIF
*******************************************************************************/

uLLInt T(int row, short type) {
   
   int topRow = (row + ARSZ - 1) % ARSZ;

   if(type) {
      return oldGrid[topRow] & oldGrid[row];

   } else {
      return oldGrid[topRow] & ~oldGrid[row];
   }
}


/*******************************************************************************

   PURPOSE: Get a binary number representing live neighbours to the bottom
            of a row of cells.
   
   HISTORY: Coded by Justin Bertrand, based on documentation by D. Houtman 
            February 20th, 2015

   INPUTS:  Row, the row number in the grid to be affected
            Type, the type of cell to be acted upon, ALIVE or ZOMBIE

   OUTPUTS: A 64bit number representing the live neighbours to the bottom

   ALGORITHM(S): 
               topRow <- (row + 1) % ARSZ
               IF type > 0
                  return oldGrid[botRow] bitwiseAND oldGrid[row]
               ELSE
                  return oldGrid[botRow] bitwiseAND ONESCOMPLEMENT(oldGrid[row])
               ENDIF
*******************************************************************************/

uLLInt B(int row, short type) {

   int botRow = (row + 1) % ARSZ;

   if(type) {
      return oldGrid[botRow] & oldGrid[row];

   } else {
      return oldGrid[botRow] & ~oldGrid[row];
   }
}


/*******************************************************************************

   PURPOSE: Get a binary number representing live neighbours to the left
            of a row of cells.
   
   HISTORY: Coded by Justin Bertrand, based on documentation by D. Houtman 
            February 20th, 2015

   INPUTS:  Row, the row number in the grid to be affected
            Type, the type of cell to be acted upon, ALIVE or ZOMBIE

   OUTPUTS: A 64bit number representing the live neighbours to the left

   ALGORITHM(S): 
      IF type > 0
         IF rightmost bit is 1
            return (oldGrid[row] shift bits 1 to right) bitOR 0x8000000000000000
                     bitwiseAND oldGrid[row]
         ELSE
            return (oldGrid[row] shift bits 1 to right) bitwiseAND oldGrid[row]
         ENDIF
      ELSE
         IF rightmost bit is 1
            return (oldGrid[row] shift bits 1 to right) bitOR 0x8000000000000000
                     bitwiseAND (ONESCOMPLEMENT(oldGrid[row]))
         ELSE
            return (oldGrid[row] shift bits 1 to right) bitwiseAND 
                     ONESCOMPLEMENT(oldGrid[row])
         ENDIF
      ENDIF
*******************************************************************************/

uLLInt L(int row, short type) {

   if(type) {
      if(oldGrid[row] & RBITMASK) {
         return (oldGrid[row] >> 1 | LBITMASK) & oldGrid[row];

      } else {
         return oldGrid[row] >> 1 & oldGrid[row];
      }

   } else {
      if(oldGrid[row] & RBITMASK) {
         return (oldGrid[row] >> 1 | LBITMASK) & ~oldGrid[row];

      } else {
         return oldGrid[row] >> 1 & ~oldGrid[row];
      }
   }
}


/*******************************************************************************

   PURPOSE: Get a binary number representing live neighbours to the right
            of a row of cells.
   
   HISTORY: Coded by Justin Bertrand, based on documentation by D. Houtman 
            February 20th, 2015

   INPUTS:  Row, the row number in the grid to be affected
            Type, the type of cell to be acted upon, ALIVE or ZOMBIE

   OUTPUTS: A 64bit number representing the live neighbours to the right

   ALGORITHM(S): 
      IF type > 0
         IF leftmost bit is 1
            return (oldGrid[row] shift bits 1 to left) bitOR 0x0000000000000001
                     bitwiseAND oldGrid[row]
         ELSE
            return (oldGrid[row] shift bits 1 to left) bitwiseAND oldGrid[row]
         ENDIF
      ELSE
         IF rightmost bit is 1
            return (oldGrid[row] shift bits 1 to left) bitOR 0x0000000000000001
                     bitwiseAND (ONESCOMPLEMENT(oldGrid[row]))
         ELSE
            return (oldGrid[row] shift bits 1 to left) bitwiseAND 
                     ONESCOMPLEMENT(oldGrid[row])
         ENDIF
      ENDIF
*******************************************************************************/

uLLInt R(int row, short type) {

   if(type) {
      if(oldGrid[row] & LBITMASK) {
         return (oldGrid[row] << 1 | RBITMASK) & oldGrid[row];

      } else {
         return oldGrid[row] << 1 & oldGrid[row];
      }

   } else {
      if(oldGrid[row] & LBITMASK) {
         return (oldGrid[row] << 1 | RBITMASK) & ~oldGrid[row];

      } else {
         return oldGrid[row] << 1 & ~oldGrid[row];
      }
   }
}


/*******************************************************************************

   PURPOSE: Get a binary number representing live neighbours to the top left
            of a row of cells.
   
   HISTORY: Coded by Justin Bertrand, based on documentation by D. Houtman 
            February 20th, 2015

   INPUTS:  Row, the row number in the grid to be affected
            Type, the type of cell to be acted upon, ALIVE or ZOMBIE

   OUTPUTS: A 64bit number representing the live neighbours to the top left

   ALGORITHM(S): 
      topRow <- (row + ARSZ - 1) % ARSZ
      IF type > 0
         IF rightmost bit is 1
            return (oldGrid[topRow] shift bits 1 to right) bitOR 0x8000000000000000
                     bitwiseAND oldGrid[topRow]
         ELSE
            return (oldGrid[topRow] shift bits 1 to right) bitwiseAND oldGrid[row]
         ENDIF
      ELSE
         IF rightmost bit is 1
            return (oldGrid[topRow] shift bits 1 to right) bitOR 0x8000000000000000
                     bitwiseAND (ONESCOMPLEMENT(oldGrid[row]))
         ELSE
            return (oldGrid[topRow] shift bits 1 to right) bitwiseAND 
                     ONESCOMPLEMENT(oldGrid[row])
         ENDIF
      ENDIF
*******************************************************************************/

uLLInt TL(int row, short type) {

   int topRow = (row + ARSZ - 1) % ARSZ;

   if(type) {
      if(oldGrid[topRow] & RBITMASK) {
         return (oldGrid[topRow] >> 1 | LBITMASK) & oldGrid[row];

      } else {
         return oldGrid[topRow] >> 1 & oldGrid[row];
      }

   } else {
      if(oldGrid[topRow] & RBITMASK) {
         return (oldGrid[topRow] >> 1 | LBITMASK) & ~oldGrid[row];

      } else {
         return oldGrid[topRow] >> 1 & ~oldGrid[row];
      }
   }
}


/*******************************************************************************

   PURPOSE: Get a binary number representing live neighbours to the top right
            of a row of cells.
   
   HISTORY: Coded by Justin Bertrand, based on documentation by D. Houtman 
            February 20th, 2015

   INPUTS:  Row, the row number in the grid to be affected
            Type, the type of cell to be acted upon, ALIVE or ZOMBIE

   OUTPUTS: A 64bit number representing the live neighbours to the top right

   ALGORITHM(S): 
      topRow <- (row + ARSZ - 1) % ARSZ
      IF type > 0
         IF leftmost bit is 1
            return (oldGrid[topRow] shift bits 1 to left) bitOR 0x0000000000000001
                     bitwiseAND oldGrid[row]
         ELSE
            return (oldGrid[topRow] shift bits 1 to left) bitwiseAND oldGrid[row]
         ENDIF
      ELSE
         IF rightmost bit is 1
            return (oldGrid[topRow] shift bits 1 to left) bitOR 0x0000000000000001
                     bitwiseAND (ONESCOMPLEMENT(oldGrid[row]))
         ELSE
            
            return (oldGrid[topRow] shift bits 1 to left) bitwiseAND 
                     ONESCOMPLEMENT(oldGrid[row])
         ENDIF
      ENDIF
*******************************************************************************/

uLLInt TR(int row, short type) {

   int topRow = (row + ARSZ - 1) % ARSZ;

   if(type) {
      if(oldGrid[topRow] & LBITMASK) {
         return (oldGrid[topRow] << 1 | RBITMASK) & oldGrid[row];

      } else {
         return oldGrid[topRow] << 1 & oldGrid[row];
      }

   } else {
      if(oldGrid[topRow] & LBITMASK) {
         return (oldGrid[topRow] << 1 | RBITMASK) & ~oldGrid[row];

      } else {
         return oldGrid[topRow] << 1 & ~oldGrid[row];
      }
   }
}


/*******************************************************************************

   PURPOSE: Get a binary number representing live neighbours to the bottom right
            of a row of cells.
   
   HISTORY: Coded by Justin Bertrand, based on documentation by D. Houtman 
            February 20th, 2015

   INPUTS:  Row, the row number in the grid to be affected
            Type, the type of cell to be acted upon, ALIVE or ZOMBIE

   OUTPUTS: A 64bit number representing the live neighbours to the bottom right

   ALGORITHM(S): 
      botRow <- (row + 1) % ARSZ
      IF type > 0
         IF leftmost bit is 1
            return (oldGrid[botRow] shift bits 1 to left) bitOR 0x0000000000000001
                     bitwiseAND oldGrid[row]
         ELSE
            return (oldGrid[botRow] shift bits 1 to left) bitwiseAND oldGrid[row]
         ENDIF
      ELSE
         IF rightmost bit is 1
            return (oldGrid[botRow] shift bits 1 to left) bitOR 0x0000000000000001
                     bitwiseAND (ONESCOMPLEMENT(oldGrid[row]))
         ELSE
            return (oldGrid[botRow] shift bits 1 to left) bitwiseAND 
                     ONESCOMPLEMENT(oldGrid[row])
         ENDIF
      ENDIF
*******************************************************************************/

uLLInt BR(int row, short type) {

   int botRow = (row + 1) % ARSZ;

   if(type) {
      if(oldGrid[botRow] & LBITMASK) {
         return (oldGrid[botRow] << 1 | RBITMASK) & oldGrid[row];

      } else {
         return oldGrid[botRow] << 1 & oldGrid[row];
      }
   } else {
      if(oldGrid[botRow] & LBITMASK) {
         return (oldGrid[botRow] << 1 | RBITMASK) & ~oldGrid[row];

      } else {
         return oldGrid[botRow] << 1 & ~oldGrid[row];
      }
   }
}


/*******************************************************************************

   PURPOSE: Get a binary number representing live neighbours to the bottom left
            of a row of cells.
   
   HISTORY: Coded by Justin Bertrand, based on documentation by D. Houtman 
            February 20th, 2015

   INPUTS:  Row, the row number in the grid to be affected
            Type, the type of cell to be acted upon, ALIVE or ZOMBIE

   OUTPUTS: A 64bit number representing the live neighbours to the bottom left

   ALGORITHM(S): 
      botRow <- (row + 1) % ARSZ
      IF type > 0
         IF rightmost bit is 1
            return (oldGrid[topRow] shift bits 1 to right) bitOR 
                     0x8000000000000000 bitwiseAND oldGrid[topRow]
         ELSE
            return (oldGrid[topRow] shift bits 1 to right) bitAND oldGrid[row]
         ENDIF
      ELSE
         IF rightmost bit is 1
            return (oldGrid[topRow] shift bits 1 to right) bitOR 
                     0x8000000000000000 bitwiseAND ONESCOMPLEMENT(oldGrid[row])
         ELSE
            return (oldGrid[topRow] shift bits 1 to right) bitwiseAND 
                     ONESCOMPLEMENT(oldGrid[row])
         ENDIF
      ENDIF
*******************************************************************************/

uLLInt BL(int row, short type) {

   int botRow = (row + 1)%ARSZ;

   if(type) {
      if(oldGrid[botRow] & RBITMASK) {
         return (oldGrid[botRow] >> 1 | LBITMASK) & oldGrid[row];

      } else {
         return oldGrid[botRow] >> 1 & oldGrid[row];
      }

   } else {
      if(oldGrid[botRow] & RBITMASK) {
         return (oldGrid[botRow] >> 1 | LBITMASK) & ~oldGrid[row];

      } else {
         return oldGrid[botRow] >> 1 & ~oldGrid[row];
      }
   }
}


/*******************************************************************************

   PURPOSE: Get a binary number representing live neighbours to the bottom left
            of a row of cells.
   
   HISTORY: Coded by Justin Bertrand, based on documentation by D. Houtman 
            February 20th, 2015

   INPUTS:  Row, the row number in the grid to be affected
            Type, the type of cell to be acted upon, ALIVE or ZOMBIE

   OUTPUTS: A 64bit number representing the live neighbours

   ALGORITHM(S): 
   MASK <- LBITMASK
   newRow <- 0;
   Call T, B, L, R, TL, TR, BL, BR, and put all returned numbers in an array.
   Go through each vertical row of bits in the array and sum up positive bits
   FOR each column of cells
      IF ALIVE and has 2 or 3 neighbours
      OR
      IF ZOMBIE and has 3 neighbours
      newRow <- newRow bitwiseAND MASK
      MASK <- MASK bitshiftright 1
   ENDFOR
   return newRow
*******************************************************************************/

uLLInt sumNeighbours(int row, short type) {

   uLLInt Neighbours[8];
   uLLInt LMASK = LBITMASK;
   uLLInt newRow = 0;
   int totAliveNeighbours;

   Neighbours[TOP] = T(row, type);
   Neighbours[BOT] = B(row, type);
   Neighbours[LFT] = L(row, type);
   Neighbours[RGT] = R(row, type);
   Neighbours[TLF] = TL(row, type);
   Neighbours[TRT] = TR(row, type);
   Neighbours[BLF] = BL(row, type);
   Neighbours[BRT] = BR(row, type);

   if(type) {
      for(int index = 0; LMASK; ++index) {
         totAliveNeighbours = 0;

         for (unsigned int compass = 0; compass < 8; compass++) {
            totAliveNeighbours += ((LMASK & Neighbours[compass]) > 0);
         }

         if(totAliveNeighbours == 2 || totAliveNeighbours == 3) {
            newRow |= LMASK;
         }

         LMASK = LMASK >> 1;
      }

   } else {
      for(int index = 0; LMASK; ++index) {
         totAliveNeighbours = 0;

         for (unsigned int compass = 0; compass < 8; compass++) {
            totAliveNeighbours += ((LMASK & Neighbours[compass]) > 0);
         }

         if(totAliveNeighbours == 3) {
            newRow |= LMASK;
         }

         LMASK = LMASK >> 1;
      }
   }

   return newRow;
}


/*******************************************************************************

   PURPOSE: Print out an X if a cell is alive(1) or a space if dead(0)
   
   HISTORY: Created D. Houtman

   INPUTS:  A 64bit number representing live and dead cells

   OUTPUTS: Prints to the console.

   ALGORITHM(S): 
      MASK <- 0x8000000000000000
      DO
         IF (Cell bitwiseAND MASK)
            print('X')
         ELSE
            0x20
         ENDIF
      WHILE((MASK >>= 1) != 0)
      PRINT newline
*******************************************************************************/

void displayBinary(uLLInt x){

   uLLInt MASK=LBITMASK;

   do {
      printf("%c", (x & MASK)?'X': 0x20);
   } while((MASK >>= 1)!=0);
   printf("\n");
 }
