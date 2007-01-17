#ifndef PSTADE_OVEN_SUB_SET_HPP
#define PSTADE_OVEN_SUB_SET_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/base_from_member.hpp>
#include <boost/utility/result_of.hpp>
#include "./indirected.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace sub_set_detail {


    template< class Range >
    struct storage
    {
        typedef std::vector<
            typename range_iterator<Range>::type
        > type;
    };


    template< class Range >
    struct init
    {
        typedef boost::base_from_member<
            typename storage<Range>::type
        > type;
    };


    template< class Range >
    struct super_ :
        boost::result_of<op_make_indirected<>(typename storage<Range>::type&)>
    { };


} // namespace sub_set_detail


template< class Range >
struct sub_set :
    private sub_set_detail::init<Range>::type,
    sub_set_detail::super_<Range>::type
{
private:
    typedef typename sub_set_detail::init<Range>::type init_t;
    typedef typename sub_set_detail::super_<Range>::type super_t;

public:
    // Question: should this ctor be removed?
    //   If so, 'sub_set<> ss(rng|directed);'
    //
    explicit sub_set(Range& rng) :
        init_t(
            boost::make_counting_iterator(boost::begin(rng)),
            boost::make_counting_iterator(boost::end(rng))
        ),
        super_t(init_t::member)
    { }

    template< class Iterators >
    explicit sub_set(Iterators& its) :
        init_t(boost::begin(its), boost::end(its)),
        super_t(init_t::member)
    { }
};


} } // namespace pstade::oven


#endif
