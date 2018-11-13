#include <stdio.h>
#include <time.h>
#include <rpc/rpc.h>
#include "compute.h"
#define YES "YES"
#define NO "NO"
#define OUTPUT_FILE "out.txt"

char * getAnswer(char *c) {
	return strcmp(c, "Y") == 0 ? YES : NO;
}

void printOutput(FILE *fo, output *out) {
	fprintf(fo, "%s %ld %ld\n", getAnswer(out->answer), out->value1, out->value2);
}

input * initInput(long value) {
	input *in = (input *)malloc(sizeof(input));

	in->value = value;
	return in;
}

void sendToCompute(FILE *fp, CLIENT *client, FILE *fo) {
	input *in = NULL;
	output *out = NULL;
	long value;

	while (fscanf(fp, "%ld", &value) != EOF) {
		in = initInput(value);
		out = get_compute_1(in, client);
		printOutput(fo, out);
		free(in);
	}
}

int main(int argc, char *argv[]) {
	CLIENT *client = NULL;
	FILE *fp = NULL;
	FILE *fo = NULL;

	if (argc < 3) {
		perror("Few arguments.\n The process has been killed with the following status");
		return -1;
	}
	client = clnt_create(
		argv[1],
		COMPUTE_PROG,
		COMPUTE_VERS,
		"tcp"
		);
	if (client == NULL) {
		perror("Client not created.\n The process has been killed with the following status");
		return -1;
	}
	fp = fopen(argv[2], "r+");
	if (fp == NULL) {
		perror("File not found.\n The process has been killed with the following status");
		return -1;
	}
	fo = fopen(OUTPUT_FILE, "w+");
	if (fo == NULL) {
		perror("Output file not created.\n The process has been killed with the following status");
		return -1;
	}
	sendToCompute(fp, client, fo);
	fclose(fp);
	fclose(fo);
	return 0;
}
