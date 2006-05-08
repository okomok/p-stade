#ifndef PSTADE_OVEN_SHARE_RANGE_HPP
#define PSTADE_OVEN_SHARE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/shared_container_iterator.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/utility/base_from_member.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace share_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            boost::shared_container_iterator<Range>
        > type;
    };


} // namespace share_range_detail


template< class Range >
struct share_range :
    private boost::base_from_member< boost::shared_ptr<Range> >,
    share_range_detail::super_<Range>::type
{
private:
    typedef boost::base_from_member< boost::shared_ptr<Range> > ptr_bt;
    typedef typename share_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit share_range(Range *prng) :
        ptr_bt(boost::shared_ptr<Range>(prng)),
        super_t(
           iter_t(boost::begin(*ptr_bt::member), ptr_bt::member),
           iter_t(boost::end(*ptr_bt::member), ptr_bt::member)
        )
    { }

    // Workaround:
    // VC++7.1 implicitly generated copy constructor is sometimes broken
    // if the base type has constructor templates (as 'base_from_member' does).
    // VC++7.1 seems to bring 'other' to the construct template of the base type.
    // This problem is the same as 'boost::sub_range' nonassignable behavior.
    //
    share_range(const share_range& other) :
        ptr_bt(other.member),
        super_t(other)
    { }

    // Question:
    // good or bad syntax?
    //
    Range& operator*() const
    {
        return *ptr_bt::member;
    }
};


namespace share_range_detail {


    struct baby_generator
    {
        template< class RangePtrT >
        struct result
        {
            typedef typename boost::remove_pointer<RangePtrT>::type rng_t;
            typedef const share_range<rng_t> type;
        };

        template< class Result, class RangePtrT >
        Result call(RangePtrT prng)
        {
            return Result(prng);
        }
    };


} // namespace share_range_detail


PSTADE_EGG_FUNCTION(make_share_range, share_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(shared, share_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::share_range, 1)


#endif
