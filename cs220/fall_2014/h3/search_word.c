/* File:     search_word.c
 * Author:   Tim Siwula
 * Date:     Friday September 12th 2014
 *
 * Purpose:  search input text for all occurrences of a word.  
 *           This version gets the word from the command line and
 *           the input text from stdin.
 *
 * Compile:  gcc -g -Wall -o search_word search_word.c
 * Invoke:   ./search_word <word to be searched for>
 *
 * Input:    text
 * Output:   If found, the index of the words occurance and the total occurances.
 *           If not found, message saying not found.
 *
 * Notes:
 * 1.  Word searched for should contain no white space
 * 2.  Words in input text consist of strings separated by white space
 * 3.  No error check for strings exceeding MAX_STRING_LEN
 */
#include <stdio.h> // i/o
#include <string.h> // string compare strcmp
#include <stdlib.h>  /* For exit */
const int MAX_STRING_LEN = 100;
void Usage(char prog_name[]); // method construction.

int main(int argc, char* argv[]) {
   char search_for[MAX_STRING_LEN]; // this is the key used to search
   char current_word[MAX_STRING_LEN];  // This is the current word and increments word by word.
   int  scanf_rv;
   int  word_count = 0;  // keeps an index of the string inputed.
   int found_count = 0; // keeps track of how many matches

   /* Check that the user-specified word is on the command line */
   if (argc != 2) Usage(argv[0]); //error, calls Usage and lets user know.
   strcpy(search_for, argv[1]); // search_for has the key.

   printf("Enter the text to be searched\n");
   scanf_rv = scanf("%s", current_word); // takes the current_word and assigns it to scanf_rv.
   while ( scanf_rv != EOF  ) // reads until end of file. 
   { 
      if ( (strcmp(current_word, search_for)) == 0 ) // loop through words and if match key then proceed and add to found_word[].
      { 
         printf("\n Found <%s> at index %d !\n", search_for, word_count);
         found_count++; // found word increment total.
      }
      word_count++; // This keeps track of the index of the string.
      scanf_rv = scanf("%s", current_word); // this is the same as line 36, still not sure of it's signifinance. 
   }

   if (found_count == 0) // this means scanf_rv did not match agains the word and hit the end of the file. Let user know.
      printf("\n%s was not found in the %d words of input!\n",
         search_for, word_count);
   else 
      printf("\nThe word <%s> was found %d times! \n", // otherwise search_for was found at index word_count.
         search_for, found_count);

   return 0; //end of program. terminate.
}  /* main */

/* If user-specified word isn't on the command line, 
 * print a message and quit
 */
void Usage(char prog_name[]) {
   fprintf(stderr, "usage: %s <string to search for>\n",  // only called when the user does not include two arguments from when invoking the file.
      prog_name);
   exit(0);
}  /* Usage */