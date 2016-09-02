#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void polydiv_loop(int base, mpz_t value, int *digits, int step) {
	int i;
	mpz_t base_loop_value, loop_value;

	if (step == base) {
		if (base > 62) {
			printf("* %s\n", mpz_get_str(NULL, 10, value));
		} else {
			printf("%s %s\n", mpz_get_str(NULL, base, value),
					mpz_get_str(NULL, 10, value));
		}
	}

	mpz_init_set(base_loop_value, value);
	mpz_mul_ui(base_loop_value, base_loop_value, base);
	mpz_init(loop_value);

	for(i=1; i<base; i++) {
		if(digits[i]) {
			mpz_add_ui(loop_value, base_loop_value, i);
			if(mpz_divisible_ui_p(loop_value, step)) {
				digits[i]=0;
				polydiv_loop(base, loop_value, digits, step+1);
				digits[i]=1;
			}
		}
	}
    mpz_clears(base_loop_value, loop_value, NULL);
}

void polydiv_start(int base) {
	int i;
	int *digits;
	mpz_t value;

	// Allocate digits list
	digits = malloc(sizeof(int) * base);
	for (i=0; i<base; i++) {
		digits[i] = 1;
	}

	// Create multi-precision int
	mpz_init(value);

	polydiv_loop(base, value, digits, 1);
}

int main(int argc, char *argv[]) {
	int base;

	if (argc != 2) {
		fprintf(stderr, "Requires base on command line.\n");
		exit(1);
	}

	sscanf(argv[1], "%d", &base);
	printf("Testing base %d...\n", base);

	polydiv_start(base);

	exit(0);
}
