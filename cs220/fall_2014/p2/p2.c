/*-----------------------------------------------------------------
 * ################### BEGIN p2.c #################
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author: Tim Siwula
 * -----------------------------------------------------------------
 * File: p2.c
 * -----------------------------------------------------------------
 * Purpose:  Implement an sorted doubly linked list of stings with ops insert (at head),
 *           print, search, delete, free_list.
 * -----------------------------------------------------------------
 * Input:    Single character lower case letters to indicate operators, 
 *           followed by arguments needed by operators.
 * -----------------------------------------------------------------
 * Output:   Results of operations.
 * -----------------------------------------------------------------
 * Compile:  gcc -g -Wall -o p2 p2.c
 * -----------------------------------------------------------------
 * Run:      ./p2
 * -----------------------------------------------------------------
 * Notes:
 *    1.  Repeated values are allowed in the list
 *    2.  delete only deletes the first occurrence of a value
 *    3.  Program assumes an int will be entered when prompted
 *        for one.
 * -----------------------------------------------------------------
 * ################### START GLOBAL VARIABLES ###################
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int STRING_MAX=100;

struct list_node_s {
   char*   data;
   struct list_node_s* next_p;
   struct list_node_s* pred_p;
};

struct list_s {
   struct list_node_s* h_p;
   struct list_node_s* t_p;
};
struct list_node_s* head_p;
struct list_node_s* Insert(char string[], struct list_s* list);
struct list_node_s* Delete(char string[], struct list_s* list);
struct list_node_s* Free_list(struct list_node_s* head_p); 
int  Member(char string[], struct list_s* list);
void Free_node(struct list_node_s* node_p);
void Print(struct list_s* list_s);
void Print_Head(struct list_node_s* head_p);
void Print_Tail(struct list_node_s* tail_p);
char Get_command(void);
char* Get_value(char string[]);
struct list_node_s* Allocate_Node(int size);


/*-----------------------------------------------------------------*/
int main(void) {

   char command;
   char  string[STRING_MAX];
   struct list_node_s* head_p = NULL;
   struct list_s list;
   char* val;
   /* start with empty list */
   /* Empty list has NULL h_p, t_p pointers */
   list.h_p = NULL;
   list.t_p = NULL;

   command = Get_command();
   while (command != 'q' && command != 'Q') {
      switch (command) {
         case 'i': 
         case 'I': 
            Get_value(string);
            head_p = Insert(string, &list);
            break;
         case 'p':
         case 'P':
            Print(&list);
            break;
         case 'm': 
         case 'M':
            Get_value(string);
            if (Member(string, &list))
               printf("%s is in the list\n", string);
            else
               printf("%s is not in the list\n", string);
            break;
         case 'd':
         case 'D':
            val = Get_value(string);
            Delete(val, &list);
            break;
         case 'f':
         case 'F':
            head_p = Free_list(head_p);
            break;
         default:
            printf("There is no %c command\n", command);
            printf("Please try again\n");
      }
      command = Get_command();
   }

   Free_list(head_p);

   return 0;
}  /* main */


/*-----------------------------------------------------------------
 * Function:    Member
 * Purpose:     search list for val
 * Input args:  head_p:  pointer to head of list
 *              val:  value to search for
 * Return val:  1 if val is in list, 0 otherwise
 */
int Member(char string[], struct list_s* list) {
   struct list_node_s* curr_p = list->h_p;

   while (curr_p != NULL) {
      if (strcmp(curr_p->data,string) == 0)
         return 1;
      else if(strcmp(curr_p->data, string) > 0)
         curr_p = curr_p->next_p;
   }
   return 0;
}  /* Member */


/*-----------------------------------------------------------------
 * Function:   Delete
 * Purpose:    Delete the first occurrence of val from list
 * Input args: head_p: pointer to the head of the list
 *             val:    value to be deleted
 * Return val: Possibly updated pointer to head of list
 */
struct list_node_s* Delete(char string[], struct list_s* list) {
   struct list_node_s* curr_p = list->h_p;

   /* Find node containing val and predecessor of this node */
   while (curr_p->next_p != NULL)
      if (strcmp(curr_p->data, string) >= 0)
         break;
      else { // curr_p->data != val 
         curr_p = curr_p->next_p;
      }


if (curr_p->pred_p == NULL) {
   list->h_p = curr_p->next_p;
      if(list->h_p != NULL)
         list->h_p -> pred_p = NULL;
      else
         list->t_p = NULL;

      Free_node(curr_p);
      }
else if (strcmp(curr_p->data, string) != 0){
   printf("%s is not in the list\n", string);
}
 else {
      if(curr_p->next_p == NULL){
         curr_p->pred_p->next_p = NULL;
         list->t_p = curr_p;
      }

      else{  
      curr_p->pred_p->next_p = curr_p->next_p;    
      curr_p->next_p->pred_p = curr_p->pred_p;
      }

      Free_node(curr_p);
   }

