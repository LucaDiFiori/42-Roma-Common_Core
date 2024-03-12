#include "push_swap.h"

static void    max_a(t_stack *stk)
{
    int i;
    int max;

    i = -1;
    stk->mm.max_idx_a = 0;
    max = stk->stk_a[0];
    while (++i < stk->len_a)
    {
        if (max < stk->stk_a[i])
        {
            max = stk->stk_a[i];
            stk->mm.max_idx_a = i;
        }
    }
}

static void    min_a(t_stack *stk)
{
    int i;
    int min;

    i = -1;
    stk->mm.min_idx_a = 0;
    min = stk->stk_a[0];
    while (++i < stk->len_a)
    {
        if (min > stk->stk_a[i])
        {
            min = stk->stk_a[i];
            stk->mm.min_idx_a = i;
        }
    }
}

static void    max_b(t_stack *stk)
{
    int i;
    int max;

    i = -1;
    stk->mm.max_idx_b = 0;
    max = stk->stk_b[0];
    while (++i < stk->len_b)
    {
        if (max < stk->stk_b[i])
        {
            max = stk->stk_b[i];
            stk->mm.max_idx_b = i;
        }
    }
}

static void    min_b(t_stack *stk)
{
    int i;
    int min;

    i = -1;
    stk->mm.min_idx_b = 0;
    min = stk->stk_b[0];
    while (++i < stk->len_b)
    {
        if (min > stk->stk_b[i])
        {
            min = stk->stk_b[i];
            stk->mm.min_idx_b = i;
        }
    }
}

/*Restituisce gli indici dei valori massimi e minimi delle stack*/
void    get_max_min(t_stack *stk)
{
    max_a(stk);
    max_b(stk);
    min_a(stk);
    min_b(stk);
}