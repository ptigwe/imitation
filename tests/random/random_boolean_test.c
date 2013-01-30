#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/random.h"

#define IN_RANGE(x, y, z) ((x >= y) && (x <= z))
#define IN_RANGE_WITH_ERROR(x, y, z) ((x >= (y - (y * z))) && (x <= (y + (y * z))))
#define THRESHOLD 0.15
#define N 10000

gint random_boolean_test_generate(mpq_t p, int n)
{
    int count = 0;
    int i;
    for(i = 0; i < 10000; ++i)
    {
        int b = random_boolean_with_probability(p);
        count += b;
    }
    
    return count;
}

static void random_boolean_test(int num, int den)
{
    mpq_t p;
    mpq_init(p);
    mpq_set_ui(p, num, den);
    
    gint res = random_boolean_test_generate(p, N);
    gint expt_res = (num * N) / den;
    
    mpq_clear(p);
    g_printf("%d ", res);
    
    g_assert(IN_RANGE_WITH_ERROR(res, expt_res, THRESHOLD));
}

static void random_boolean_test_0()
{
    random_boolean_test(0, 10);
}

static void random_boolean_test_1()
{
    random_boolean_test(1, 10);
}

static void random_boolean_test_2()
{
    random_boolean_test(2, 10);
}

static void random_boolean_test_3()
{
    random_boolean_test(3, 10);
}

static void random_boolean_test_4()
{
    random_boolean_test(4, 10);
}

static void random_boolean_test_5()
{
    random_boolean_test(5, 10);
}

static void random_boolean_test_6()
{
    random_boolean_test(6, 10);
}

static void random_boolean_test_7()
{
    random_boolean_test(7, 10);
}

static void random_boolean_test_8()
{
    random_boolean_test(8, 10);
}

static void random_boolean_test_9()
{
    random_boolean_test(9, 10);
}

static void random_boolean_test_10()
{
    random_boolean_test(10, 10);
}

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
    
    g_test_add_func("/Random Boolean Test 1 (p = 0/10)", random_boolean_test_0);
    g_test_add_func("/Random Boolean Test 2 (p = 1/10)", random_boolean_test_1);
    g_test_add_func("/Random Boolean Test 3 (p = 2/10)", random_boolean_test_2);
    g_test_add_func("/Random Boolean Test 4 (p = 3/10)", random_boolean_test_3);
    g_test_add_func("/Random Boolean Test 5 (p = 4/10)", random_boolean_test_4);
    g_test_add_func("/Random Boolean Test 6 (p = 5/10)", random_boolean_test_5);
    g_test_add_func("/Random Boolean Test 7 (p = 6/10)", random_boolean_test_6);
    g_test_add_func("/Random Boolean Test 8 (p = 7/10)", random_boolean_test_7);
    g_test_add_func("/Random Boolean Test 9 (p = 8/10)", random_boolean_test_8);
    g_test_add_func("/Random Boolean Test 10 (p = 9/10)", random_boolean_test_9);
    g_test_add_func("/Random Boolean Test 11 (p = 10/10)", random_boolean_test_10);
    
    return g_test_run();
}