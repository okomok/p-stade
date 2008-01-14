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
#include "./concepts.hpp"
#include "./detail/adaptor_output_iterator.hpp"
#include "./detail/base_to_adaptor.hpp"


namespace pstade { namespace oven {


namespace copier_detail {


    template< class PreIterator >
    struct proc
    {
        PreIterator m_pre;

        typedef void result_type;

        template< class Iterator, class Value >
        void operator()(Iterator& it, Value& v)
        {
            *m_pre++ = v;
            *it++ = v;
        }
    };


    template< class Iterator, class PreIterator >
    struct base
    {
        typedef
            proc<typename pass_by_value<PreIterator>::type>
        proc_t;

        typedef
            detail::adaptor_output_iterator<
                typename pass_by_value<Iterator>::type,
                proc_t
            >
        result_type;

        result_type operator()(Iterator& it, PreIterator& pre) const
        {
            PSTADE_CONCEPT_ASSERT((Output<Iterator>));
            PSTADE_CONCEPT_ASSERT((Output<PreIterator>));
            proc_t p = {pre};
            return result_type(it, p);
        }
    };


} // namespace copier_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(copier, (copier_detail::base<_, _>))


} } // namespace pstade::oven


#endif
