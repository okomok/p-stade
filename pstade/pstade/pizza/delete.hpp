#ifndef PSTADE_PIZZA_DELETE_HPP
#define PSTADE_PIZZA_DELETE_HPP


// PStade.Pizza
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/if.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/overload.hpp>
#include <pstade/tomato/c_str.hpp>
#include "./access.hpp"
#include "./detail/has_pstade_pizza_profile.hpp"


namespace pstade { namespace pizza {


namespace delete_detail {


    struct member_function
    {
        template< class Profile > static
        void call(Profile& pr, TCHAR const *pszValueName)
        {
            access::detail_delete(pr, pszValueName);
        }
    };


    struct adl_customization
    {
        template< class Profile > static
        void call(Profile& pr, TCHAR const *pszValueName)
        {
            pstade_pizza_delete(pr, pszValueName, overload<>());
        }
    };


} // namespace delete_detail


template< class Profile, class CStringizable >
void delete_(Profile& pr, CStringizable const& valueName)
{
    TCHAR const *pszValueName = tomato::c_str(valueName);

    using namespace delete_detail;

    typedef typename
    boost::mpl::if_< detail::has_pstade_pizza_profile<Profile>,
        member_function,
        adl_customization
    >::type impl_t;

    impl_t::call(pr, pszValueName);
}


} } // namespace pstade::pizza


#endif
