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
#include "./concepts.hpp"
#include "./detail/adaptor_output_iterator.hpp"
#include "./detail/base_to_adaptor.hpp"


namespace pstade { namespace oven {


namespace indirecter_detail {


    struct proc
    {
        typedef void result_type;

        template< class Iterator, class Value >
        void operator()(Iterator& it, Value& v)
        {
            *it++ = *v;
        }
    };


    template< class Iterator >
    struct base
    {
        typedef
            detail::adaptor_output_iterator<
                typename pass_by_value<Iterator>::type,
                proc
            >
        result_type;

        result_type operator()(Iterator& it) const
        {
            PSTADE_CONCEPT_ASSERT((Output<Iterator>));
            return result_type(it, proc());
        }
    };


} // namespace indirecter_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(indirecter, (indirecter_detail::base<_>))


} } // namespace pstade::oven


#endif
