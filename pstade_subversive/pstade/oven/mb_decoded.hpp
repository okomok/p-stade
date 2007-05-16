#ifndef PSTADE_OVEN_MB_DECODED_HPP
#define PSTADE_OVEN_MB_DECODED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/archive/iterators/wchar_from_mb.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace mb_decoded_detail {


    // The convertibility of the original is over-optimistic.


    template< class Iterator >
    struct wchar_from_mb;


    template< class Iterator >
    struct wchar_from_mb_super
    {
        typedef
            boost::iterator_adaptor<
                wchar_from_mb<Iterator>,
                boost::archive::iterators::wchar_from_mb<Iterator>
            >
        type;
    };


    template< class Iterator >
    struct wchar_from_mb :
        wchar_from_mb_super<Iterator>::type
    {
    private:
        typedef typename wchar_from_mb_super<Iterator>::type super_t;

    public:
        explicit wchar_from_mb(Iterator it) :
            super_t(it)
        { }

        template< class I >
        wchar_from_mb(wchar_from_mb<I> const& other,
            typename boost::enable_if_convertible<I, Iterator>::type * = 0
        ) :
            super_t(other.base())
        { }

    private:
    friend class boost::iterator_core_access;
        // as is.
    };


    template< class Range >
    struct baby
    {
        typedef
            wchar_from_mb<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng) const
        {
            return result_type(rng);
        }
    };


} // namespace mb_decoded_detail


PSTADE_FUNCTION(make_mb_decoded, (mb_decoded_detail::baby<_>))
PSTADE_PIPABLE(mb_decoded, (op_make_mb_decoded))


} } // namespace pstade::oven


#endif
