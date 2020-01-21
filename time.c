#include<time.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
  int i,j;
  struct timespec start, stop;
  i=clock_gettime(CLOCK_REALTIME, &start);
  for (int i=0; i<1000; i++)
    for (int j=0; j<1000;j++);
  j=clock_gettime(CLOCK_REALTIME, &stop);
  printf("%d, %d, %ld\n", i, j, stop.tv_nsec - start.tv_nsec);
}
