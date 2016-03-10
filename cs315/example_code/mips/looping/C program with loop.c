#include <stdio.h>

int main(void) {
   int n, i, sum;

   scanf("%d", &n);

   sum = 0;
   for (i = 1; i <= n; i++)
      sum += i;

   printf("%d\n", sum);

   return 0;
}
