#ifndef PSTADE_OVEN_TO_COUNTER_HPP
#define PSTADE_OVEN_TO_COUNTER_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include "./to_function.hpp"


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


template< class Incrementable >
struct baby_to_counter
{
    typedef typename
        boost::result_of<op_to_function(
            op_increment<typename pass_by_value<Incrementable>::type>
        )>::type
    result;

    result call(Incrementable& i)
    {
        return result(typename result::function_type(i));
    }
};

PSTADE_FUNCTION(to_counter, (baby_to_counter<_>))


} } // namespace pstade::oven


#endif
