#ifndef PSTADE_OVEN_DETAIL_NOT_HPP
#define PSTADE_OVEN_DETAIL_NOT_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace oven { namespace detail {


template< class Predicate >
struct not_fun
{
    typedef bool result_type;

    explicit not_fun(Predicate pred) :
        m_pred(pred)
    { }

    template< class T >
    bool operator()(T& x) const
    {
        return !m_pred(x);
    }

    template< class T >
    bool operator()(T const& x) const
    {
        return !m_pred(x);
    }

private:
    Predicate m_pred;
};


template< class Predicate > inline
not_fun<Predicate> not_(Predicate pred)
{
    return not_fun<Predicate>(pred);
}


} } } // namespace pstade::oven::detail


#endif
