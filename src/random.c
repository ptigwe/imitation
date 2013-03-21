#include "random.h"


void random_set_seed(unsigned int seed)
{
    g_random_set_seed(seed);
}

void lcm(mpz_t l, mpz_t *num, gint n)
{
    mpz_t tmp;
    mpz_init(tmp);
    mpz_set_si(tmp, 1);
    
    mpz_lcm(l, num[0], tmp);
    
    gint i;
    for(i = 1; i < n; ++i)
    {
        mpz_set(tmp, l);
        mpz_lcm(l, tmp, num[i]);
    }
    
    mpz_clear(tmp);
}

gboolean random_boolean_with_probability(mpq_t p)
{
    int i = g_random_int_range(0, mpz_get_si(mpq_denref(p)));
    if(i < mpz_get_si(mpq_numref(p)))
    {
        return TRUE;
    }
    return FALSE;
}

gint random_integer_with_probability(mpq_t *p, gint n)
{
    mpz_t *den;
    den = (mpz_t *)g_malloc(sizeof(mpz_t) * n);
    int i;
    for(i = 0; i < n; ++i)
    {
        mpz_init(den[i]);
        mpq_get_den(den[i], p[i]);
    }
    
    mpz_t l;
    mpz_init(l);
    lcm(l, den, n);
    
    mpq_t nlcm;
    mpq_init(nlcm);
    mpq_set_z(nlcm, l);
    
    int lc =  mpz_get_ui(l);
    gint x = g_random_int_range(0, lc);
    mpq_t y;
    mpq_init(y);
    mpq_set_si(y, x, 1);
    
    mpq_t p_i;
    mpq_init(p_i);
    
    int j = n - 1;
    
    for(i = 0; i < n - 1; i++)
    {
        mpq_mul(p_i, nlcm, p[i]);
        
        if(mpq_cmp(y, p_i) < 0)
        {
            j = i;
            break;
        }
        
        mpq_sub(y, y, p_i);
    }
    
    for(i = 0; i < n; ++i)
    {
        mpz_clear(den[i]);
    }
    g_free(den);
    
    mpz_clear(l);
    mpq_clear(nlcm);
    mpq_clear(y);
    mpq_clear(p_i);
    
    return j;
}

gint random_integer(int n)
{
    return g_random_int_range(0, n);
}
