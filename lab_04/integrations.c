#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>

#define STEP 0.001
#define TO_RADIAN(a) a * (M_PI/180)  

const double step = 0.0001;
double to_radian(double a){ return a * M_PI / 180.0; }

// calculates aproximate area under the figure
double sin_integration(double a, double b){
	double sum = 0.0;
	for(double i = a; i < b; i+=step){
		// STEP == HEIGHT --> WE CALCULATE THE AREA OF TRAPEZIOD
		//if ((i > 0.0 && i+step > 0.0) || (i < 0.0 && i+step < 0.0)) {
			sum += ( (step/2) * (sin(i) + sin(i+step)) );
	//	}
	}
	return sum; 
}

HANDLE viper_threads[4];

int main(int ac, char* av[]) {

	double beg = 0.0, end = 0.0;
	int threads = 1;
	if (ac < 4){
		printf("please, provide:\n beginning of the interval (in radians): ");
		scanf("%lf", &beg);
		printf("please, provide:\n ending of the interval (in radians): ");
		scanf("%lf", &end);
		printf("please, provide:\n number of threads: ");
		scanf("%d", &threads);
	}
	else {
		beg = atol(av[1]);
		end = atol(av[2]);
		threads = atoi(av[3]);
	}
	double result = sin_integration(beg, end);
	printf("calculated integral of sin() for interval <%lf, %lf> (radians) calculated by %d proces%s\n result: %lf\n", beg, end, threads, (threads==1)? " " : "ses", result);
	
	//printf("\n %lf \n", sin(TO_RADIAN(end)));
	
	return 0;
}

