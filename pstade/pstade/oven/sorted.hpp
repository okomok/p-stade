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
#include <pstade/egg/less.hpp>
#include <pstade/egg/make_function_of.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./detail/baby_to_adaptor.hpp"
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


    struct baby
    {
        template< class Myself, class Range, class Compare = void >
        struct apply :
            result_of<
                op_make_indirected(
                    typename result_of<op_make_outplaced(Range&)>::type&
                )
            >
        { };

        template< class Result, class Range, class Compare >
        Result call(Range& rng, Compare comp) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            typename result_of<op_make_outplaced(Range&)>::type its = make_outplaced(rng);
            std::sort(boost::begin(its), boost::end(its), read_then<Compare>(comp));
            return make_indirected(its);
        }

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            return egg::make_function_of(*this)(rng, egg::less);
        }
    };


} // namespace sorted_detail


PSTADE_OVEN_BABY_TO_ADAPTOR(sorted, (sorted_detail::baby))


} } // namespace pstade::oven


#endif
