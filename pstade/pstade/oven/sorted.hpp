#ifndef PSTADE_OVEN_SORTED_HPP
#define PSTADE_OVEN_SORTED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // sort
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/pipable.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./indirected.hpp"
#include "./outplaced.hpp"
#include "./read.hpp"


namespace pstade { namespace oven {


namespace sorted_detail {


    template< class Compare >
    struct read_then
    {
        template< class Iterator >
        bool operator()(Iterator it1, Iterator it2) const
        {
            return m_comp(read(it1), read(it2));
        }

        explicit read_then(Compare comp) :
            m_comp(comp)
        { }

    private:
        Compare m_comp;
    };


} // namespace sorted_detail


struct op_make_sorted :
    callable<op_make_sorted>
{
    template< class Myself, class Range, class Compare = op_less const >
    struct apply :
        result_of<
            op_make_indirected<>(
                typename result_of<op_make_outplaced(Range&)>::type&
            )
        >
    { };

    template< class Result, class Range, class Compare >
    Result call(Range& rng, Compare comp) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));
        typename result_of<op_make_outplaced(Range&)>::type its = make_outplaced(rng);
        std::sort(boost::begin(its), boost::end(its), sorted_detail::read_then<Compare>(comp));
        return make_indirected(its);
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
