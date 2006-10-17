#ifndef PSTADE_OVEN_SHARE_RANGE_HPP
#define PSTADE_OVEN_SHARE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
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
#include <boost/utility/addressof.hpp>
#include <pstade/instance.hpp>
#include <pstade/radish/pointable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
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
    radish::pointable< share_range<Range>, Range >,
    private as_lightweight_proxy< share_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

private:
    typedef typename share_range_detail::super_<Range>::type super_t;

public:
    explicit share_range(Range *prng) :
        super_t(share_range_detail::make<super_t>(prng))
    { }

    explicit share_range(std::auto_ptr<Range> prng) :
        super_t(share_range_detail::make<super_t>(prng.release()))
    { }

    Range *operator->() const
    {
        return boost::addressof(this->begin().range());
    }

    typedef Range pstade_oven_range_base_type;
};


// Egg is useless here, because a temporary 'auto_ptr' is const-qualified,
// thus, the ownership cannot be moved. So make it by scratch.
//

template< class Pointer > inline
share_range<typename boost::pointee<Pointer>::type> const
make_share_range(Pointer prng)
{
    return share_range<typename boost::pointee<Pointer>::type>(prng);
}


namespace share_range_detail {


    struct pipe :
        private boost::noncopyable
    { };


    template< class Pointer > inline
    share_range<typename boost::pointee<Pointer>::type> const
    operator|(Pointer prng, pipe const&)
    {
        return share_range<typename boost::pointee<Pointer>::type>(prng);
    }


} // namespace share_range_detail


PSTADE_INSTANCE(share_range_detail::pipe const, shared, value)


} } // namespace pstade::oven


#endif
