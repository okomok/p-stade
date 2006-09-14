#ifndef PSTADE_OVEN_TO_COUNTER_HPP
#define PSTADE_OVEN_TO_COUNTER_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function.hpp>
#include "./function_output_iterator.hpp"


namespace pstade { namespace oven {


namespace to_counter_detail {


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

        Incrementable const& incrementable() const
        {
            return m_i;
        }

    // as "adaptor", 'oven::adaptor_to' kicks in!
        Incrementable const& base() const
        {
            return m_i;
        }

    private:
        Incrementable m_i;
    };


    struct baby
    {
        template< class Unused, class Incrementable >
        struct result
        {
            typedef typename egg::by_value<Incrementable>::type inc_t;
            typedef function_output_iterator< increment_fun<inc_t> > const type;
        };

        template< class Result, class Incrementable >
        Result call(Incrementable const& i)
        {
            return Result(increment_fun<Incrementable>(i));
        }
    };


} // namespace to_counter_detail


PSTADE_EGG_FUNCTION(to_counter, to_counter_detail::baby)


} } // namespace pstade::oven


#endif
