#include <math.h>    // sqrt, pow
#include <stdbool.h> // bool
#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free
#include <pthread.h>  // pthread_create, pthread_join


/* Reverse the order of an integer *n*. */
int reverse_integer(int n)
{
  int result = 0;

  while (n) {
    result = result * 10 + n % 10;
    n = n / 10;
  }

  return result;
}


/* An implimentation of the Sieve of Eratosthenes, used to find prime
 * numbers nievely and efficently. In this case we use the algorithm to
 * produce primes less than or equal to *n*. The primes are represented
 * as an array of booleans, which if true denotes a prime number.
 */
bool *generate_primes(int n)
{
  bool *A = malloc(sizeof(bool) * n + 1);

  for (int i = 0; i <= n; i++)
    A[i] = true;

  for (int i = 2; i < sqrt(n); i++)
    if (A[i])
      for (int j = pow(i, 2); j <= n; j += i)
        A[j] = false;

  return A;
}


void print_primes(int n, bool *prime_array)
{
  for (int i = 2; i <= n; i++)
    if (prime_array[i])
      printf("Found prime: %d\n", i);
}



void print_reverse_primes(int n, bool *prime_array)
{
  for (int i = 2; i <= n; i++)
    if (prime_array[i]) {
      int reversed = reverse_integer(i);

      // Skip a number if it too large or is a duplicate
      if (reversed > n || i > reversed || reversed == i)
        continue;

      if (prime_array[reversed])
        printf("Reverse prime: %d (rev of %d)\n", reversed, i);
    }
}


/* Start thread wrappers */
struct thread_print_primes_args {
  int n;
  bool *primes;
};


struct thread_print_reverse_primes_args {
  int n;
  bool *primes;
};


void *thread_print_primes(void *arguments)
{
  struct thread_print_primes_args *args = arguments;

  print_primes(args->n, args->primes);

  return NULL;
}


void *thread_print_reverse_primes(void *arguments)
{
  struct thread_print_primes_args *args = arguments;

  print_reverse_primes(args->n, args->primes);

  return NULL;
}
/* End thread wrappers */


int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("Usage: %s INT\n", argv[0]);
    return 1;
  }

  const int value = atoi(argv[1]);

  // Generate an array of booleans (true means prime)
  bool *primes = generate_primes(value);

  // Initialize two thread ID values
  pthread_t prime_thread, rev_prime_thread;

  // Create a structs containing function arguments
  struct thread_print_primes_args prime_thread_args;

  prime_thread_args.n = value;
  prime_thread_args.primes = primes;

  // This is ugly
  struct thread_print_reverse_primes_args rev_prime_thread_args;

  rev_prime_thread_args.n = value;
  rev_prime_thread_args.primes = primes;

  pthread_create(
    &prime_thread, NULL, thread_print_primes,
    (void *)&prime_thread_args
  );

  pthread_create(
    &rev_prime_thread, NULL, thread_print_reverse_primes,
    (void *)&rev_prime_thread_args
  );

  pthread_join(prime_thread, NULL);
  pthread_join(rev_prime_thread, NULL);

  return 0;
}
