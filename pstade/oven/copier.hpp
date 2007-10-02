#ifndef PSTADE_OVEN_COPIER_HPP
#define PSTADE_OVEN_COPIER_HPP
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


namespace copier_detail {


    template< class OutIter, class PreOutIter >
    struct proc
    {
        OutIter m_it;
        PreOutIter m_pre;

        typedef OutIter base_type;

        OutIter base() const
        {
            return m_it;
        }

        typedef void result_type;

        template< class Value >
        void operator()(Value& v)
        {
            *m_pre++ = v;
            *m_it++ = v;
        }
    };


    template< class OutIter, class PreOutIter >
    struct base
    {
        typedef
            proc<
                typename pass_by_value<OutIter>::type,
                typename pass_by_value<PreOutIter>::type
            >
        proc_t;

        typedef typename
            result_of<op_applier(proc_t&)>::type
        result_type;

        result_type operator()(OutIter& it, PreOutIter& pre) const
        {
            proc_t p = {it, pre};
            return applier(p);
        }
    };


} // namespace copier_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(copier, (copier_detail::base<_, _>))


} } // namespace pstade::oven


#endif
