#ifndef PSTADE_OVEN_SORTED_HPP
#define PSTADE_OVEN_SORTED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Rejected...
//
// Because this adaptor is *expensive* enough
// to effect on your software design sooner or later.
// On the other hand, when you can accept the big time-and-space,
// this may be still useful. So I don't remove...


#include <boost/ptr_container/indirect_fun.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./algorithm.hpp" // sort
#include "./concepts.hpp"
#include "./outplaced.hpp"


namespace pstade { namespace oven {


namespace sorted_detail {


    template< class Compare >
    struct op_sort
    {
        explicit op_sort(Compare const& comp) :
            m_comp(comp)
        { }

        template< class Range >
        void operator()(Range& its) const
        {
            sort(its, boost::make_indirect_fun(m_comp));
        }

    private:
        Compare m_comp;
    };


} // namespace sorted_detail


struct op_make_sorted :
    callable<op_make_sorted>
{
    template< class Myself, class Range, class Compare = op_less const >
    struct apply
    {
        typedef
            sorted_detail::op_sort<typename pass_by_value<Compare>::type>
        fun_t;

        typedef typename
            boost::result_of<
                op_make_outplaced(Range&, fun_t)
            >::type
        type;
    };

    template< class Result, class Range, class Compare >
    Result call(Range& rng, Compare& comp) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));
        // PSTADE_CONCEPT_ASSERT((Readable<Range>));

        typedef typename apply<void, Range, Compare>::fun_t fun_t;
        return make_outplaced(rng, fun_t(comp));
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return (*this)(rng, less);
    }
};


PSTADE_CONSTANT(make_sorted, (op_make_sorted))
PSTADE_PIPABLE(sorted, (op_make_sorted))


} } // namespace pstade::oven


#endif
