struct my_routine
{
    typedef int routine_result_type;

    template< class Yield >
    int operator()(Yield yield)
    {
        int min = 0, max = 30;
        for (int i = min; i < max; ++i)
            yield(min++);

        return min;
    }
};