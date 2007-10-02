#ifndef PSTADE_OVEN_PERMUTER_HPP
#define PSTADE_OVEN_PERMUTER_HPP
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
#include "./range_iterator.hpp"
#include "./read.hpp"


namespace pstade { namespace oven {


namespace permuter_detail {


    template< class Iterator, class ElementIter >
    struct proc
    {
        Iterator m_it;
        ElementIter m_elemIter;

        typedef Iterator base_type;

        Iterator base() const
        {
            return m_it;
        }

        typedef void result_type;

        template< class Index >
        void operator()(Index& i)
        {
            *m_it++ = read(m_elemIter + i);
        }
    };


    template< class Iterator, class ElementRange >
    struct base
    {
        typedef
            proc<
                typename pass_by_value<Iterator>::type,
                typename range_iterator<ElementRange>::type
            >
        proc_t;

        typedef typename
            result_of<op_applier(proc_t&)>::type
        result_type;

        result_type operator()(Iterator& it, ElementRange& elems) const
        {
            PSTADE_CONCEPT_ASSERT((Output<Iterator>));
            PSTADE_CONCEPT_ASSERT((RandomAccess<ElementRange>));

            proc_t p = {it, boost::begin(elems)};
            return applier(p);
        }
    };


} // namespace permuter_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(permuter, (permuter_detail::base<_, _>))


} } // namespace pstade::oven


#endif
