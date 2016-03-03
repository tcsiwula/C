/* Author: Tim Siwula
*
*  File:     ll_sorted
 *
 * Purpose:  Implement a sorted linked list with ops Insert 
 *           and Print.
 * 
 * Input:    Single character lower case letters to indicate operations, 
 *           followed by arguments needed by operations.
 *
 * Output:   Results of operations.
 *
 * Compile:  gcc -g -Wall -o lls ll_sorted.c
 * Run:      ./lls
 *
 * Notes:
 *    1.  Repeated values are allowed in the list
 *    2.  Program assumes an int will be entered when prompted
 *        for one.
 *    3.  The insert function is missing some code ...
 */
#include <stdio.h>
#include <stdlib.h>

struct list_node_s {
   int    data;
   struct list_node_s* next_p;
};

struct list_node_s* Insert(struct list_node_s* head_p, int val);
void Print(struct list_node_s* head_p);
char Get_command(void);
int  Get_value(void);

/*-----------------------------------------------------------------*/
int main(void) {
   char command;
   int  value;
   struct list_node_s* head_p = NULL;  
      /* start with empty list */


   // test
   command = Get_command();
   while (command != 'q' && command != 'Q') {
      switch (command) {
         case 'i': 
         case 'I': 
            value = Get_value();
            head_p = Insert(head_p, value);
            break;
         case 'p':
         case 'P':
            Print(head_p);
            break;
         default:
            printf("There is no %c command\n", command);
            printf("Please try again\n");
      }
      command = Get_command();
   }

   return 0;
}  /* main */

/*-----------------------------------------------------------------*/
struct list_node_s* Insert(struct list_node_s* head_p, int val) {
   struct list_node_s* curr_p = head_p;
   struct list_node_s* pred_p = NULL;
   struct list_node_s* temp_p;

   // go through the list and compare until inserting value finds the right place to insert value
   while (curr_p != NULL) {
      if (curr_p->data >= val) 
         break;
      pred_p = curr_p;           // 
      curr_p = curr_p->next_p;
   } 

 // insert in the front of the list or insert into an empty list
if (pred_p == NULL)
{
   temp_p = malloc(sizeof(struct list_node_s));    // sets temp_p size 
   temp_p->data = val;
   temp_p->next_p = curr_p;
   return temp_p;
}
   // normal case: insert nums in the middle of list or at the tail of list
   temp_p = malloc(sizeof(struct list_node_s));    // sets temp_p size 
   temp_p->data = val;        // sets inserted value to temp_p's data
   temp_p->next_p = curr_p;
   pred_p->next_p = temp_p;   
   return head_p;

}  /* Insert */


/*-----------------------------------------------------------------
 * Function:   Print
 * Purpose:    print list on a single line of stdout
 * Input arg:  head_p
 */
void Print(struct list_node_s* head_p) {
   struct list_node_s* curr_p = head_p;

   printf("list = ");
   while (curr_p != NULL) {
      printf("%d ", curr_p->data);
      curr_p = curr_p->next_p;
   }  
   printf("\n");
}  /* Print */

/*-----------------------------------------------------------------
 * Function:      Get_command
 * Purpose:       Get a single character command from stdin
 * Return value:  The first non-whitespace character from stdin
 */
char Get_command(void) {
   char c;

   printf("Please enter a command (i, p, q):  ");
   /* Put the space before the %c so scanf will skip white space */
   scanf(" %c", &c);
   return c;
}  /* Get_command */

/*-----------------------------------------------------------------
 * Function:   Get_value
 * Purpose:    Get an int from stdin
 * Return val: The next int in stdin
 * Note:       Behavior unpredictable if an int isn't entered
 */
int  Get_value(void) {
   int val;

   printf("Please enter a value:  ");
   scanf("%d", &val);
   return val;
}  /* Get_value */