#ifndef PSTADE_SAUSAGE_DETAIL_YIELD_FORWARD_HPP
#define PSTADE_SAUSAGE_DETAIL_YIELD_FORWARD_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Workaround:
//
// Boost.Lambda functors cannot take non-const rvalues.


namespace pstade { namespace sausage { namespace detail {


template< class Functor >
struct yield_forward_fun
{
    explicit yield_forward_fun(Functor fun) :
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
yield_forward_fun<Functor> const
make_yield_forward(Functor fun)
{
    return yield_forward_fun<Functor>(fun);
}


} } } // namespace pstade::sausage::detail


#endif
