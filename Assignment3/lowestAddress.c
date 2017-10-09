#include <stdio.h>

char * getLowestAddress(char* []);

int main(void){

   char cAr[26] = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
   char* chAr[26];

   for (int i=0; i < 26; i++){
	chAr[i] = &cAr[i];
	printf("%c\t%p\n", cAr[i], chAr[i]);
   }

   char* Zaddress = getLowestAddress(chAr);
   printf("Character %c is stored at the lowest address at %p\n", 
	*Zaddress, Zaddress);
}


char *getLowestAddress(char* Ar[]){
   char *lowestAddr = Ar[0];
   for (int i = 1; i<26; i++)
      lowestAddr = ((Ar[i]) < lowestAddr)?Ar[i]: lowestAddr;
   return(lowestAddr);
}
