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
#include "./concepts.hpp"
#include "./detail/adaptor_output_iterator.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./range_iterator.hpp"
#include "./read.hpp"


namespace pstade { namespace oven {


namespace permuter_detail {


    template< class ElementIter >
    struct proc
    {
        ElementIter m_elemIter;

        typedef void result_type;

        template< class Iterator, class Index >
        void operator()(Iterator& it, Index& i)
        {
            *it++ = read(m_elemIter + i);
        }
    };


    template< class Iterator, class ElementRange >
    struct base
    {
        typedef
            proc<typename range_iterator<ElementRange>::type>
        proc_t;

        typedef
            detail::adaptor_output_iterator<
                typename pass_by_value<Iterator>::type,
                proc_t
            >
        result_type;

        result_type operator()(Iterator& it, ElementRange& elems) const
        {
            PSTADE_CONCEPT_ASSERT((Output<Iterator>));
            PSTADE_CONCEPT_ASSERT((RandomAccess<ElementRange>));
            proc_t p = {boost::begin(elems)};
            return result_type(it, p);
        }
    };


} // namespace permuter_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(permuter, (permuter_detail::base<_, _>))


} } // namespace pstade::oven


#endif
