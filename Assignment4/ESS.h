#include <wchar.h>
#include <locale.h>

#define POWERGOOD 1
#define FLOORS 11
#define BASEMENT 0
#define GROUND 1
#define TOP (FLOORS-1) 

typedef enum nextFloor {
   DOWN=-1, STOP, UP
} nextFloor;

extern int repeat; //used to disable srand(), so the same sequence of instructions is called each time


extern int buttonPressedInside(void);
extern int* buttonPressedOutsideGoingUp(void);
extern int* buttonPressedOutsideGoingDown(void);
extern void openDoorCloseDoor(void);
extern int Go(nextFloor);
extern void initialize(void);

