#ifndef PSTADE_OVEN_CONSTRUCT_HPP
#define PSTADE_OVEN_CONSTRUCT_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/identity.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/addressof.hpp>


namespace pstade { namespace oven {


// customization point
//

template< class T >
struct constructor_customization;


struct constructor_default_tag
{ };

template< class T >
struct constructor_customization_tag :
    boost::mpl::identity<constructor_default_tag>
{ };


template< >
struct constructor_customization<constructor_default_tag>
{
    template< class T, class Range >
    T construct(const Range& rng) const
    {
        return T(boost::begin(rng), boost::end(rng));
    }
};


// constructor
//

template< class T, class Range > inline
T constructor(const Range& rng)
{
    typedef typename constructor_customization_tag<T>::type tag_t;
    return constructor_customization<tag_t>().template construct<T>(rng);
}


// construct
//

namespace construct_detail {


    template< class Range >
    struct temp
    {
        explicit temp(const Range& rng) :
            m_prng(boost::addressof(rng))
        { }

        template< class T >
        operator T() const
        {
            return oven::constructor<T>(*m_prng);
        }

    private:
        const Range *m_prng;
    };


} // namespace construct_detail


template< class Range > inline const
construct_detail::temp<Range> construct(const Range& rng)
{
    // Off Topic:
    // When tmp is missing under GCC3.4.4, it ran a foul of strange behaviors
    // if conversion template target is reference type.

    construct_detail::temp<Range> tmp(rng);
    return tmp;
}


} } // namespace pstade::oven


#endif
