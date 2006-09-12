#ifndef PSTADE_OVEN_TO_COUNTER_HPP
#define PSTADE_OVEN_TO_COUNTER_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/instance.hpp>
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


template< class Incrementable > inline
Incrementable const
counter_base(function_output_iterator< increment_fun<Incrementable> > const& it)
{
    return it.function().incrementable();
}


// Note:
//
// Assume 'FunOutIter' is not the iterator but
// a 'egg::baby_auto' object which is returned by 'oven::to_base'.
// In such case, 'Incrementable' of
// 'operator|(function_output_iterator< increment_fun<Incrementable> >, to_counter_base)'
// is not deducable.
// That's why we must use 'egg::baby_auto' again.
//

struct counter_base_class
{
    template< class Incrementable, class FunOutIter >
    static Incrementable call(FunOutIter const& it)
    {
        return oven::counter_base<Incrementable>(it);
    }
};


PSTADE_EGG_PIPABLE(to_counter_base, egg::baby_auto<counter_base_class>)


} } // namespace pstade::oven


#endif
