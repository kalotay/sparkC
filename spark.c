#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* limit input numbers */
#define MAX_INPUT 1024

int main(int argc, char* argv[])
{
    int n_elements = 0;
    double elements[MAX_INPUT];
    double min_element = HUGE_VAL;
    double max_element = -HUGE_VAL;

    if (argc < 2)
        return -1;

    int i;
    for (i = 1; i < argc; ++i) {
        char* process_from = argv[i];
        char* to_be_processed = argv[i];

        while (*process_from != '\0') {
            double value = strtod(process_from, &to_be_processed);
            int err_strtod = errno;
            /* strtod did not recognise a number */
            if (process_from == to_be_processed) {
                ++process_from;
                ++to_be_processed;
            /* strtod did recognise a number */
            } else {
                /* avoid overflow and underflow */
                if (err_strtod != ERANGE) {
                    elements[n_elements++] = value;
                    min_element = value < min_element ? value : min_element;
                    max_element = value > max_element ? value : max_element;

                    /* array full; get out of here */
                    if (n_elements == MAX_INPUT)
                        goto cleanup;
                }

                /* to_be_processed was shifted to point to the character
                 * following the last on of the number. Shift process_from to
                 * point to the same character */
                process_from = to_be_processed;
            }
        }
    }

cleanup:
    /* assert used to shut up compiler. labels cannot be at declerations */
    assert(min_element <= max_element);
    double scaling_factor = max_element - min_element;
    /* Avoid division by zero if all elements have the same value */
    scaling_factor = scaling_factor != 0 ? scaling_factor : 1;
    int j;
    for (j = 0; j < n_elements; ++j) {
        /* TODO: use appropriate block elements from unicode */
        putchar(48 + (int)(7 * (elements[j] - min_element) / scaling_factor));
    }
    putchar('\n');

    return 0;
}

