#ifndef PSTADE_OVEN_SUB_SET_HPP
#define PSTADE_OVEN_SUB_SET_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/base_from_member.hpp>
#include "./indirect_range.hpp"
#include "./range_iterator_type.hpp"


namespace pstade { namespace oven {


namespace sub_set_detail {


    template< class Range >
    struct storage
    {
        typedef typename range_iterator<Range>::type iter_t;
        typedef std::vector<iter_t> type;
    };


    template< class Range >
    struct super_
    {
        typedef oven::indirect_range<
            typename storage<Range>::type
        > type;
    };


} // namespace sub_set_detail


template< class Range >
struct sub_set :
    private boost::base_from_member< typename sub_set_detail::storage<Range>::type >,
    sub_set_detail::super_<Range>::type
{
private:
    typedef boost::base_from_member< typename sub_set_detail::storage<Range>::type > storage_bt;
    typedef typename sub_set_detail::super_<Range>::type super_t;

public:
    // Question: should this ctor be removed?
    //   If so, 'sub_set<> ss(rng|directed);'
    //
    explicit sub_set(Range& rng) :
        storage_bt(
            boost::make_counting_iterator(boost::begin(rng)),
            boost::make_counting_iterator(boost::end(rng))
        ),
        super_t(storage_bt::member)
    { }

    template< class Iterators >
    explicit sub_set(Iterators& its) :
        storage_bt(boost::begin(its), boost::end(its)),
        super_t(storage_bt::member)
    { }
};


} } // namespace pstade::oven


#endif
