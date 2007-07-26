#ifndef PSTADE_OVEN_DETAIL_YIELD_BREAK_EXCEPTION_HPP
#define PSTADE_OVEN_DETAIL_YIELD_BREAK_EXCEPTION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <exception>


namespace pstade { namespace oven { namespace detail {


struct yield_break_exception :
    std::exception
{
    char const *what() const throw()
    {
        return "yield_break_exception";
    }
};


template< class UnaryFun >
struct yield
{
    typedef void result_type;

    template< class A >
    void operator()(A& a) const
    {
        m_fun(a);
    }

    template< class A >
    void operator()(A const& a) const
    {
        m_fun(a);
    }

    template< class A >
    void return_(A& a) const
    {
        (*this)(a);
    }

    template< class A >
    void return_(A const& a) const
    {
        (*this)(a);
    }

    void break_() const
    {
        throw yield_break_exception();
    }

    explicit yield(UnaryFun fun) :
        m_fun(fun)
    { }

private:
    UnaryFun m_fun;
};


template< class UnaryFun> inline
yield<UnaryFun> make_yield(UnaryFun fun)
{
    return yield<UnaryFun>(fun);
}


} } } // namespace pstade::oven::detail


#endif
