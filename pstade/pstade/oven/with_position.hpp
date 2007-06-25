#ifndef PSTADE_OVEN_WITH_POSITION_HPP
#define PSTADE_OVEN_WITH_POSITION_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/spirit/iterator/position_iterator.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


struct op_make_with_position :
    callable<op_make_with_position>
{
    template< class Myself, class Range, class PositionT = boost::spirit::file_position const, class Int = void >
    struct apply
    {
        typedef
            boost::spirit::position_iterator2< // 2!
                typename range_iterator<Range>::type,
                typename pass_by_value<PositionT>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range, class PositionT >
    Result call(Range& rng, PositionT& pos, int tabchars = 4) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));

        typedef typename Result::iterator iter_t;
        iter_t first(boost::begin(rng), boost::end(rng), pos);
        first.set_tabchars(tabchars);
        return Result(first, iter_t());
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return (*this)(rng, boost::spirit::file_position());
    }
};


PSTADE_CONSTANT(make_with_position, (op_make_with_position))
PSTADE_PIPABLE(with_position, (op_make_with_position))


} } // namespace pstade::oven


#endif
