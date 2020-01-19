/*
*  clang -std=c11 -lpthread  threads.c 
*  gcc -std=c11   threads.c -lpthread
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5
void *print_hello(void *threadid)
{
  long tid;
  tid = (long)threadid;
  printf("Hello World! It’s me, thread #%ld!\n", tid);
  sleep(1);
  pthread_exit(NULL);
}

#if defined(__STDC_NO_THREADS) && __STDC_NO_THREADS__ == 1
#error "No threading support"
#else
//#include <threads.h>
#endif

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;
  for (t = 0; t < NUM_THREADS; t++)
  {
    printf("main: creating thread %ld\n", t);
    rc = pthread_create(threads + t, NULL, print_hello, (void *)t);
    if (rc)
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  pthread_exit(NULL);  // clean up procedure invoked
  printf("\nthe end"); // so here is unreachable
}