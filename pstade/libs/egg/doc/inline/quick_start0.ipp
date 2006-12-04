struct baby_multiply
{
    template< class Myself, class X, class Y >
    struct apply :
        boost::remove_const<X>
    { };


    template< class Result, class X, class Y >
    Result call(X& x, Y& y) const
    {
        return x * y;
    }
};