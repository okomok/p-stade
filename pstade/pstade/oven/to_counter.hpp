#ifndef PSTADE_OVEN_TO_COUNTER_HPP
#define PSTADE_OVEN_TO_COUNTER_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./function_output_iterator.hpp"


namespace pstade { namespace oven {


template< class Incrementable >
struct increment_fun
{
    typedef void result_type;

    explicit increment_fun(Incrementable const& i) :
        m_i(i)
    { }

    template< class Value >
    void operator()(Value const&)
    {
        ++m_i;
    }

// as "adaptor", 'oven::to_base' can kick in!
    typedef Incrementable base_type;

    Incrementable const& base() const
    {
        return m_i;
    }

private:
    Incrementable m_i;
};


template< class Incrementable > inline
function_output_iterator< increment_fun<Incrementable> > const
to_counter(Incrementable const& i)
{
    return oven::to_function(increment_fun<Incrementable>(i));
}


template< class Incrementable > inline
Incrementable const
counter_base(function_output_iterator< increment_fun<Incrementable> > const& it)
{
    return it.base().base();
}


} } // namespace pstade::oven


#endif
