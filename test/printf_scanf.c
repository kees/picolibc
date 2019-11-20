/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright © 2019 Keith Packard
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <sys/stat.h>

extern double strtod(char *, char **);

static const double test_vals[] = { 1.234567, 1.1, M_PI };

int
main(int argc, char **argv)
{
	int x = -35;
	char	buf[256];
	int	errors = 0;
#if 0
	double	a;

	printf ("hello world\n");
	for (x = 1; x < 20; x++) {
		printf("%.*f\n", x, 9.99999999999);
	}

	for (a = 1e-10; a < 1e10; a *= 10.0) {
		printf("g format: %10.3g %10.3g\n", 1.2345678 * a, 1.1 * a);
		fflush(stdout);
	}
	for (a = 1e-10; a < 1e10; a *= 10.0) {
		printf("f format: %10.3f %10.3f\n", 1.2345678 * a, 1.1 * a);
		fflush(stdout);
	}
	for (a = 1e-10; a < 1e10; a *= 10.0) {
		printf("e format: %10.3e %10.3e\n", 1.2345678 * a, 1.1 * a);
		fflush(stdout);
	}
	printf ("%g\n", exp(11));
#endif
	for (x = 0; x < 32; x++) {
		uint32_t v = 0x12345678ul >> x;
		uint32_t r;

		sprintf(buf, "%u", v);
		sscanf(buf, "%u", &r);
		if (v != r) {
			printf("\t%3d: wanted %u got %u\n", x, v, r);
			errors++;
			fflush(stdout);
		}
		sprintf(buf, "%x", v);
		sscanf(buf, "%x", &r);
		if (v != r) {
			printf("\t%3d: wanted %u got %u\n", x, v, r);
			errors++;
			fflush(stdout);
		}
		sprintf(buf, "%o", v);
		sscanf(buf, "%o", &r);
		if (v != r) {
			printf("\t%3d: wanted %u got %u\n", x, v, r);
			errors++;
			fflush(stdout);
		}
	}

	for (x = -37; x <= 37; x++)
	{
		int t;
		for (t = 0; t < sizeof(test_vals)/sizeof(test_vals[0]); t++) {
			double v = test_vals[t] * pow(10.0, (double) x);
			double r;
			double e;

			sprintf(buf, "%.45f", v);
			sscanf(buf, "%lf", &r);
			e = fabs(v-r) / v;
			if (e > 1e-6) {
				printf("\t%3d: wanted %.7e got %.7e (error %.7e\n", x, v, r, e);
				errors++;
				fflush(stdout);
			}


			sprintf(buf, "%.14e", v);
			sscanf(buf, "%lf", &r);
			e = fabs(v-r) / v;
			if (e > 1e-6) {
				printf("\t%3d: wanted %.7e got %.7e (error %.7e, buf %s)\n", x, v, r, e, buf);
				errors++;
				fflush(stdout);
			}


			sprintf(buf, "%.7g", v);
			sscanf(buf, "%lf", &r);
			e = fabs(v-r) / v;
			if (e > 1e-6) {
				printf("\t%3d: wanted %.7e got %.7e (error %.7e, buf %s)\n", x, v, r, e, buf);
				errors++;
				fflush(stdout);
			}
		}
	}
	if (!errors)
		printf("success\n");
	fflush(stdout);
	return errors;
}