/*==============================================================================
 Author:       =        Tim Siwula
 Liscense:     =        GPLv2
 File:         =        sets.c
 Version:      =        0.03
 Created:      =        09/23/2015
 ==============================================================================
 Debug:        =        gcc -DDEBUG -g -Wall -o sets sets.c
 Compile:      =        gcc -g -Wall -o sets sets.c
 Run:          =        ./sets
 ==============================================================================
 Purpose:      =        Implement a set abstract data type with operations
               =        union, intersection and set difference.
 ==============================================================================
 Input:        =        A sequene of single characters separated by white space.
 ==============================================================================
 Output:       =        The results of the set operation user selected.
 ==============================================================================
 Note:         =        1. The program is supposed to add new nodes to the head
               =           of the list.  For example, if the user enters
               =           1 2 3 0, the list *should* be head_p -> 3 -> 2 -> 1
  .......................................................................... */

/* ========================================================================== */
/*                          External libaries                                 */
/* ========================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* .......................................................................... */

/* ========================================================================== */
/*                          Structs                                           */
/* ========================================================================== */
struct set_s
{
    int element;
    struct set_s* next_p;
};
/* .......................................................................... */

/* ========================================================================== */
/*                          Custom function definitions                       */
/* ========================================================================== */
char Get_command(void);
int Member(struct set_s* head_p, int element);
void Print(struct set_s* head_p, int type);
struct set_s* Read_set(struct set_s* a_p, int* asize, int listNumber);
struct set_s* Append(struct set_s** C, struct set_s* c_p, int element);
struct set_s* Insert(struct set_s* head_p, int val);
struct set_s* Advance(struct set_s* node_p);
struct set_s* Free_list(struct set_s* head_p);
struct set_s* Union(struct set_s* a_p, int asize, struct set_s* b_p, int bsize,
                    struct set_s* c_p, int csize, struct set_s* C);
struct set_s* Intersection(struct set_s* a_p, int asize, struct set_s* b_p,
                   int bsize, struct set_s* c_p, int csize, struct set_s* C);
struct set_s* Difference(struct set_s* a_p, int asize, struct set_s* b_p,
                   int bsize, struct set_s* c_p, int csize, struct set_s* C);
/* .......................................................................... */

/* ========================================================================== */
/*                          Main( )                                           */
/* ========================================================================== */
int main(void)
{
# ifdef DEBUG
    printf("\n\t\t######################################");
    printf("\n\t\t#!!!   Debugger mode turned on.   !!!#");
    printf("\n\t\t#!!!   File: %s               !!!#", __FILE__);
    printf("\n\t\t#!!!   Line: %d.                  !!!#", __LINE__);
    printf("\n\t\t######################################\n\n");
# endif
    struct set_s* a_p = NULL;
    struct set_s* b_p = NULL;
    struct set_s* c_p = NULL;
    struct set_s* C = NULL;
    int asize, bsize, csize;
    asize = bsize = csize = 0;
    char command;
    command = Get_command();

    if(command != 'q' && command != 'Q')
    {
        a_p = Read_set(a_p, &asize, 1);
        b_p = Read_set(b_p, &bsize, 2);
        csize = asize + bsize;
    }

   while (command != 'q' && command != 'Q')
   {
       switch (command)
       {
           case 'u':
           case 'U':
                printf("\n\nFinding the union of the two sets. \n");
                c_p = Union(a_p, asize, b_p, bsize, c_p, csize, C);
                Print(a_p, 1);
                Print(b_p, 2);
                printf("Union: ");
                Print(c_p, 3);
                printf("\n");
                break;
           case 'i':
           case 'I':
               printf("\n\nFinding the intersection of the two sets. \n");
               c_p = Intersection(a_p, asize, b_p, bsize, c_p, csize, C);
               Print(a_p, 1);
               Print(b_p, 2);
               printf("Intersection: ");
               Print(c_p, 3);
               printf("\n");
               break;
           case 'd':
           case 'D':
               printf("\n\nFinding the difference of the two sets. \n");
               c_p = Difference(a_p, asize, b_p, bsize, c_p, csize, C);
               Print(a_p, 1);
               Print(b_p, 2);
               printf("Difference: ");
               Print(c_p, 3);
               printf("\n");
               break;
           case '\n':
               printf("\n$ ");
               break;
           default:
               printf("There is no %c command\n", command);
               printf("Please try aga_pn\n");
       }

       // free lists and reset list sizes.
        a_p = Free_list(a_p);
        b_p = Free_list(b_p);
        c_p = Free_list(c_p);
        C = Free_list(C);
        asize = bsize = csize = 0;

       // get command for operation to perform.
       command = Get_command();

       // read in new lists and update csize.
       if(command != 'q' && command != 'Q')
       {
           a_p = Read_set(a_p, &asize, 1);
           b_p = Read_set(b_p, &bsize, 2);
           csize = asize + bsize;
       }
   }

    return 0;
}  /* main */
/* .......................................................................... */

