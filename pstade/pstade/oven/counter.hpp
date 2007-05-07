#ifndef PSTADE_OVEN_COUNTER_HPP
#define PSTADE_OVEN_COUNTER_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include "./passer.hpp"


namespace pstade { namespace oven {


namespace counter_detail  {


    template< class Incrementable >
    struct increment
    {
        typedef void result_type;

        template< class Value >
        void operator()(Value const&)
        {
            ++m_i;
        }

        explicit increment(Incrementable i) :
            m_i(i)
        { }

        // as "adaptor"; 'adapted_to' kicks in!
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
        inc_t;

        typedef typename
            boost::result_of<
                op_passer(increment<inc_t>)
            >::type
        result_type;

        result_type operator()(Incrementable& i) const
        {
            return passer(increment<inc_t>(i));
        }
    };


} // namespace counter_detail


PSTADE_FUNCTION(counter, (counter_detail::baby<_>))


} } // namespace pstade::oven


#endif
