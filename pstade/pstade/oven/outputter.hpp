#ifndef PSTADE_OVEN_OUTPUTTER_HPP
#define PSTADE_OVEN_OUTPUTTER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/result_of.hpp>
#include "./applier.hpp"
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./read.hpp"
#include "./single.hpp"


namespace pstade { namespace oven {


namespace outputter_detail {


    template< class Iterator, class UnaryFun >
    struct proc
    {
        Iterator m_it;
        UnaryFun m_fun;

        typedef Iterator base_type;

        Iterator base() const
        {
            return m_it;
        }

        typedef void result_type;

        template< class Value >
        void operator()(Value& v)
        {
            *m_it++ = read( boost::begin( m_fun(single(v)) ) );
        }
    };


    template< class Iterator, class UnaryFun >
    struct base
    {
        typedef
            proc<
                typename pass_by_value<Iterator>::type,
                typename pass_by_value<UnaryFun>::type
            >
        proc_t;

        typedef typename
            result_of<op_applier(proc_t&)>::type
        result_type;

        result_type operator()(Iterator& it, UnaryFun& fun) const
        {
            PSTADE_CONCEPT_ASSERT((Output<Iterator>));
            proc_t p = {it, fun};
            return applier(p);
        }
    };


} // namespace outputter_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(outputter, (outputter_detail::base<_, _>))


} } // namespace pstade::oven


#endif
