#ifndef PSTADE_OVEN_UTF8_ENCODE_RANGE_HPP
#define PSTADE_OVEN_UTF8_ENCODE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp> // uint8_t
#include <boost/range/iterator_range.hpp>
#include <boost/regex/pending/unicode_iterator.hpp> // u32_to_u8_iterator
#include <boost/type_traits/add_const.hpp>
#include <pstade/const_overloaded.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_iterator.hpp"



namespace pstade { namespace oven {


namespace utf8_encode_range_detail {


    template< class BidiRange, class U8T >
    struct super_
    {
        typedef boost::iterator_range<
            boost::u32_to_u8_iterator<
                typename range_iterator<BidiRange>::type,
                U8T
            >
        > type;
    };


} // namespace utf8_encode_range_detail


template< class BidiRange, class U8T = boost::uint8_t >
struct utf8_encode_range :
    utf8_encode_range_detail::super_<BidiRange, U8T>::type,
    private lightweight_proxy< utf8_encode_range<BidiRange, U8T> >
{
    typedef BidiRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(BidiRange, BidirectionalRangeConcept);
    typedef typename utf8_encode_range_detail::super_<BidiRange, U8T>::type super_t;

public:
    explicit utf8_encode_range(BidiRange& rng) :
        super_t(rng)
    { }
};


// generators
//

template< class U8T, class BidiRange > inline
typename const_overloaded<utf8_encode_range<BidiRange, U8T>, BidiRange>::type const
make_utf8_encode_range(BidiRange& rng)
{
    return utf8_encode_range<BidiRange, U8T>(rng);
}


template< class U8T, class BidiRange > inline
utf8_encode_range<typename boost::add_const<BidiRange>::type, U8T> const
make_utf8_encode_range(BidiRange const& rng)
{
    return utf8_encode_range<typename boost::add_const<BidiRange>::type, U8T>(rng);
}


template< class U8T >
struct utf8_encoded;


namespace utf8_encode_range_detail {


    struct adl_marker
    { };


    template< class BidiRange, class U8T > inline
    utf8_encode_range<BidiRange, U8T> const
    operator|(BidiRange& rng, utf8_encoded<U8T> const&)
    {
        return utf8_encode_range<BidiRange, U8T>(rng);
    }


    template< class BidiRange, class U8T > inline
    utf8_encode_range<typename boost::add_const<BidiRange>::type, U8T> const
    operator|(BidiRange const& rng, utf8_encoded<U8T> const&)
    {
        return utf8_encode_range<typename boost::add_const<BidiRange>::type, U8T>(rng);
    }


} // namespace utf8_encode_range_detail


template< class U8T = boost::uint8_t >
struct utf8_encoded :
    utf8_encode_range_detail::adl_marker
{ };


} } // namespace pstade::oven


#endif
