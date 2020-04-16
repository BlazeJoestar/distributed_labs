#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#define STEP 0.0000001
#define TO_RADIAN(a) a * (M_PI/180)  

const double step = 0.0000001;
double to_radian(double a) { return a * M_PI / 180.0; }

typedef struct pair {
	double beginning;
	double ending;
	double area;
} pair_t;

// calculates aproximate area under the figure
DWORD WINAPI sin_integration(void* args) {
	pair_t* temp = (pair_t*)args;
	double a = temp->beginning;
	double b = temp->ending;
	double sum = 0.0;
	for (double i = a; i < b; i += step) {
		sum += ((step / 2) * (sin(i) + sin(i + step)));
	}
	temp->area = sum;
	return 0;
}
pair_t* prepare_intervals(double a, double b, int intervals) {
	pair_t* arr = (pair_t*)malloc(sizeof(pair_t) * intervals);
	double temp = a, difference = (b - a) / intervals;
	for (int i = 0; i < intervals; i++, temp += difference) {
		arr[i].beginning = temp;
		arr[i].ending = temp + difference;
	}
	return arr;
}

HANDLE* viper_threads = NULL;

int main(int ac, char* av[]) {

	double beg = 0.0, end = 0.0;
	int threads = 1;
	if (ac < 4) {
		printf("please, provide:\n beginning of the interval (in radians): ");
		scanf("%lf", &beg);
		printf("please, provide:\n ending of the interval (in radians): ");
		scanf("%lf", &end);
		printf("please, provide:\n number of threads (1 - 4): ");
		scanf("%d", &threads);
		//if (threads > 4) {
		//	threads = 4;
		//}
		if (threads < 1) {
			threads = 1;
		}

	}
	else {
		beg = atol(av[1]);
		end = atol(av[2]);
		threads = atoi(av[3]);
	}
	//double result = sin_integration(beg, end);
	//printf("calculated integral of sin() for interval <%lf, %lf> (radians) calculated by %d proces%s\n result: %lf\n", beg, end, threads, (threads == 1) ? " " : "ses", result);

	pair_t* intervals = prepare_intervals(beg, end, threads);

	viper_threads = (HANDLE*)malloc(sizeof(HANDLE) * threads);
	DWORD thread_id;

	clock_t time_ = clock();

	for (int i = 0; i < threads; i++) {
		viper_threads[i] = CreateThread(
			NULL,
			0,
			sin_integration,
			(void*)&intervals[i],
			0,
			&thread_id
			);
	}
	
	DWORD synchro = WaitForMultipleObjects(
		threads,
		viper_threads,
		TRUE,
		INFINITE
		);

	double result = 0.0;

	time_ = clock() - time_;
	double time_total = ((double)time_)/CLOCKS_PER_SEC; 

	for (int i = 0; i < threads; i++) {
		result += intervals[i].area;
	}

	printf("calculated integral of sin() for interval <%lf, %lf> (radians) calculated by %d proces%s\n result: %lf\n time taken: %lf\n",
		beg, end, threads, (threads == 1) ? " " : "ses", result, time_total);

	for (int i = 0; i < threads; i++) {
		CloseHandle(viper_threads[i]);
	}

	free(intervals);
	free(viper_threads);
	return 0;
}

