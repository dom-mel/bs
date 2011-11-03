/* example for a serial calculation of pi */ 
#include <stdio.h>
int main() {
 int n, i;
 double sum, pi, x, h;

 n = 1000000000;
 h = 1.0 / n;
 sum = 0.0;
 printf("starting \n");
 for ( i=1 ; i<n ; i++ ){
   x = h * ( i-0.5);
   sum = sum + (4.0/(1.0+x*x));
 }
 pi = h*sum;
 printf("pi is %f \n",pi);
}