/*==============================================================================
 Function:     =        Free_list
 Purpose:      =        free each node in the list
 ==============================================================================
 Input arg:    =        1. head_p:  pointer to head of list/
 ==============================================================================
 Return val:   =        1. NULL pointer
 ==============================================================================
 Note:         =        head_p is set to NULL on completion, indicating
                        list is empty.
==============================================================================*/
struct set_s* Free_list(struct set_s* head_p)
{
   struct set_s* curr_p;
   struct set_s* temp_p;

   curr_p = head_p;
   while (curr_p != NULL)
   {
      temp_p = curr_p;
      curr_p = curr_p->next_p;
      free(temp_p);
   }
   curr_p = NULL;
   return curr_p;
}  /* Free_list */
/* .......................................................................... */

/*==============================================================================
 Function:     =        Union
 Purpose:      =        Union the contents of the arrays A and B into array C
 ==============================================================================
 Input arg:    =        1. struct set_s* a_p:  pointer to head of list a_p
               =        2. int asize:  size of elements in list a_p.
               =        3. struct set_s* b_p:  pointer to head of list b_p
               =        4. int bsize:  size of elements in list b_p.
               =        5. struct set_s* c_p:  pointer to head of list c_p
               =        6. int csize:  size of elements in list c_p.
               =        7. struct set_s* C:    pointer to head of list C
 ==============================================================================
 Return val:   =        1. struct set_s* C:  pointer to head of list C
 =============================================================================*/
struct set_s* Union(struct set_s* a_p, int asize, struct set_s* b_p, int bsize,
                    struct set_s* c_p, int csize, struct set_s* C )
{
    C = malloc(csize * sizeof(struct set_s));
    C->next_p = NULL;
    c_p = malloc(csize * sizeof(struct set_s));
    c_p->next_p = NULL;

    while (a_p != NULL &&  b_p != NULL)
        if (a_p->element <= b_p->element)
        {
          if (!Member(C, a_p->element))
          {
              c_p = Append(&C, c_p, a_p->element);
          }
            a_p = Advance(a_p);
        }
        else
        {  // b_p->data < a_p->data
          if (!Member(C, b_p->element))
          {
            c_p = Append(&C, c_p, b_p->element);
          }
            b_p = Advance(b_p);
        }
        // else
        // // case ==
        // // advance both

    while (a_p != NULL)
    {
      if (!Member(C, a_p->element))
      {
        c_p = Append(&C, c_p, a_p->element);
      }
      a_p = Advance(a_p);
    }

    while (b_p != NULL)
    {
      if (!Member(C, b_p->element))
      {
        c_p = Append(&C, c_p, b_p->element);
      }
      b_p = Advance(b_p);
    }
    return c_p;
}  /* Union */
/* .......................................................................... */

/*
 ==============================================================================
 Function:     =        Intersection
 Purpose:      =        Intersection the contents of the arrays A and B into
                        array C
 ==============================================================================
 Input arg:    =        1. struct set_s* a_p:  pointer to head of list a_p
               =        2. int asize:  size of elements in list a_p.
               =        3. struct set_s* b_p:  pointer to head of list b_p
               =        4. int bsize:  size of elements in list b_p.
               =        5. struct set_s* c_p:  pointer to head of list c_p
               =        6. int csize:  size of elements in list c_p.
               =        7. struct set_s* C:    pointer to head of list C
 ==============================================================================
 Return val:   =        1. struct set_s* C:  pointer to head of list C
 =============================================================================*/
 struct set_s* Intersection(struct set_s* a_p, int asize, struct set_s* b_p,
                    int bsize, struct set_s* c_p, int csize, struct set_s* C )
 {
     C = malloc(csize * sizeof(struct set_s));
     C->next_p = NULL;
     c_p = malloc(csize * sizeof(struct set_s));
     c_p->next_p = NULL;

     while (a_p != NULL &&  b_p != NULL)
         if (a_p->element <= b_p->element)
         {
           if (Member(b_p, a_p->element))
           {
               c_p = Append(&C, c_p, a_p->element);
           }
             a_p = Advance(a_p);
         }
         else
         {  // b_p->data < a_p->data
           if (Member(a_p, b_p->element))
           {
             c_p = Append(&C, c_p, b_p->element);
           }
             b_p = Advance(b_p);
         }

     while (a_p != NULL)
     {
       if (Member(b_p, a_p->element) && !Member(C, b_p->element))
       {
         c_p = Append(&C, c_p, a_p->element);
       }
       a_p = Advance(a_p);
     }

     while (b_p != NULL)
     {
       if (Member(a_p, b_p->element)  && !Member(C, b_p->element))
       {
         c_p = Append(&C, c_p, b_p->element);
       }
       b_p = Advance(b_p);
     }
    //  c_p = c_p;
     return c_p;
 }  /* Intersection */
 /* ........................................................................ */