   return 0;
}  /* Delete */


// is are not linking to each other.



/*-----------------------------------------------------------------
 * Function:   Insert
 * Purpose:    Insert val at head of list
 * Input args: head_p: pointer to head of list
 *             val:  new value to be inserted
 * Return val: Pointer to head of list
 */
struct list_node_s* Insert(char string[], struct list_s* list) {
struct list_node_s* curr_p = list->h_p;
struct list_node_s* temp_p;

if(list->h_p == NULL){
    
      temp_p = Allocate_Node(strlen(string));
      strncpy(temp_p->data,string,strlen(string)+1);
      
      list->h_p = temp_p;
      list->h_p->pred_p = NULL;
      list->h_p->next_p = NULL;
     
   }
   else{
      
      while (curr_p->next_p != NULL) {
         if (strcmp(curr_p->next_p->data, string) >= 0) {
            break;
          }             
         curr_p = curr_p->next_p;
      }

      if (strcmp(curr_p->data,string) > 0){
         temp_p = Allocate_Node(strlen(string));
         strncpy(temp_p->data,string,strlen(string)+1);
       
         temp_p->pred_p = curr_p->pred_p;
         temp_p->next_p = curr_p;

         if(curr_p->pred_p == NULL)
            list->h_p = temp_p;
         else{
            curr_p->pred_p->next_p = temp_p;  
         }

         curr_p->pred_p = temp_p;
      }
      else if(strcmp(curr_p->data,string) < 0){

         temp_p = Allocate_Node(strlen(string));
         strncpy(temp_p->data,string,strlen(string)+1);
        
         temp_p->next_p = curr_p->next_p;
         temp_p->pred_p = curr_p;

         if(curr_p->next_p == NULL)
            list->t_p = temp_p;
         else{
            curr_p->next_p->pred_p = temp_p;  
         }

         curr_p->next_p = temp_p;
      }
      return head_p;

   }
   return 0;
}   /* Insert */ 

/*-----------------------------------------------------------------
 * Function:   Print
 * Purpose:    Print list on a single line of stdout
 * Input arg:  head_p
 */
void Print(struct list_s* list) {
   struct list_node_s* temp_p = list->h_p;

   printf("list = ");
   while (temp_p != NULL) {
      printf("%s ", temp_p->data);
      temp_p = temp_p->next_p;
   }  
   printf("\n");
}  /* Print */


/*-----------------------------------------------------------------
 * Function:    Free_list
 * Purpose:     free each node in the list
 * Input arg:   head_p:  pointer to head of list
 * Return val:  NULL pointer
 * Note:        head_p is set to NULL on completion, indicating
 *              list is empty.
 */
struct list_node_s* Free_list(struct list_node_s* head_p) {
   struct list_node_s* curr_p;
   struct list_node_s* temp_p;

   curr_p = head_p;
   while (curr_p != NULL) {
      temp_p = curr_p;
      curr_p = curr_p->next_p;
      free(temp_p);     
   }

   head_p = NULL;
   return head_p;
}  /* Free_list */

/*-----------------------------------------------------------------
 * Function:      Get_command
 * Purpose:       Get a single character command from stdin
 * Return value:  the first non-whitespace character from stdin
 */
char Get_command(void) {
   char c;

   printf("Please enter a command:\n");
   printf("1.     i = insert. ");
   printf("2.     p = print. ");
   printf("3.     h = print head. ");
   printf("4.     t = print tail. ");
   printf("5.     s = search. ");
   printf("6.     d = delete. ");
   printf("7.     f = free list. ");
   //printf("8.     fn = free node ");
   printf("9.     q = quit. ");
   //printf("10.     f = free list ");

   /* Put the space before the %c so scanf will skip white space */
   scanf(" %c", &c);
   return c;
}  /* Get_command */

/*-----------------------------------------------------------------
 * Function:   Get_value
 * Purpose:    Get an int from stdin
 * Return value:  the next int in stdin
 * Note:       Behavior unpredictable if an int isn't entered
 */
char* Get_value(char string[]) {
   printf("Now enter your favourite colour: ");
   scanf("%s", string);
   return string;
}  /* Get_value */

void Free_node(struct list_node_s* node_p) {
   free(node_p->data);
   free(node_p);
}  /* Free_node */

struct list_node_s* Allocate_Node(int size) {
   struct list_node_s* temp;
   temp = malloc(sizeof(struct list_node_s));
   temp->data = malloc(size*sizeof(char));
   return temp; 
}
/* ----------------------------------------------------------------
 * ################### END GET_USERS_REQUEST() ###################
 * ----------------------------------------------------------------*/

 /*-----------------------------------------------------------------
 * ################### END p2.c ###################
 *-----------------------------------------------------------------*/