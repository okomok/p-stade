#ifndef PSTADE_OVEN_INDIRECTER_HPP
#define PSTADE_OVEN_INDIRECTER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pass_by.hpp>
#include <pstade/result_of.hpp>
#include "./applier.hpp"
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"


namespace pstade { namespace oven {


namespace indirecter_detail {


    template< class Iterator >
    struct proc
    {
        Iterator m_it;

        typedef Iterator base_type;

        Iterator base() const
        {
            return m_it;
        }

        typedef void result_type;

        template< class Value >
        void operator()(Value& v)
        {
            *m_it++ = *v;
        }
    };


    template< class Iterator >
    struct base
    {
        typedef
            proc<
                typename pass_by_value<Iterator>::type
            >
        proc_t;

        typedef typename
            result_of<op_applier(proc_t&)>::type
        result_type;

        result_type operator()(Iterator& it) const
        {
            PSTADE_CONCEPT_ASSERT((Output<Iterator>));
            proc_t p = {it};
            return applier(p);
        }
    };


} // namespace indirecter_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(indirecter, (indirecter_detail::base<_>))


} } // namespace pstade::oven


#endif
