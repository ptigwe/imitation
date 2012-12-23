#include <glib.h>
#include <gmp.h>

#ifndef RANDOM_H
#define RANDOM_H

void random_set_seed(unsigned int seed);
gboolean random_boolean_with_probability(mpq_t p);
gint random_integer_with_probability(mpq_t *p, int n);

#endif