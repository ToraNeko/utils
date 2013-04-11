#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

struct translation {
	int16_t  n;
	char    *s;
};

const struct translation tab1[] = { /* long version : all additive */
	{    1, "I"       },
	{    5,  "V"      },
	{   10,   "X"     },
	{   50,    "L"    },
	{  100,     "C"   },
	{  500,      "D"  },
	{ 1000,       "M" }
};

const struct translation tab2[] = { /* usual version */
	{    1, "I"       },
	{    4, "IV"      },
	{    5,  "V"      },
	{    9,  "IX"     },
	{   10,   "X"     },
	{   40,   "XL"    },
	{   50,    "L"    },
	{   90,    "XC"   },
	{  100,     "C"   },
	{  400,     "CD"  },
	{  500,      "D"  },
	{  900,      "CM" },
	{ 1000,       "M" }
};

const struct translation tab3[] = { /* shortest possible version */
	{    1, "I"       },
	{    4, "IV"      },
	{    5,  "V"      },
	{    9,  "IX"     },
	{   10,   "X"     },
	{   40,   "XL"    },
	{   45,   "VL"    },
	{   49,   "IL"    },
	{   50,    "L"    },
	{   90,    "XC"   },
	{   95,    "VC"   },
	{   99,    "IC"   },
	{  100,     "C"   },
	{  400,     "CD"  },
	{  450,     "LD"  },
	{  490,     "XD"  },
	{  495,     "VD"  },
	{  499,     "ID"  },
	{  500,      "D"  },
	{  900,      "CM" },
	{  950,      "LM" },
	{  990,      "XM" },
	{  995,      "VM" },
	{  999,      "IM" },
	{ 1000,       "M" }
};

void process(const char *p, const struct translation *t, const int size);

int
main(int argc, const char * argv[])
{
	const char **p = argv;

	(void) argc;

	if      (   !strcmp(argv[1], "-l"     )
	         || !strcmp(argv[1], "--long" )) {
		++p;
		while ((*++p)) {
			process(*p, tab1, sizeof(tab1) / sizeof(tab1[0]));
		}
	}
	else if (   !strcmp(argv[1], "-s"     )
	         || !strcmp(argv[1], "--short")) {
		++p;
		while ((*++p)) {
			process(*p, tab3, sizeof(tab3) / sizeof(tab3[0]));
		}
	}
	else {
		while ((*++p)) {
			process(*p, tab2, sizeof(tab2) / sizeof(tab2[0]));
		}
	}

	return 0;
}

void
process(const char *p, const struct translation *t, const int size)
{
	unsigned long long n = strtoull(p, NULL, 0);
//	printf("\"%s\" -> %llu\n", p, n);

	if (n) { // Arabic -> Roman
		for (int i = size - 1 ; i >= 0 ; --i) {
			while (n >= (unsigned long long) t[i].n) {
				n -= t[i].n;
				printf("%s", t[i].s);
			}
		}

		puts("");
	}
	else {   // Roman -> Arabic
		int j = 0;
		int i;

		while (*p) {
			switch (*p) {
				case 'I' : i =    1; break;
				case 'V' : i =    5; break;
				case 'X' : i =   10; break;
				case 'L' : i =   50; break;
				case 'C' : i =  100; break;
				case 'D' : i =  500; break;
				case 'M' : i = 1000; break;

				default  : return;
			}

			if (i > j) n -= j << 1;

			n += i;
			j  = i;

			++p;
		}

		printf("%llu\n", n);
	}

	return;
}
