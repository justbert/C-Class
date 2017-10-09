/*******************************************************************************

   PURPOSE: Swaps two characters, input by the user, in the text of a cipher 
               until the plaintext is discovered. Also displays a frequency
               analysis of the characters to help in the swapping.
   
   HISTORY: Created Justin Bertrand, February 20th, 2015

   INPUTS: Two characters to be swapped.

   OUTPUTS: The cipher or cipher whose characters have been swapped.
            A frequency analysis of all the characters in the cipher.

   ALGORITHM(S): 
      Continue loop until stopped
         PRINT cipherText
         reset the character frequency array
         call to doFrequencyAnalysis
         call to sortFrequencyAddresses
         call to displayFrequencyAnalysis
         call to swapCipherTextChars
*******************************************************************************/


/*******************************************************************************
   Begin #include statements
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>


/*******************************************************************************
   Begin #define statements
*******************************************************************************/

#define ALPHABETSIZE 26


/*******************************************************************************
   Begin declarations
*******************************************************************************/

void doFrequencyAnalysis(char*, int*);
void sortFrequencyAddresses(int*, int**);
void displayFrequencyAnalysis(int**, int*);
void swapCipherTextChars(char*);


/*******************************************************************************
   Begin main()
*******************************************************************************/

int main(void) {
   
	char cipherText[] = "GEUZ UZT XQKOBTUEQC QY UZT KQHTKTCU QY UZT QOTDFUECW " 
				"BTHTD FCS EUL DTUVDC UQ EUL CQDKFB OQLEUEQC, UZT OFOTD UFOT "
				"FSHFCXTL QCT OQLEUEQC, UZT ODECU GZTTB ODECUL UZT XEOZTD XZFDFXUTD"
				" QC OFOTD UFOT, UZT RFDL EC";
	int charFreq[ALPHABETSIZE] = {0};
	int* alphaSort[ALPHABETSIZE] = {'\0'};

	while(1) {
      //Prints out ciphertext
		printf("\n%s\n\n", cipherText);
      
      //Reset the character frequency array
		memset(charFreq, 0, sizeof(charFreq));
		doFrequencyAnalysis(cipherText, charFreq);
		sortFrequencyAddresses(charFreq, alphaSort);
		displayFrequencyAnalysis(alphaSort, charFreq);

		swapCipherTextChars(cipherText);
	}

}


/*******************************************************************************

   PURPOSE: Count characters in a cipher to create a frequency analysis.
   
   HISTORY: Created J. Bertrand, March 20th, 2015

   INPUTS: A pointer to an array of character, the cipher, and a pointer to 
            an array of integers representing the frequency of characters in 
            the cipher.

   OUTPUTS: None.

   ALGORITHM(S): 
      FOR every CHAR in cipherText
         Increment pointer to integer representing current CHAR by one
      ENDFOR
*******************************************************************************/

void doFrequencyAnalysis(char *text, int *frequency) {
	
	int *temp;
	
	while(*text) {
      //Set temp to address of currently selected char 
		temp = *text - 'A' + frequency;
		*temp += (*text >= 'A' && *text <= 'Z');
		++text;
	} 
}


/*******************************************************************************

   PURPOSE: A comparator used as part of qsort.
   
   HISTORY: Created J. Bertrand, March 20th, 2015

   INPUTS: Two void pointers representing two pointers to pointers of integers

   OUTPUTS: 0 if both integers are the came
            >0 if elem1 is smaller than elem2
            <0 if elem1 is greater than elem2

   ALGORITHM(S): 
      RETURN pElem2 - pElem1
*******************************************************************************/

int compare(const void* pElem1, const void* pElem2) {
	return **(int**) pElem2 - **(int**) pElem1;
}


/*******************************************************************************

   PURPOSE: Sorts an array of integers representing character frequency from
               largest to smallest.
   
   HISTORY: Created J. Bertrand, March 20th, 2015

   INPUTS: A pointer, frequency, to an array of integers representing character 
               frequency where the first address is A and the last is Z
           A pointer to an array of pointers to integers, alphaSort, so as to 
               store the values of frequency in a decreasing order.

   OUTPUTS: None.

   ALGORITHM(S): 
      Copy addresses of values from frequency to alphaSort
      Call qsort on alphaSort
*******************************************************************************/

void sortFrequencyAddresses(int *frequency, int **alphaSort) {

	int **sortTemp = alphaSort;

	//copy alphasort pointers into frequency array
	for(int index = 0; index < ALPHABETSIZE; ++index) {
		*alphaSort = frequency+index;
		++alphaSort;
	}
   
   //Reset alphaSort pointer to initial value
	alphaSort = sortTemp;

	qsort((void *)alphaSort, ALPHABETSIZE, sizeof(int*), compare);
}


/*******************************************************************************

   PURPOSE: Prints out the frequency of every character within the cipher, one
               by one.
   
   HISTORY: Created J. Bertrand, March 20th, 2015

   INPUTS: A pointer to an array of pointers to integers, alphaSort,
               which is every characters frequency in decreasing order.
           A pointer, frequency, to an array of integers representing character 
               frequency where the first address is A and the last is Z

   OUTPUTS: None.

   ALGORITHM(S): 
      FOR index <- 0; index < ALPHABETSIZE(26); ++index
         PRINT character: characterFrequency
      ENDFOR
*******************************************************************************/

void displayFrequencyAnalysis(int **alphaSort, int *charFreq) {

	for(int index = 0; index < ALPHABETSIZE; ++index) {

		printf("%c:%d   ", (short)(*(alphaSort+index) - charFreq + 'A'), **(alphaSort+index));
	}
   
	printf("\n");
}


/*******************************************************************************

   PURPOSE: Swaps every position of two characters input by the user 
               in the cipher.
   
   HISTORY: Created J. Bertrand, March 20th, 2015

   INPUTS: A pointer to an array of characters which is the cipher.
           A character to be swapped
           Another character to swap the first one with

   OUTPUTS: None.

   ALGORITHM(S): 
      GET firstCharacter
      GET secondCharacter
      FOR every CHAR in cipher
         IF(CHAR == firstCharacter)
            CHAR = secondCharacter
            CONTINUE
         ELSE IF (CHAR == secondCharacter)
            CHAR = firstCharacter
         ENDIF
      ENDFOR
*******************************************************************************/

void swapCipherTextChars(char *text) {
	
	printf("\nEnter char to substitute: ");
	char firstChar = getchar();
	getchar();
	printf("Swap %c with character : ", (short)firstChar);
	char secondChar = getchar();
	getchar();

	for(int index = 0; *(text+index); ++index) {

		if(*(text+index) == firstChar) {
			*(text+index) = secondChar;
			continue;

		} else if(*(text+index) == secondChar) {
			*(text+index) = firstChar;
		}
	}
}