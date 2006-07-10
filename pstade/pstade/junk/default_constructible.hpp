#ifndef PSTADE_OVEN_DETAIL_DEFAULT_CONSTRUCTIBLE_HPP
#define PSTADE_OVEN_DETAIL_DEFAULT_CONSTRUCTIBLE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// In fact, this workaround is rather dangerous,
// so rejected.


#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>


namespace pstade { namespace oven { namespace detail {


namespace default_constructible_detail {


    template< class Functor >
    struct baby
    {
        explicit baby()
        { }

        explicit baby(Functor fun) :
            m_fun(fun)
        { }

        // 2ary
        template< class Unused, class A0 = void, class A1 = void >
        struct result :
            boost::result_of<Functor(A0, A1)>
        { };

        template< class Result, class A0, class A1 >
        Result call(A0& a0, A1& a1)
        {
            return (*m_fun)(a0, a1);
        }

        // 1ary
        template< class Unused, class A0 >
        struct result<Unused, A0> :
            boost::result_of<Functor(A0)>
        { };

        template< class Result, class A0 >
        Result call(A0& a0)
        {
            return (*m_fun)(a0);
        }

        // 0ary
        template< class Unused >
        struct result<Unused> :
            boost::result_of<Functor()>
        { };

        template< class Result >
        Result call()
        {
            return (*m_fun)();
        }

    private:
        boost::optional<Functor> m_fun;
    };


    template< class Functor >
    struct super_
    {
        typedef egg::function<
            baby<Functor>
        > type;
    };


} // namespace default_constructible_detail


template< class Functor >
struct default_constructible_fun :
    default_constructible_detail::super_<Functor>::type
{
private:
    typedef typename default_constructible_detail::super_<Functor>::type super_t;

public:
    explicit default_constructible_fun(Functor fun) :
        super_t(default_constructible_detail::baby<Functor>(fun))
    { }
}; 


template< class Functor >
default_constructible_fun<Functor> const
default_constructible(Functor fun)
{
    return default_constructible_fun<Functor>(fun);
}


} } } // namespace pstade::oven::detail


#endif
