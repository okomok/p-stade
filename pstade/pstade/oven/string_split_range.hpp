#ifndef PSTADE_OVEN_STRING_SPLIT_RANGE_HPP
#define PSTADE_OVEN_STRING_SPLIT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/algorithm/string/find_iterator.hpp> // split_iterator
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace string_split_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            boost::algorithm::split_iterator<
                typename range_iterator<Range>::type
            >
        >
    { };


} // namespace string_split_range_detail


template< class Range >
struct string_split_range :
    string_split_range_detail::super_<Range>::type,
    private as_lightweight_proxy< string_split_range<Range> >
{
    typedef string_split_range type;

private:
    typedef typename string_split_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    template< class FinderT >
    string_split_range(Range& rng, FinderT f) :
        super_t(iter_t(rng, f), iter_t())
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_string_split_range, string_split_range< deduce_to_qualified<from_1> > const)
PSTADE_PIPABLE(string_split, op_make_string_split_range)


} } // namespace pstade::oven


#endif
