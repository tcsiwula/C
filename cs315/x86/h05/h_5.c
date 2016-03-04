//##  This is an embeded assembly file. Use file fibo.c to compile and run.
//##  compile:         clang -arch i386 h_5.s h_5.c -o h_5
//##  run              ./h_5
#include <stdio.h>
int fib(int n);

int main(void)
{
	int n, i;
	char repeat;
    printf("Enter a number for fib computation.\n");
    scanf("%d", &n);

  	for (i = 0; i < n; i++) 
  	{
    	Loop(i);
  	}

    printf("Try again? Enter y/n.\n");
    scanf(" %c", &repeat);
    if(repeat == 'y')
    {
  		main();
    }
    return 0;
}

void Loop(int i) {
  int r = fib(i);
  printf("fib(%d) -> %d\n", i+1, r);
}