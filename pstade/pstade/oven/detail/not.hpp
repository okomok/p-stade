#ifndef PSTADE_OVEN_DETAIL_NOT_HPP
#define PSTADE_OVEN_DETAIL_NOT_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Predicate >
struct baby_not
{
    explicit baby_not(Predicate const& pred) :
        m_pred(pred)
    { }

    template< class Unused, class T0, class T1 = void >
    struct result
    {
        typedef bool type;
    };

    template< class Result, class T0 >
    Result call(T0& a0)
    {
        return !m_pred(a0);
    }

    template< class Result, class T0, class T1 >
    Result call(T0& a0, T1& a1)
    {
        return !m_pred(a0, a1);
    }

private:
    Predicate m_pred;
};


template< class Predicate >
struct not_fun
{
    typedef egg::function<
        baby_not<Predicate>
    > type;
};


template< class Predicate > inline
typename not_fun<Predicate>::type
not_(Predicate pred)
{
    typedef typename not_fun<Predicate>::type fun_t;
    return fun_t(
        baby_not<Predicate>(pred)
    );
}


} } } // namespace pstade::oven::detail


#endif
