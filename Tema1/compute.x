
struct output {
	char *answer;
	long value1;
	long value2;
};

struct input {
	long value;
};

program COMPUTE_PROG {
	version COMPUTE_VERS {
		output GET_COMPUTE(input) = 2;
	} = 1;
} = 0x1234;
