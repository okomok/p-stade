#ifndef PSTADE_OVEN_DUPLICATES_HPP
#define PSTADE_OVEN_DUPLICATES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Michael Goldshteyn, nonunique_copy, Boost.Wiki, 2005.
//     http://www.crystalclearsoftware.com/cgi-bin/boost_wiki/wiki.pl?STLAlgorithmExtensions/NonUniqueCopy


#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // equal_to
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./dropped.hpp"
#include "./read.hpp"
#include "./successors.hpp"
#include "./uniqued.hpp"


namespace pstade { namespace oven {


namespace duplicates_detail {


    template< class BinaryPred >
    struct skip_unique
    {
        typedef skip_unique is_constant;

        template< class ForwardIter >
        ForwardIter operator()(ForwardIter first, ForwardIter last) const
        {
            ForwardIter next(first);
            while (++next != last) {
                if (m_pred(read(first), read(next)))
                    return next;
                else // skip
                    first = next;
            }

            return last;
        }

        explicit skip_unique() 
        { }

        explicit skip_unique(BinaryPred pred) :
            m_pred(pred)
        { }

    private:
        BinaryPred m_pred;
    };


} // namespace duplicates_detail


struct op_make_duplicates :
    callable<op_make_duplicates>
{
    template< class Myself, class Range, class Predicate = op_equal_to const >
    struct apply :
        boost::result_of<
            op_make_uniqued(
                typename boost::result_of<
                    op_make_dropped(
                        typename boost::result_of<
                            op_make_successors(
                                Range&,
                                duplicates_detail::skip_unique<
                                    typename pass_by_value<Predicate>::type
                                >
                            )
                        >::type,
                        int
                    )
                >::type
            )
        >
    { };

    template< class Result, class Range, class Predicate >
    Result call(Range& rng, Predicate pred) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));

        return
            make_uniqued(
                make_dropped(
                    make_successors(
                        rng,
                        duplicates_detail::skip_unique<Predicate>(pred)
                    ),
                    1
                )
            );
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return (*this)(rng, equal_to);
    }
};


PSTADE_CONSTANT(make_duplicates, (op_make_duplicates))
PSTADE_PIPABLE(duplicates, (op_make_duplicates))


} } // namespace pstade::oven


#endif
