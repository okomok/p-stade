#ifndef PSTADE_OVEN_DETAIL_NOT_HPP
#define PSTADE_OVEN_DETAIL_NOT_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Predicate >
struct baby_not_fun
{
    explicit baby_not_fun(Predicate pred) :
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


struct baby_not
{
    template< class Unused, class Predicate >
    struct result
    {
        typedef typename egg::by_value<Predicate>::type pred_t;
        typedef egg::function< baby_not_fun<pred_t> > type;
    };

    template< class Result, class Predicate >
    Result call(Predicate& pred)
    {
        return Result(pred);
    }
};


PSTADE_EGG_FUNCTION_(not_, baby_not)


} } } // namespace pstade::oven::detail


#endif
