#ifndef PSTADE_OVEN_COPY_RANGE_HPP
#define PSTADE_OVEN_COPY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/utility/result_of.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/automatic.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./extension.hpp"


namespace pstade { namespace oven {


template< class CopyableRange_ >
struct op_copy_range
{
    typedef CopyableRange_ result_type;

    template< class Range >
    result_type operator()(Range const& from) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        return pstade_oven_extension::Range<CopyableRange_>().
            BOOST_NESTED_TEMPLATE copy<CopyableRange_>(from);
    }
};


PSTADE_ADL_BARRIER(copy_range) { // for Boost

template< class CopyableRange_, class Range > inline
typename boost::result_of<op_copy_range<CopyableRange_>(PSTADE_DEDUCED_CONST(Range)&)>::type
copy_range(Range const& from)
{
    return op_copy_range<CopyableRange_>()(from);
}

} // ADL barrier


PSTADE_PIPABLE(copied, (automatic< op_copy_range<boost::mpl::_1> >))


} } // namespace pstade::oven


// Makes 'boost::array' CopyableRange_.
//


#include <cstddef> // size_t
#include <boost/array.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include "./range_iterator.hpp"


namespace pstade_oven_extension {


    template< class T, std::size_t N, class Range >
    boost::array<T, N> pstade_oven_(copy_range< boost::array<T, N> >, Range& from)
    {
        typename pstade::oven::range_iterator<Range>::type
            it(boost::begin(from)), last(boost::end(from));

        boost::array<T, N> arr;
        std::size_t i = 0;

        for(; it != last; ++it, ++i)
            arr.at(i) = *it;
        for(; i != N; ++i)
            arr.at(i) = T();

        return arr; 
    }


} // namespace pstade_oven_extension


#endif
