/* File:     linked_list.c
 *
 * Purpose:  Implement an unsorted linked list with ops insert (at head),
 *           print, member, delete, free_list.
 * 
 * Input:    Single character lower case letters to indicate operators, 
 *           followed by arguments needed by operators.
 * Output:   Results of operations.
 *
 * Compile:  gcc -g -Wall -o linked_list linked_list.c
 * Run:      ./linked_list
 *
 * Notes:
 *    1.  Repeated values are allowed in the list
 *    2.  Delete deletes all occurrences of a value
 *    3.  For verbose output, compile with DEBUG flag set. For
 *        example:
 *           gcc -g -Wall -DDEBUG -o linked_list linked_list.c
 *    4.  Program assumes an int will be entered when prompted
 *        for one.
 */
#include <stdio.h>
#include <stdlib.h>

struct list_node_s {
   int    data;
   struct list_node_s* next_p;
};

int  Member(struct list_node_s* head_p, int val);
struct list_node_s* Insert(struct list_node_s* head_p, int val);
struct list_node_s* Delete(struct list_node_s* head_p, int val);
void Print(struct list_node_s* head_p);
struct list_node_s* Free_list(struct list_node_s* head_p); 
char Get_command(void);
int  Get_value(void);
void Print_node(char node_name[], struct list_node_s* node_p);

/*-----------------------------------------------------------------*/
int main(void) {
   char command;
   int  value;
   struct list_node_s* head_p = NULL;  
      /* start with empty list */

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
         case 'm': 
         case 'M':
            value = Get_value();
            if (Member(head_p, value))
               printf("%d is in the list\n", value);
            else
               printf("%d is not in the list\n", value);
            break;
         case 'd':
         case 'D':
            value = Get_value();
            head_p = Delete(head_p, value);
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

   head_p = Free_list(head_p);

   return 0;
}  /* main */


/*-----------------------------------------------------------------
 * Function:    Member
 * Purpose:     search list for val
 * Input args:  head_p:  pointer to head of list
 *              val:  value to search for
 * Return val:  1 if val is in list, 0 otherwise
 */
int Member(struct list_node_s* head_p, int val) {
   struct list_node_s* curr_p = head_p;

   while (curr_p != NULL) {
      if (curr_p->data == val)
         return 1;
      else
         curr_p = curr_p->next_p;
   }
   return 0;
}  /* Member */


/*-----------------------------------------------------------------
 * Function:   Delete
 * Purpose:    Delete all occurrences of val from list
 * Input args: head_p: pointer to the head of the list
 *             val:    value to be deleted
 * Return val: Possibly updated pointer to head of list
 */
struct list_node_s* Delete(struct list_node_s* head_p, int val) {
   struct list_node_s* curr_p = head_p;
   struct list_node_s* pred_p = NULL;  /* Points to predecessor of curr_p or
                                        * NULL when curr_p is first node */
   int deleted_count = 0;

   /* Find node containing val and predecessor of this node */
   while (curr_p != NULL)
      if (curr_p->data == val) {
         if (pred_p == NULL) { /* val is in first node */
            head_p = curr_p->next_p;
            free(curr_p);
            curr_p = head_p;
         } else { /* val not in first node */
            pred_p->next_p = curr_p->next_p;
            free(curr_p);
            curr_p = pred_p->next_p;
         }
         deleted_count++;
      } else { // curr_p->data != val 
         pred_p = curr_p;
         curr_p = curr_p->next_p;
      }

   if (deleted_count == 0)
      printf("%d isn't in the list\n", val);

   return head_p;
}  /* Delete */


/*-----------------------------------------------------------------
 * Function:   Insert
 * Purpose:    Insert val at head of list
 * Input args: head_p: pointer to head of list
 *             val:  new value to be inserted
 * Return val: Pointer to head of list
 */
struct list_node_s* Insert(struct list_node_s* head_p, int val) {
   struct list_node_s* temp_p;

   temp_p = malloc(sizeof(struct list_node_s));
   temp_p->data = val;
   temp_p->next_p = head_p;
   head_p = temp_p;

   return head_p;
}   /* Insert */

/*-----------------------------------------------------------------
 * Function:   Print
 * Purpose:    Print list on a single line of stdout
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
#     ifdef DEBUG
      printf("Freeing %d\n", curr_p->data);
      fflush(stdout);
#     endif
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

   printf("Please enter a command (i, p, m, d, f, q):  ");
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
int  Get_value(void) {
   int val;

   printf("Please enter a value:  ");
   scanf("%d", &val);
   return val;
}  /* Get_value */

/*-----------------------------------------------------------------
 * Function:   Print_node
 * Purpose:    Print the value referred to by a node or NULL.
 *             Only used in DEBUG mode
 * Input args: node_name: Name of node pointer 
 *             node_p: pointer to node
 */
void Print_node(char node_name[], struct list_node_s* node_p) {
   if (node_p != NULL)
      printf("%s = %d\n", node_name, node_p->data);
   else
      printf("%s = NULL\n", node_name);
}  /* Print_node */
