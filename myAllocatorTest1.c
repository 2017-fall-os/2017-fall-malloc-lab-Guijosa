#include "stdio.h"
#include "stdlib.h"
#include "myAllocator.h"
#include "sys/time.h"
#include <sys/resource.h>
#include <unistd.h>

double diffTimeval(struct timeval *t1, struct timeval *t2) {
  double d = (t1->tv_sec - t2->tv_sec) + (1.0e-6 * (t1->tv_usec - t2->tv_usec));
  return d;
}

void getutime(struct timeval *t)
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  *t = usage.ru_utime;
}

int main() 
{
  void *p1, *p2, *p3, *p4;
  void *p5, *p6, *p7, *p8;
  arenaCheck();
  p1 = nextFitAllocRegion(131072);
  arenaCheck();
  p2 = nextFitAllocRegion(131072);
  arenaCheck();
  p3 = nextFitAllocRegion(131072);
  arenaCheck();
  p4 = nextFitAllocRegion(131072);
  arenaCheck();
  p5 = nextFitAllocRegion(131072);
  arenaCheck();
  p6 = nextFitAllocRegion(131072);
  arenaCheck();
  p7 = nextFitAllocRegion(131072);
  arenaCheck();
  p8 = nextFitAllocRegion(130944);
  printf("%8zx %8zx %8zx %8zx %8zx %8zx %8zx %8zx\n",
	 p1, p2, p3, p4, p5, p6, p7, p8);
  arenaCheck();
  printf("All memory has been allocated\n");
  printf("Freeing second region\n");
  freeRegion(p2);
  arenaCheck();
  printf("Freeing seventh region\n");
  freeRegion(p7);
  arenaCheck();
  printf("Allocating mem with first fit should allocate second region\n");
  p2 = firstFitAllocRegion(131072);
  arenaCheck();
  printf("Freeing third region\n");
  freeRegion(p3);
  arenaCheck();
  printf("Allocating third region with firstFit\n");
  p3 = firstFitAllocRegion(131072);
  arenaCheck();
  printf("Freeing second region\n");
  freeRegion(p2);
  arenaCheck();
  printf("Allocating mem with nextFit should allocate seventh region\n");
  p7 = nextFitAllocRegion(131072);
  arenaCheck();
  printf("Allocating mem with nextFit should allocate second region\n");
  p2 = nextFitAllocRegion(131072);
  arenaCheck();
  printf("%8zx %8zx %8zx %8zx %8zx %8zx %8zx %8zx\n",
	 p1, p2, p3, p4, p5, p6, p7, p8);
  printf("All memory alocated\n");
  printf("Freeing second region\n");
  freeRegion(p2);
  arenaCheck();
  printf("Resizing first region\n");
  p1 = resizeRegion(p1,262144);
  arenaCheck();
  printf("Freeing everything\n");
  freeRegion(p1);
  arenaCheck();
  freeRegion(p2);
  arenaCheck();
  freeRegion(p3);
  arenaCheck();
  freeRegion(p4);
  arenaCheck();
  freeRegion(p5);
  arenaCheck();
  freeRegion(p6);
  arenaCheck();
  freeRegion(p7);
  arenaCheck();
  freeRegion(p8);
  arenaCheck();
  {				/* measure time for 10000 mallocs */
    struct timeval t1, t2;
    int i;
    getutime(&t1);
    for(i = 0; i < 10000; i++)
      if (nextFitAllocRegion(4) == 0) 
	break;
    getutime(&t2);
    printf("%d nextFitAllocRegion(4) required %f seconds\n", i, diffTimeval(&t2, &t1));
  }
  return 0;
}



