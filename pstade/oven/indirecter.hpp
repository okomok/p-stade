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
#include "./detail/base_to_adaptor.hpp"


namespace pstade { namespace oven {


namespace indirecter_detail {


    template< class OutIter >
    struct proc
    {
        OutIter m_it;

        typedef OutIter base_type;

        OutIter base() const
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


    template< class OutIter >
    struct base
    {
        typedef
            proc<
                typename pass_by_value<OutIter>::type
            >
        proc_t;

        typedef typename
            result_of<op_make_applier(proc_t&)>::type
        result_type;

        result_type operator()(OutIter& it) const
        {
            proc_t p = {it};
            return make_applier(p);
        }
    };


} // namespace indirecter_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(indirecter, (indirecter_detail::base<_>))


} } // namespace pstade::oven


#endif
