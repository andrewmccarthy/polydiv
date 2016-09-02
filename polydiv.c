#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

mpz_t *loop_base, *values;

void polydiv_loop(int base, int *digits, int step) {
	int i;

	if (step == base) {
		if (base > 62) {
			printf("* %s\n", mpz_get_str(NULL, 10, values[step-1]));
		} else {
			printf("%s %s\n", mpz_get_str(NULL, base, values[step-1]),
					mpz_get_str(NULL, 10, values[step-1]));
		}
	}

	mpz_mul_ui(loop_base[step], values[step-1], base);

	for(i = step - mpz_fdiv_ui(loop_base[step], step); i<base; i+=step) {
		if(digits[i]) {
			mpz_add_ui(values[step], loop_base[step], i);
			if(mpz_divisible_ui_p(values[step], step)) {
				digits[i]=0;
				polydiv_loop(base, digits, step+1);
				digits[i]=1;
			}
		}
	}
}

void polydiv_start(int base) {
	int i;
	int *digits;

	// Allocate digits list
	digits = malloc(sizeof(int) * base);
	for (i=0; i<base; i++) {
		digits[i] = 1;
	}

	// Create multi-precision int
    values = malloc(sizeof(mpz_t) * (base + 1));
    loop_base = malloc(sizeof(mpz_t) * (base + 1));
	for (i=0; i<base; i++) {
        mpz_init(values[i]);
        mpz_init(loop_base[i]);
	}

	polydiv_loop(base, digits, 1);
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
