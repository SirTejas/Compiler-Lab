#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <sched.h> 
#include <sys/sysinfo.h>
#include<pthread.h>



void selectionSort(int arr[], int n){
    int i, j, min_idx;  
    for (i = 0; i < n-1; i++){ 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 
  
        // Swap the found minimum element with the first element
        int t = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = t; 
    } 
} 

void *Thread(void *argv){
	cpu_set_t  mask;
    CPU_ZERO(&mask);
    CPU_SET(3, &mask);
	sched_setaffinity(0, sizeof(mask), &mask);

	// struct timespec Start, End;
	// clock_gettime(CLOCK_MONOTONIC, &Start);
    // clock_gettime(CLOCK_MONOTONIC, &End);
	// int accum = (End.tv_nsec - Start.tv_nsec)/100;
		
	int *n = (int *)argv;
	int a[*n];
	for(int i=*n-1;i>=0;i--) a[i] = i;



	clock_t t = clock();
	selectionSort(a,*n);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    clock_t tt = clock();
    for(int i=0;i<*n;i++){
        for(int j=0;j<*n;j++){}
    }

    tt = clock()-tt;
    double time_taken2 = ((double)tt)/CLOCKS_PER_SEC;

	

    printf("%d %f %f\n",*n,time_taken,time_taken2);
		

}


int main(){


	pthread_t thread_id;
	int size[]={3000,6000,9000,12000,15000,18000,21000,24000,27000,30000};

	for(int i=0;i<10;i++){
		pthread_create(&thread_id, NULL, Thread, (void *)&size[i]);
		pthread_join(thread_id, NULL);
	}
	
   
   
}
