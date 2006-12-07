#ifndef PSTADE_SAUSAGE_DETAIL_FORWARD_YIELD_HPP
#define PSTADE_SAUSAGE_DETAIL_FORWARD_YIELD_HPP


// PStade.Sausage
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Workaround:
//
// Boost.Lambda functors cannot take non-const rvalues.


namespace pstade { namespace sausage { namespace detail {


template< class Functor >
struct op_forward_yield
{
    explicit op_forward_yield(Functor fun) :
        m_fun(fun)
    { };

    typedef void result_type;

    template< class T >
    void operator()(T& x) const
    {
        m_fun(x);
    }

    template< class T >
    void operator()(T const& x) const
    {
        m_fun(x);
    }

private:
    Functor m_fun;
};


template< class Functor > inline
op_forward_yield<Functor> const
make_forward_yield(Functor fun)
{
    return op_forward_yield<Functor>(fun);
}


} } } // namespace pstade::sausage::detail


#endif
