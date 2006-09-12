#ifndef PSTADE_OVEN_TO_COUNTER_HPP
#define PSTADE_OVEN_TO_COUNTER_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./function_output_iterator.hpp"


namespace pstade { namespace oven {


template< class Incrementable >
struct increment_fun
{
    typedef Incrementable incrementable_type;
    typedef void result_type;

    explicit increment_fun(Incrementable const& i) :
        m_i(i)
    { }

    template< class Value >
    void operator()(Value const&)
    {
        ++m_i;
    }

    Incrementable incrementable() const
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


struct baby_counter_base
{
    template< class Unused, class FunOutIter >
    struct result
    {
        typedef typename FunOutIter::function_type::incrementable_type const type;
    };

    template< class Result, class FunOutIter >
    Result call(FunOutIter const& it)
    {
        return it.function().incrementable();
    }
};


PSTADE_EGG_FUNCTION(counter_base, baby_counter_base)
PSTADE_EGG_PIPABLE(to_counter_base, baby_counter_base)


} } // namespace pstade::oven


#endif
