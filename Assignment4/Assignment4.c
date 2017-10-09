#include ESS.h


int main(void) {
	
	nextFloor travelling = STOP;
	int currentFloor = BASEMENT;
	int travelTo[FLOORS] = {0};
	int buttonPress = -1;

	initialize();

	while(POWERGOOD) {

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
		} else if(travelling = UP || currentFloor = BASEMENT) {
			
			int* temp = buttonPressedOutsideGoingUp();
			
			for(int index = currentFloor; index < FLOORS; ++index) {
				
				if(*(temp+index)) {
					travelTo[index] = *(temp+index);
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
					travelTo[index] = *(temp+index);
				}

				if(travelTo[index] && index < currentFloor) {
					travelling = DOWN;
				}
			}

		} else {
			
			for(int index = 0; index < FLOORS; ++index) {
				
				if(travelTo[index] && index > currentFloor) {
					travelling = UP;
				
				} else if(travelTo[index] && index < currentFloor) {
					travelling = DOWN;

				} else if(index == TOP && currentFloor != BASEMENT) {
					travelling = DOWN;
				
				} else {
					travelling = STOP;
				}
			}
		}

		currentFloor = Go(travelling);
	}
}