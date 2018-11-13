#include <stdio.h>
#include <time.h>
#include <rpc/rpc.h>
#include "compute.h"
#include "malloc.h"
#define YES "Y"
#define NO "N"

static long * primes = NULL;
static long numOfPrimes = 0;
static long lastNumber = 2;

output * initOutput (long value1, long value2, char *answer) {
	output *out = (output *)malloc(sizeof(output));

	out->answer = (char *)malloc(sizeof(char));
	out->value1 = value1;
	out->value2 = value2;
	strcpy(out->answer, answer);
	return out;
}

void constructPrimes(int start, int end) {
	long prime, i, j;

	for (i = start; i <= end; i++) {
        prime = 1;
        for (j = 2; j * j <= i; j++) {
            if (i % j == 0 && i != j) {
                prime = 0;
                break;    
            }
        }   
        if(prime == 1) {
        	numOfPrimes++;
        	primes = (long *)realloc(primes, numOfPrimes * sizeof(long));
        	primes[numOfPrimes - 1] = i;
    	}
    }
    lastNumber = end + 1;
}

char * search(long start, long end, long x) {
	long mid;

	if (start <= end) {
		mid = (start + end) / 2;
		if (x == primes[mid]) {
			return YES;
		}
		if (x > primes[mid]) {
			return search(mid + 1, end, x);
		}
		if (x < primes[mid]) {
			return search(start, mid - 1, x);
		}
	}
	return NO;
}

long getFlag(char * answer) {
	return strcmp(answer, YES) == 0 ? 1 : 0;
}

output * checkComputation(long value) {
	long left = 0, right = numOfPrimes - 1;

	while (left <= right) {
		if (primes[left] + primes[right] == value) {
			return initOutput(primes[left], primes[right], YES);
		} else if (primes[left] + primes[right] < value) {
			left ++;
		} else {
			right--;
		}
	}
	return NULL;
}

output * get_compute_1_svc(input *in, struct svc_req *cl) {
	char * answer = NO;

	constructPrimes(lastNumber, in->value);
	if (in->value % 2 != 0) {
		answer = search(0, numOfPrimes - 1, in->value);
		return initOutput(in->value, getFlag(answer), answer);
	} else if (in->value == 2) {
		return initOutput(in->value, 1, YES);
	}

	return checkComputation(in->value);
}


