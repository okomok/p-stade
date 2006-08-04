#ifndef PSTADE_OVEN_UTF8_DECODE_RANGE_HPP
#define PSTADE_OVEN_UTF8_DECODE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp> // uint32_t
#include <boost/range/iterator_range.hpp>
#include <boost/regex/pending/unicode_iterator.hpp> // u8_to_u32_iterator
#include <boost/type_traits/add_const.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/nonassignable.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace utf8_decode_range_detail {


    template< class BidiRange, class Ucs4T >
    struct super_
    {
        typedef boost::iterator_range<
            boost::u8_to_u32_iterator<
                typename range_iterator<BidiRange>::type,
                Ucs4T
            >
        > type;
    };


} // namespace utf8_decode_range_detail


template< class BidiRange, class Ucs4T = boost::uint32_t >
struct utf8_decode_range :
    utf8_decode_range_detail::super_<BidiRange, Ucs4T>::type,
    private lightweight_proxy< utf8_decode_range<BidiRange, Ucs4T> >
{
    typedef BidiRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(BidiRange, BidirectionalRangeConcept);
    typedef typename utf8_decode_range_detail::super_<BidiRange, Ucs4T>::type super_t;

public:
    explicit utf8_decode_range(BidiRange& rng) :
        super_t(rng)
    { }
};


// generators
//

template< class Ucs4T, class BidiRange > inline
typename const_overloaded<utf8_decode_range<BidiRange, Ucs4T>, BidiRange>::type const
make_utf8_decode_range(BidiRange& rng)
{
    return utf8_decode_range<BidiRange, Ucs4T>(rng);
}


template< class Ucs4T, class BidiRange > inline
utf8_decode_range<typename boost::add_const<BidiRange>::type, Ucs4T> const
make_utf8_decode_range(BidiRange const& rng)
{
    return utf8_decode_range<typename boost::add_const<BidiRange>::type, Ucs4T>(rng);
}


template< class Usc4T >
struct utf8_decoded;


namespace utf8_decode_range_detail {


    struct adl_marker
    { };


    template< class BidiRange, class Ucs4T > inline
    utf8_decode_range<BidiRange, Ucs4T> const
    operator|(BidiRange& rng, utf8_decoded<Ucs4T> const&)
    {
        return utf8_decode_range<BidiRange, Ucs4T>(rng);
    }


    template< class BidiRange, class Ucs4T > inline
    utf8_decode_range<typename boost::add_const<BidiRange>::type, Ucs4T> const
    operator|(BidiRange const& rng, utf8_decoded<Ucs4T> const&)
    {
        return utf8_decode_range<typename boost::add_const<BidiRange>::type, Ucs4T>(rng);
    }


} // namespace utf8_decode_range_detail


template< class Usc4T = boost::uint32_t >
struct utf8_decoded :
    utf8_decode_range_detail::adl_marker,
    private nonassignable
{ };


} } // namespace pstade::oven


#endif
