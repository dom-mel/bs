/* example for a calculation of pi with OpenMP */
#include <stdio.h>
#include <omp.h>

int main() {
 int n, i;
 double sum, pi, x, h;

 n = 1000000000;
 h = 1.0 / n;
 sum = 0.0;
 printf("starting \n");
 #pragma omp parallel for private(i,x) shared(h) reduction(+:sum)
 for ( i=1 ; i<n ; i++ ){
   x = h * ( i-0.5);
   sum = sum + (4.0/(1.0+x*x));
 }
 pi = h*sum;
 printf("pi is %f \n",pi);
}