/* =============================================================================
 Function:      =        Difference
 Purpose:       =        Difference the contents of the arrays A and B into
                         array C
 ==============================================================================
  Input arg:    =        1. struct set_s* a_p:  pointer to head of list a_p
                =        2. int asize:  size of elements in list a_p.
                =        3. struct set_s* b_p:  pointer to head of list b_p
                =        4. int bsize:  size of elements in list b_p.
                =        5. struct set_s* c_p:  pointer to head of list c_p
                =        6. int csize:  size of elements in list c_p.
                =        7. struct set_s* C:    pointer to head of list C
  ==============================================================================
  Return val:   =        1. struct set_s* C:  pointer to head of list C
  ============================================================================*/
 struct set_s* Difference(struct set_s* a_p, int asize, struct set_s* b_p,
                    int bsize, struct set_s* c_p, int csize, struct set_s* C )
 {
     C = malloc(csize * sizeof(struct set_s));
     C->next_p = NULL;
     c_p = malloc(csize * sizeof(struct set_s));
     c_p->next_p = NULL;

     while (a_p != NULL &&  b_p != NULL)
         if (a_p->element <= b_p->element)
         {
           if (!Member(b_p, a_p->element))
           {
               c_p = Append(&C, c_p, a_p->element);
           }
             a_p = Advance(a_p);
         }
         else
         {  // b_p->data < a_p->data
             b_p = Advance(b_p);
         }

     while (a_p != NULL)
     {
       if (!Member(b_p, a_p->element))
       {
         c_p = Append(&C, c_p, a_p->element);
       }
       a_p = Advance(a_p);
     }
     return c_p;
 }  /* Difference */
/* .......................................................................... */

/*==============================================================================
 Function:     =        Append
================================================================================
 Purpose:      =        Add a new element to the end of the list.
================================================================================
 Input arg:    =        1. struct set_s** C: A pointer to the list.
               =        2. struct set_s* c_p: Index of curr_p in C.
               =        3. int newElem: A element to add to the list.
================================================================================
 Output arg:   =        1. struct set_s* c_p: A pointer to head node of list.
==============================================================================*/
struct set_s* Append(struct set_s** C, struct set_s* c_p, int newElem)
{
    struct set_s* curr_p = *C;

    // go to last elem in list
    if(curr_p != NULL)
    {
      while (curr_p->next_p != NULL)
      {
          curr_p = curr_p->next_p;
      }
    }
    // create node and assign value
    struct set_s* newNode;
    newNode = malloc(sizeof(struct set_s));
    newNode->element = newElem;
    newNode->next_p = NULL;

    // set last to point to new elem
    curr_p->next_p = newNode;
    c_p = newNode;

    return *C;
}  /* Append */
/* .......................................................................... */

/*==============================================================================
Function:     =        Advance
================================================================================
Purpose:      =        Advance the current node to the next node.
================================================================================
Input arg:    =        1. struct set_s* node_p: A pointer to node in list.
================================================================================
Output arg:   =        1. temp_p: A pointer to the node next in the list.
==============================================================================*/
struct set_s* Advance(struct set_s* node_p)
{
    struct set_s* curr_p = node_p;
      if ( curr_p->next_p != NULL)
      {
        curr_p = curr_p->next_p;
        return curr_p;
      }
        return NULL;
}  /* Advance */
/* .......................................................................... */

