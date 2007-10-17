#ifndef PSTADE_OVEN_RANGE_TRANSFORMER_HPP
#define PSTADE_OVEN_RANGE_TRANSFORMER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // copy
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/to_ref.hpp>
#include <pstade/pass_by.hpp>
#include "./concepts.hpp"
#include "./detail/adaptor_output_iterator.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./single.hpp"


namespace pstade { namespace oven {


namespace range_transformer_detail {


    template< class UnaryFun >
    struct proc
    {
        UnaryFun m_fun;

        typedef void result_type;

        template< class Iterator, class Value >
        void operator()(Iterator& it, Value& v)
        {
            aux(it, egg::to_ref( m_fun(single(v)) ));
        }

        template< class Iterator, class Range >
        void aux(Iterator& it, Range& rng)
        {
            it = std::copy(boost::begin(rng), boost::end(rng), it);
        }
    };


    template< class Iterator, class UnaryFun >
    struct base
    {
        typedef
            proc<typename pass_by_value<UnaryFun>::type>
        proc_t;

        typedef
            detail::adaptor_output_iterator<
                typename pass_by_value<Iterator>::type,
                proc_t
            >
        result_type;

        result_type operator()(Iterator& it, UnaryFun& fun) const
        {
            PSTADE_CONCEPT_ASSERT((Output<Iterator>));
            proc_t p = {fun};
            return result_type(it, p);
        }
    };


} // namespace range_transformer_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(range_transformer, (range_transformer_detail::base<_, _>))


} } // namespace pstade::oven


#endif
