#ifndef PSTADE_OVEN_TO_COUNTER_HPP
#define PSTADE_OVEN_TO_COUNTER_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include "./to_function.hpp"


namespace pstade { namespace oven {


namespace to_counter_detail  {


    template< class Incrementable >
    struct op_inc
    {
        typedef void result_type;

        explicit op_inc(Incrementable i) :
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

        // as "adaptor"; 'oven::adapted_to' kicks in!
        Incrementable base() const
        {
            return m_i;
        }

    private:
        Incrementable m_i;
    };


    template< class Incrementable >
    struct baby
    {
        typedef typename
            pass_by_value<Incrementable>::type
        i_t;

        typedef typename
            boost::result_of<
                op_to_function(op_inc<i_t>)
            >::type
        result_type;

        result_type operator()(Incrementable& i) const
        {
            return to_function(op_inc<i_t>(i));
        }
    };


} // namespace to_counter_detail


PSTADE_FUNCTION(to_counter, (to_counter_detail::baby<_>))


} } // namespace pstade::oven


#endif
