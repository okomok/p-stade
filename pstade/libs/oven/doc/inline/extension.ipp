namespace Foo {

    template< class T >
    struct Pair
    {
        T first, last;
    };

} // namespace Foo

namespace pstade_oven_extension {

    template< class T >
    struct range< Foo::Pair<T> >
    {
        // X == Foo::Pair<T>
        template< class X >
        struct meta
        {
            typedef T mutable_iterator;
            typedef T constant_iterator;
        };

        // if X is not const, Iterator == mutable_iterator;
        // otherwise, Iterator == constant_iterator.
        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.first;
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return x.last;
        }
    };

} // namespace pstade_oven_extension

PSTADE_OVEN_EXTENSION_TEMPLATE((Foo)(Pair), (class))
// PSTADE_OVEN_EXTENSION_TEMPLATE((Foo)(Pair), 1) // also ok.