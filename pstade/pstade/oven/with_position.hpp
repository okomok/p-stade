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
#include <pstade/egg/make_function.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pass_by.hpp>
#include "./concepts.hpp"
#include "./detail/has_position.hpp"
#include "./detail/little_to_adaptor.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


// with_position
//

namespace with_position_detail {


    struct little
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
            return egg::make_function(*this)(rng, boost::spirit::file_position());
        }
    };


} // namespace with_position_detail


PSTADE_OVEN_LITTLE_TO_ADAPTOR(with_position, (with_position_detail::little))


// position
//

template< class Position >
struct X_position
{
    typedef X_position function_type;
    typedef Position result_type;

    template< class Adapted >
    Position operator()(Adapted ad,
        typename enable_if< detail::has_position<Adapted, Position> >::type = 0) const
    {
        return ad.get_position();
    }

    template< class Adapted >
    Position operator()(Adapted ad,
        typename disable_if<detail::has_position<Adapted, Position> >::type = 0) const
    {
        return (*this)(ad.base());

    }
};

template< class Position, class Adapted > inline
Position position(Adapted ad)
{
    return X_position<Position>()(ad);
}


} } // namespace pstade::oven


#endif
