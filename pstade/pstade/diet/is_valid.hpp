#ifndef PSTADE_DIET_IS_VALID_HPP
#define PSTADE_DIET_IS_VALID_HPP


// PStade.Diet
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/enable_if.hpp>
#include <boost/foreach.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_reference
#include <boost/mpl/if.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/overload.hpp>
#include "./access.hpp"
#include "./detail/has_pstade_diagnostic.hpp"


namespace pstade { namespace diet {


namespace is_valid_detail {


    struct member_function
    {
        template< class T > static
        bool call(const T& x)
        {
            return access::detail_is_valid(x);
        }
    };


    template< class T > inline
    bool pstade_diet_is_valid(const T& x)
    {
        return pstade_diet_is_valid(x, overload<>());
    }

    struct adl_customization
    {
        template< class T > static
        bool call(const T& x)
        {
            return pstade_diet_is_valid(x);
        }
    };


} // namespace is_valid_detail


template< class Diagnostic > inline
bool is_valid(const Diagnostic& dg)
{
    typedef typename
    boost::mpl::if_< detail::has_pstade_diet_diagnostic<Diagnostic>,
        is_valid_detail::member_function,
        is_valid_detail::adl_customization
    >::type impl_t;

    return impl_t::call(dg);
}


} } // namespace pstade::diet


// predefined customizations
//

template< class Range > inline
typename boost::enable_if<pstade::apple::is_boost_range<Range>, bool>::type
pstade_diet_is_valid(const Range& rng, pstade::overload<>)
{
    typedef typename boost::range_const_iterator<Range>::type iter_t;
    typedef typename boost::iterator_reference<iter_t>::type ref_t;

    BOOST_FOREACH (ref_t x, rng) {
        if (!pstade::diet::is_valid(x))
            return false;
    }

    return true;
}


#endif
