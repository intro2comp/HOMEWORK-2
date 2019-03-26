#include <pthread.h> // pthread_t, pthread_create, pthread_exit, pthread_join
#include <stdlib.h>  // malloc, free
#include <stdio.h>   // printf


void array_fib(int n, int *array)
{
  if (n == 0 || n == 1)
    array[n] = n;
  else
    array[n] = array[n - 1] + array[n - 2];
}


/* Start thread wrappers */
struct thread_fib_args {
  int n;
  int *arr;
};


void *thread_calc_fib(void *arg_struct)
{
  struct thread_fib_args *args = arg_struct;

  for (int i = 0; i < args->n; i++)
    array_fib(i, args->arr);

  pthread_exit(0);
}


void *thread_print_fib(void *arg_struct)
{
  struct thread_fib_args *args = arg_struct;

  pthread_t child;

  pthread_create(&child, NULL, thread_calc_fib, args);

  pthread_join(child, NULL);

  for (int i = 0; i < args->n; i++)
    printf("%d: %d\n", i + 1, args->arr[i]);

  pthread_exit(0);
}
/* End thread wrappers */


int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("Usage: %s COUNT\n", argv[0]);
    return 1;
  }

  const int count = atoi(argv[1]);

  struct thread_fib_args parent_args;

  parent_args.n = count;
  parent_args.arr = malloc(sizeof(int) * count);

  pthread_t parent;

  pthread_create(&parent, NULL, thread_print_fib, &parent_args);

  pthread_join(parent, NULL);

  free(parent_args.arr);

  return 0;
}
