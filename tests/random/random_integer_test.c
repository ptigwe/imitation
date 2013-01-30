#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/random.h"

#define IN_RANGE(x, y, z) ((x >= y) && (x <= z))
#define IN_RANGE_WITH_ERROR(x, y, z) ((x >= (y - (y * z))) && (x <= (y + (y * z))))
#define THRESHOLD 0.2
#define N 100000
#define NUM 50

static void random_integer_test(int i)
{
    i -= 1;
    mpq_t *p = (mpq_t *)g_malloc(NUM * sizeof(mpq_t));
    int *c = (int *)g_malloc(NUM * sizeof(int));
    int *expt_res = (int *)g_malloc(NUM * sizeof(int));
        
    int j;
    for(j = 0; j < NUM; ++j)
    {
        mpq_init(p[j]);
        c[j] = 0;
        
        if(i == j)
        {
            mpq_set_ui(p[i], 1, 2);
            expt_res[i] = N / 2;
        }
        else
        {
            mpq_set_ui(p[j], 1, (NUM - 1) * 2);
            expt_res[j] = N / ((NUM - 1) * 2);
        }
        mpq_canonicalize(p[j]);
    }
    
    for(j = 0; j < N; ++j)
    {
        int x = random_integer_with_probability(p, NUM);
        ++c[x];
    }
    
    for(j = 0; j < NUM; ++j)
    {
        g_printf("%d : %d\n", j, c[j]);
        g_assert(IN_RANGE_WITH_ERROR(c[j], expt_res[j], THRESHOLD));
    }
    
    for(j = 0; j < NUM; ++j)
    {
        mpq_clear(p[j]);
    }
    g_free(p);
    g_free(c);
    g_free(expt_res);
}

static void random_integer_test_0()
{
    random_integer_test(1);
}

static void random_integer_test_1()
{
    random_integer_test(5);
}

static void random_integer_test_2()
{
    random_integer_test(10);
}

static void random_integer_test_3()
{
    random_integer_test(15);
}

static void random_integer_test_4()
{
    random_integer_test(20);
}

static void random_integer_test_5()
{
    random_integer_test(25);
}

static void random_integer_test_6()
{
    random_integer_test(30);
}

static void random_integer_test_7()
{
    random_integer_test(35);
}

static void random_integer_test_8()
{
    random_integer_test(40);
}

static void random_integer_test_9()
{
    random_integer_test(45);
}

static void random_integer_test_10()
{
    random_integer_test(50);
}

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/Random Boolean Test 1 (p = 0/10)", random_integer_test_0);
    g_test_add_func("/Random Boolean Test 2 (p = 1/10)", random_integer_test_1);
    g_test_add_func("/Random Boolean Test 3 (p = 2/10)", random_integer_test_2);
    g_test_add_func("/Random Boolean Test 4 (p = 3/10)", random_integer_test_3);
    g_test_add_func("/Random Boolean Test 5 (p = 4/10)", random_integer_test_4);
    g_test_add_func("/Random Boolean Test 6 (p = 5/10)", random_integer_test_5);
    g_test_add_func("/Random Boolean Test 7 (p = 6/10)", random_integer_test_6);
    g_test_add_func("/Random Boolean Test 8 (p = 7/10)", random_integer_test_7);
    g_test_add_func("/Random Boolean Test 9 (p = 8/10)", random_integer_test_8);
    g_test_add_func("/Random Boolean Test 10 (p = 9/10)", random_integer_test_9);
    g_test_add_func("/Random Boolean Test 11 (p = 10/10)", random_integer_test_10);
    return g_test_run();
}