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
struct op_increment
{
    typedef void result_type;

    explicit op_increment(Incrementable const& i) :
        m_i(i)
    { }

    template< class Value >
    void operator()(Value const&)
    {
        ++m_i;
    }

    Incrementable const& incrementable() const
    {
        return m_i;
    }

// as "adaptor", 'oven::adapted_to' kicks in!
    Incrementable const& base() const
    {
        return m_i;
    }

private:
    Incrementable m_i;
};


template< class Incrementable > inline
function_output_iterator< op_increment<Incrementable> > const
to_counter(Incrementable const& i)
{
    return oven::to_function(op_increment<Incrementable>(i));
}


} } // namespace pstade::oven


#endif
