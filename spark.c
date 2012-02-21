#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* limit input numbers */
#define MAX_INPUT 1024

int parse_input(char *input,
                double values[],
                double *min_value,
                double *max_value,
                size_t n,
                int offset);

void print_sparkline(double values[],
                     double min_value,
                     double max_value,
                     int n);

static const char *blocks[8] = {"▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"};

int main(int argc, char *argv[])
{
    int n_elements = 0;
    double elements[MAX_INPUT];
    double min_element = HUGE_VAL;
    double max_element = -HUGE_VAL;

    if (argc < 2)
        /* TODO: print help message */
        return -1;

    int i;
    for (i = 1; i < argc; ++i) {
        n_elements += parse_input(argv[i],
                                 elements,
                                 &min_element,
                                 &max_element,
                                 MAX_INPUT - n_elements,
                                 n_elements);
        if (n_elements >= MAX_INPUT) break;
    }

    print_sparkline(elements, min_element, max_element, n_elements);

    /* TODO: return appropriate values */
    return 0;
}

void print_sparkline(double values[],
                     double min_value,
                     double max_value,
                     int n)
{
    assert(min_value <= max_value);
    double scaling_factor = max_value - min_value;
    /* Avoid division by zero if all elements have the same value */
    scaling_factor = scaling_factor != 0 ? scaling_factor : 1;
    int j;
    for (j = 0; j < n; ++j) {
        printf("%s",
               blocks[(int)(7 * (values[j] - min_value) / scaling_factor)]);
    }
    putchar('\n');
}

int parse_input(char *input,
                double values[],
                double *min_value,
                double *max_value,
                size_t n,
                int offset)
{
    char* process_from = input;
    char* to_be_processed = input;
    int n_elements = 0;
    double local_min = *min_value;
    double local_max = *max_value;

    while (*process_from != '\0') {
        /* array full; get out of here */
        if (n_elements == n) break;

        double value = strtod(process_from, &to_be_processed);
        /* strtod did not recognise a number */
        if (process_from == to_be_processed) {
            ++process_from;
            ++to_be_processed;
        /* strtod did recognise a number */
        } else {
            /* avoid overflow and underflow */
            if (errno != ERANGE) {
                values[offset + n_elements++] = value;
                if (value < local_min) local_min = value;
                if (value > local_max) local_max = value;
            }

            /* to_be_processed was shifted to point to the character
             * following the last on of the number. Shift process_from to
             * point to the same character */
            process_from = to_be_processed;
        }
        /* reset errno so more numbers can be added */
        errno = 0;
    }

    *min_value = local_min;
    *max_value = local_max;
    return n_elements;
}
