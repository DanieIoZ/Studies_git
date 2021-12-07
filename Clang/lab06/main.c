#include <stdio.h>
#include <stdbool.h>

#include <unistd.h>
#include <pthread.h>

void* thread1(void*);
void* thread2(void*);

int counter;
bool quit = false;

int main(void)
{
   counter = 0;


   getchar();
   quit = true;
   for (int i = 0; i < 2; ++i) {
   }
   return 0;
}

void* thread1(void *v)
{
   bool q = false;
   while (!q) {
      usleep(100 * 1000);
      counter += 1;
      q = quit;
   }
   return 0;
}

void* thread2(void *v) 
{
   bool q = false;
   while (!q) {
      printf("\rCounter %10i", counter);
      fflush(stdout);
      q = quit;
   }
   return 0;
}
