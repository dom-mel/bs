/* example for a calculation of pi        */
/* Parallelization via explicit threading */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#define THREADS 2
#define N 1000000000
typedef struct {
        int id;
} parm;
double sum[THREADS], h;
void *Calc_Partials(void *arg) //thread function to calculate partial sum
{
  int my_thrd;           //this thread's number ( 0 through NUM_THREADS-1 )
  int my_iters;          //number of iterations for each thread
  int my_start, my_end;  //iteration start and end for each thread
  int i;
  double  x, local_sum;
  parm *p=(parm *)arg;
  my_iters = N / THREADS;
  my_thrd = p->id;
  my_start = (my_iters * my_thrd) + 1;
  my_end = my_iters * (my_thrd+1);
  for ( i=my_start ; i < my_end ; i++ ){
   x = h * ( i-0.5);
   local_sum = local_sum + (4.0/(1.0+x*x));
  }
  sum[my_thrd] = local_sum;  //store local partial to global partial
  return ( NULL );
}
int main(int argc, char* argv[]) {
        int n,i;
        pthread_t *threads;
        pthread_attr_t pthread_custom_attr;
        parm *p;
        h = 1.0 / N;
        threads=(pthread_t *)malloc(THREADS*sizeof(*threads));
        pthread_attr_init(&pthread_custom_attr);
        p=(parm *)malloc(sizeof(parm)*THREADS);
        /* Start up thread */
        for (i=0; i<THREADS; i++) {
                p[i].id=i;
                pthread_create(
                   &threads[i],
                   &pthread_custom_attr,
                   Calc_Partials,
                   (void *)(p+i));
        }
        /* Synchronize the completion of each thread. */
        for (i=0; i<THREADS; i++) pthread_join(threads[i],NULL);
        printf( "pi is %f\n", (sum[0]+sum[1])*h);
        free(p);
}  
