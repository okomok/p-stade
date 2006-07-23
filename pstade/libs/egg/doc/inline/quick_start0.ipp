struct baby_multiply
{
    template< class Unused, class X, class Y >
    struct result :
        boost::remove_const<X>
    { };


    template< class Result, class X, class Y >
    Result call(X& x, Y& y)
    {
        return x * y;
    }
};