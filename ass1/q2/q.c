#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <sched.h> 
#include <sys/sysinfo.h>
#include<pthread.h>

#define BILLION 1E9


int bs(long long int a[], long long int l, long long int r, long long int num){
	if(r>=l){
		int m = (l+r)/2;
		if(a[m] == num){
			return m;
		}
		else if(a[m]>num) return bs(a,l,m-1,num);
		return bs(a,m+1,r,num);
	}
	return -1;
}

void *thread(void *argv){
	cpu_set_t  mask;
    CPU_ZERO(&mask);
    CPU_SET(3, &mask);
	sched_setaffinity(0, sizeof(mask), &mask);

	// long long int accum = 0;
	// struct timespec Start, End;
	// clock_gettime(CLOCK_MONOTONIC, &Start);

	FILE *fp;
	fp = fopen("Worst.txt","a+");
	if(fp==NULL) {printf("Unable to open Worst.txt\n"); pthread_exit(NULL); }

	FILE *fp2;
	fp2 = fopen("timeVsLogn.txt","a+");
	if(fp2==NULL) {printf("Unable to open timeVsLogn.txt\n"); pthread_exit(NULL); }
	

	long long int *n = (long long int *)argv;
	printf("%lld\n",*n);

	long long int a[*n];
	for(long long int i=0;i<*n;i++) a[i] = i;


	long long int accum = 0;
	struct timespec Start, End;
	clock_gettime(CLOCK_MONOTONIC, &Start);
	
	int ans = 0;
	for(int i=0;i<1000;i++) ans = bs(a,0,*n-1,*n);


	
	clock_gettime(CLOCK_MONOTONIC, &End);
	accum = (End.tv_nsec - Start.tv_nsec)/1000;
	

	// printf("Size of array : %lld\n",*n);
	// printf("Index : %d\n",ans);
	// printf("Time taken to search : %lld\n",accum);

	fprintf(fp,"%lld %lld\n",*n,accum);
	fprintf(fp2,"%lf %lld\n",log((double) *n)/log(2.0),accum);
	

}

int main(){

	long long int size[]={50,100,500,1000,3000,5000,8000,10000,15000,20000,25000,30000,35000,40000,45000,50000};

	pthread_t thread_id;
	for(int i=0;i<16;i++){
		pthread_create(&thread_id,NULL,thread,(void *)&size[i]);
		pthread_join(thread_id,NULL);
	}   
   
}
