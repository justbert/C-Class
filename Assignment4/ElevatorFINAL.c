/*******************************************************************************

   PURPOSE: Simulates the operations of an elevator in an Elevator Simulation
   				Program
   
   HISTORY: Created Justin Bertrand, April 15th, 2015

   INPUTS: A carriage return to continue the simulation.

   OUTPUTS: A simulated elevator shaft, with accompanying requests for stops,
   			and passengers.

   ALGORITHM(S): 
   
      ORIGINAL PSEUDOCODE
      
      travelTo[FLOORS]
      travelling <- STOP
      currentFloor <- BASEMENT
      buttonPress <- -1

      WHILE(POWERGOOD)

         buttonPress <- buttonPressedInside()
         
         IF(buttonPress != -1)
            travelTo[buttonPress] <- 1
            buttonPress <- -1
         ENDIF
         
         //Checks to see if the currentFloor is a stop
         IF(travelTo[currentFloor])
            openDoorCloseDoor()
            travelling = STOP;
            travelTo[currentFloor] <- 0
         
         ELSE IF(currentFloor = BASEMENT AND travelling = DOWN) 
            travelling = STOP;
            
         //If travelling up or at the basement, checks if more buttons have
         //been pressed
         ELSE IF(travelling = UP OR (currentFloor = BASEMENT)) 
            temp[] <- buttonPressedGoingUp()	
            FOR(index <- currentFloor; index < FLOORS; ++index)
               IF(temp[index])
                  travelTo[index] <- temp[index]
               ENDIF
               IF(travelTo[index] AND index > currentFloor)
                  travelling <- UP
               ENDIF
            ENDFOR
         
         //If travelling down or at the top floor, checks to see if more 
         // buttons have been pressed down
         ELSE IF (travelling = DOWN OR currentFloor = FLOORS-1)
            temp[] <- buttonPressedGoingDown()	
            
            FOR(index <- currentFloor; index >= BASEMENT; --index)
               
               IF(temp[index])
                  travelTo[index] <- temp[index]
               ENDIF
               
               IF(travelTo[index] AND index < currentFloor)
                  travelling <- DOWN
               ENDIF
            ENDFOR
               
         ELSE 
            FOR(index <- 0; index < FLOORS; ++index)
               
               IF(travelTo[index] AND index > currentFloor)
                  travelling = UP
               
               ELSE IF(travelTo[index] AND index < currentFloor)
                  travelling = DOWN
               
               ELSE IF(index = FLOORS-1 AND currentFloor != BASEMENT)
                  travelling = DOWN
               
               ELSE
                  travelling <- STOP
               ENDIF
            ENDFOR
         ENDIF
         
         currentFloor <- Go(travelling)

      ENDWHILE
*******************************************************************************/


/*******************************************************************************
   Begin #include statements
*******************************************************************************/
#include <stdio.h>
#include "ESS.h"


/*******************************************************************************
   Begin main()
*******************************************************************************/
int main(void) {

	nextFloor travelling = STOP;
	int currentFloor = BASEMENT;
	int travelTo[FLOORS] = {0};
	int buttonPress = -1;

   //Initializes the Elevator Simulation Software (ESS)
	initialize();

	do {

		//MODIFICATION
		//Checks to see if anyone wants to get on at the basement,
		//while on standby.
		if(currentFloor == BASEMENT) {
			int* tempUp = buttonPressedOutsideGoingUp();
			int* tempDown = buttonPressedOutsideGoingDown();
			if(*tempUp || *tempDown)
				travelTo[BASEMENT] = 1;
		}

		//Checks to see if any buttons have been
		//pressed inside the elevator
		do {

			buttonPress = buttonPressedInside();
			
			if(buttonPress > -1) {
			
				travelTo[buttonPress] = 1;
			}
		
		} while(buttonPress != -1);

		//Checks to see if the current floor is a stop
		if(travelTo[currentFloor]) {
		
			openDoorCloseDoor();
			travelling = STOP;
			travelTo[currentFloor] = 0;
		
		//Prevents the elevator from going lower than the basement
		} else if(currentFloor == BASEMENT && travelling == DOWN) {
		
			travelling = STOP;

		//If travelling up or at the basement, checks to see if more
		//buttons have been pressed
		} else if(travelling == UP || currentFloor == BASEMENT) {
			
			//MODIFICATION
			//Will add the highest floor requesting to go down
			//to the list of destinations to travel to.
			int* temp = buttonPressedOutsideGoingDown();

			for(int index = TOP; index >= BASEMENT; --index) {
				if(*(temp+index)) {
					travelTo[index] = 1;
					break;
				}
			}
			
			temp = buttonPressedOutsideGoingUp();

			for(int index = currentFloor; index < FLOORS; ++index) {
				
				if(*(temp+index)) {
					travelTo[index] = 1;
				} 

				if(travelTo[index] && index > currentFloor) {
					travelling = UP;
				}
			}

		//If travelling down or at the top floor, checks to see if more
		//buttons have been pressed.
		} else if(travelling == DOWN || currentFloor == TOP) {

			int* temp = buttonPressedOutsideGoingDown();

			for(int index = currentFloor; index >= BASEMENT; --index) {

				if(*(temp+index)) {
					travelTo[index] = 1;
				}

				if(travelTo[index] && index < currentFloor) {
					travelling = DOWN;
				}
			}

		} else {
         
			//If stopped, will decide how to proceed
			//MODIFICATION: flipped the loop
			for(int index = TOP; index >= BASEMENT; --index) {
				
            //If a stop request was made higher up, will
            //proceed up.
				if(travelTo[index] && index > currentFloor) {
					travelling = UP;
					//MODIFICATION: Added the break to preserve
					//correct order of operations
					break;
				
            //If a stop request was made lower down, will
            //proceed down.
				} else if(travelTo[index] && index < currentFloor) {
					travelling = DOWN;
					//MODIFICATION: Added the break to preserve
					//correct order of operations
					break;
					
            //IF no stops are requested, and it is not at the basement
            //will go down.
				} else if(index == BASEMENT && currentFloor != BASEMENT) {
					travelling = DOWN;
						
				} else {
					travelling = STOP;
				}
			}
		}

		currentFloor = Go(travelling);
	
	} while(POWERGOOD && getchar());
}