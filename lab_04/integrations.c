#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STEP 0.001

// calculates aproximate area under the figure
double sin_integration(double a, double b){
	double sum = 0.0;
	for(double i = a; i < b; i+=STEP){
		sum += (sin(i) * STEP);
	} 
}

int main(int ac, char* av[]) {
	double beg, end;
	int processes = 1;
	if (ac < 4){
		printf("please, provide:\n beginning of the interval: ");
		scanf("%lf", &beg);
		printf("please, provide:\n ending of the interval: ");
		scanf("%lf", &end);
		printf("please, provide:\n number of processes: ");
		scanf("%d", &processes);
	}
	else {
		beg = atol(av[1]);
		end = atol(av[2]);
		processes = atoi(av[3]);
	}
	double result = sin_integration(beg, end);
	printf("calculated integral of sin() for interval <%lf, %lf> calculated by %d proces%s\n result: %lf\n", beg, end, processes, (processes==1)? " " : "ses", result);


	return 0;
}

