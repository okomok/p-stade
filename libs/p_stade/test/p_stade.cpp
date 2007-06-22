#include <pstade/minimal_test.hpp>


namespace boost {
    
    template<class X, class J>
    struct equality_comparable : J
    {
        friend bool operator==(X, X) { return true; }
    };


    template<class X>
    void boost_range_begin(X)
    {
        X::non();
    }


}


template<class X>
void
boost_foreach_is_lightweight_proxy(X)
{
    X::non();
}



namespace pstade { namespace radish {

    template<class X>
    struct null_injector { };

} }


namespace pstade { namespace oven {

namespace iter_range_detail {
    struct null_injector { };
}


template<
    class Range,
    class Injector = radish::null_injector<Range>
>
struct lightweight_copyable :
    Injector
{
    friend
    void
    boost_foreach_is_lightweight_proxy(Range)
    { }
};

template<
    class T,
    class ConstantIter,
    class Injector = radish::null_injector<T>
>
struct range_constantable :
    Injector
{
    friend
    ConstantIter boost_range_begin(T)
    {
        return ConstantIter();
    }
};


template<
    class Iterator,
    class Injector = iter_range_detail::null_injector
>
struct iter_range :
    boost::equality_comparable< iter_range<Iterator, Injector>,
    lightweight_copyable      < iter_range<Iterator, Injector>,
    Injector > >
{
    iter_range() { }
};


template< class Value >
struct empty_range;


namespace empty_range_detail {


    template< class Value >
    struct super_
    {
        typedef
            iter_range<Value *,
                range_constantable  < empty_range<Value>, Value const *,
                lightweight_copyable< empty_range<Value> > >
            >
        type;
    };


} // namespace empty_range_detail


template< class Value >
struct empty_range :
    empty_range_detail::super_<Value>::type 
{ };

} }


void pstade_minimal_test()
{
    using namespace pstade::oven;
    empty_range<double> r;
    boost_range_begin(r);
    boost_foreach_is_lightweight_proxy(r);
}