/*==============================================================================
 Function:     =        Insert
 ===============================================================================
 Purpose:      =        Add node to the end of the list.
 ===============================================================================
 Input arg:    =        1. head_p:  Pointer to the head of the list.
                        2. element: new value to assign to the new node.
 ===============================================================================
 Output arg:   =        1. head_p:  Pointer to the head of the list.
 =============================================================================*/
struct set_s* Insert(struct set_s* head_p, int element)
{
    struct set_s* curr_p = head_p;
    struct set_s* pred_p = NULL;
    struct set_s* temp_p;

    while (curr_p != NULL)
    {
        if (curr_p->element >= element)
        {
            break;
        }
        pred_p = curr_p;
        curr_p = curr_p->next_p;
    }

    if (pred_p == NULL)
    {
        temp_p = malloc(sizeof(struct set_s));
        temp_p->element = element;
        temp_p->next_p = curr_p;
        return temp_p;
    }

    temp_p = malloc(sizeof(struct set_s));
    temp_p->element = element;
    temp_p->next_p = curr_p;
    pred_p->next_p = temp_p;
    return head_p;

}  /* Insert */
/* .......................................................................... */

/*==============================================================================
 Function:     =        Read_set
 ===============================================================================
 Purpose:      =        Read in the contents of the array A
 ===============================================================================
 Input arg:    =        1. struct set_s* a_p head_p:  Pointer to head of list.
                        2. int* asize: the number of elements to be read.
 ===============================================================================
 Output arg:   =        1. struct set_s* head_p: Pointer to head of list.
 =============================================================================*/
struct set_s* Read_set(struct set_s* a_p, int* asize, int listNumber)
{
  if (listNumber == 1)
  {
    printf("Enter the elements of A.\n");
  }
  else
  {
    printf("Enter the elements of B.\n");
  }
    int i;
    scanf("%d", &i);
    while (i > -1)
    {
        (*asize)++;
        a_p = Insert(a_p, i);
        scanf("%d", &i);
    }
    return a_p;
}

/*
 ==============================================================================
 Function:     =        Print
 Purpose:      =        Print list on a single line of stdout
 ==============================================================================
 Input arg:    =        1. head_p:  pointer to head of list
 ==============================================================================
 */
void Print(struct set_s* head_p, int type)
{
    struct set_s* curr_p;
    if (head_p != NULL)
    {
        printf("\n");
        if(type == 1)
        {
            printf("Set A = {");
            curr_p = head_p;
        }
        else if (type == 2)
        {
            printf("Set B = {");
            curr_p = head_p;
        }
        else
        {
            printf("Set C = {");
            curr_p = head_p->next_p;
        }
        while (curr_p != NULL)
        {
            if (curr_p)
                printf("%d", curr_p->element);
            if (curr_p->next_p != NULL)
                printf(", ");

            curr_p = curr_p->next_p;
        }
        printf("}.\n");
    }
    else
    {
      if(type == 1)
      {
          printf("Set A is empty \n");
      }
      else if (type == 2)
      {
          printf("Set B is empty \n");
      }
      else
      {
          printf("Set C is empty \n");
      }
    }
    printf("\n");
}  /* Print */
/* .......................................................................... */

/*-----------------------------------------------------------------
 * Function:    Member
 * Purpose:     search list for val
 * Input args:  head_p:  pointer to head of list
 *              val:  value to search for
 * Return val:  1 if val is in list, 0 otherwise
 */
int Member(struct set_s* head_p, int val) {
   struct set_s* curr_p = head_p;

   while (curr_p != NULL) {
      if (curr_p->element == val)
         return 1;
      else
         curr_p = curr_p->next_p;
   }
   return 0;
}  /* Member */

/*
 ==============================================================================
 Function:     =        Get_command
 Purpose:      =        Get a single character command from stdin
 ==============================================================================
 Output arg:   =        1. the first non-whitespace character from stdin
 ==============================================================================
 */
char Get_command(void)
{
    char c;
    printf("###########################################\n");
    printf("#\tPlease enter a command:           #\n");
    printf("#\t1.     u = union.                 #\n");
    printf("#\t2.     i = intersection.          #\n");
    printf("#\t3.     d = difference.            #\n");
    printf("#\t4.     q = quit.                  #\n");
    printf("###########################################\n");
    printf("$ ");
    /* Put the space before the %c so scanf will skip white space */
    scanf(" %c", &c);
    return c;
}  /* Get_command */
/* .......................................................................... */
