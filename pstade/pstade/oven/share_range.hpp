#ifndef PSTADE_OVEN_SHARE_RANGE_HPP
#define PSTADE_OVEN_SHARE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/noncopyable.hpp>
#include <boost/pointee.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/instance.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./share_iterator.hpp"


namespace pstade { namespace oven {


namespace share_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            share_iterator<Range>
        > type;
    };


    template< class Super, class Range >
    Super make(Range *prng)
    {
        boost::shared_ptr<Range> sprng(prng);
        return Super(
            oven::make_share_iterator(boost::begin(*sprng), sprng),
            oven::make_share_iterator(boost::end(*sprng),   sprng)
        );
    }


} // namespace share_range_detail


template< class Range >
struct share_range :
    share_range_detail::super_<Range>::type,
    private lightweight_proxy< share_range<Range> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename share_range_detail::super_<Range>::type super_t;

public:
    explicit share_range(Range *prng) :
        super_t(share_range_detail::make<super_t>(prng))
    { }

    explicit share_range(std::auto_ptr<Range> prng) :
        super_t(share_range_detail::make<super_t>(prng.release()))
    { }

    Range& operator*() const
    {
        return boost::begin(*this).range();
    }
};


// Workaround:
// Egg is useless, because a temporary 'auto_ptr' is const-qualified,
// then, the ownership cannot be moved.
//

template< class Pointer > inline
share_range<typename boost::pointee<Pointer>::type> const
make_share_range(Pointer prng)
{
    return share_range<typename boost::pointee<Pointer>::type>(prng);
}


namespace share_range_detail {


    struct pipeline :
        private boost::noncopyable
    { };


    template< class Pointer > inline
    share_range<typename boost::pointee<Pointer>::type> const
    operator|(Pointer prng, pipeline const&)
    {
        return share_range<typename boost::pointee<Pointer>::type>(prng);
    }


} // namespace share_range_detail


PSTADE_INSTANCE(share_range_detail::pipeline const, shared, value)


} } // namespace pstade::oven


#endif
