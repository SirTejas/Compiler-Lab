#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <sched.h> 
#include <sys/sysinfo.h>
#include<pthread.h>

#define BILLION 1E9


int linearSearch(long long int a[], long long int k, long long int n){
	
	long long int i=0;
	for(i=0;i<n;i++){
		if(a[i]==k) return 1;
	}

	return -1;
}

void *Thread(void *argv){
	cpu_set_t  mask;
    CPU_ZERO(&mask);
    
    CPU_SET(3, &mask);
	sched_setaffinity(0, sizeof(mask), &mask);

	struct timespec Start, End;
	clock_gettime(CLOCK_MONOTONIC, &Start);

	FILE *fp;
	fp = fopen("Worst2.txt","a+");
	if(fp==NULL) {printf("Unable to open Worst.txt\n"); pthread_exit(NULL);}

	

	// double logn = log((double) n);
	// double log2 = log(2.0);

	
	
	long long int *n = (long long int *)argv;
	printf("%lld\n",*n);
		

	long long int a[*n];
	for(long long int i=0;i<*n;i++) a[i] = i;


	long long int accum = 0;
	// struct timespec Start, End;
	
	// clock_gettime(CLOCK_MONOTONIC, &Start);
	
	int ans = 0;
	for(int i=0;i<1;i++) ans = linearSearch(a,*n,*n);

	// clock_gettime(CLOCK_MONOTONIC, &End);

	// accum = (End.tv_nsec - Start.tv_nsec)/100;
	
	

	printf("Size of array : %lld\n",*n);
	printf("Index : %d\n",ans);
	printf("Time taken to search : %lld\n",accum);	

	fprintf(fp,"%lld %lld\n",*n,accum);

	clock_gettime(CLOCK_MONOTONIC, &End);
	accum = (End.tv_nsec - Start.tv_nsec)/1;
		

}


int main(){


	pthread_t thread_id;
	long long int size[]={50,100,500,1000,5000,10000,20000,40000,60000,80000,100000,150000,200000};
	// for(int i=0;i<13;i++) printf("%lld ",size[i]);


	for(int i=0;i<13;i++){
		pthread_create(&thread_id, NULL, Thread, (void *)&size[i]);
		pthread_join(thread_id, NULL);
	}
	
   
   
}
