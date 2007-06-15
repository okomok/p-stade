#ifndef PSTADE_PIZZA_SET_STRING_HPP
#define PSTADE_PIZZA_SET_STRING_HPP


// PStade.Pizza
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/if.hpp>
#include <pstade/gravy/sdk/tchar.hpp>
#include <pstade/detail/overload.hpp>
#include <pstade/gravy/c_str.hpp>
#include "./access.hpp"
#include "./detail/has_pstade_pizza_profile.hpp"


namespace pstade { namespace pizza {


namespace set_string_detail {


    struct member_function
    {
        template< class Profile > static
        void call(Profile& pr, TCHAR const *pszValueName, TCHAR const *pszValue)
        {
            access::detail_set_string(pr, pszValueName, pszValue);
        }
    };


    struct adl_customization
    {
        template< class Profile > static
        void call(Profile& pr, TCHAR const *pszValueName, TCHAR const *pszValue)
        {
            pstade_pizza_set_string(pr, pszValueName, pszValue, pstade::detail::overload<>());
        }
    };


} // namespace set_string_detail


template< class Profile, class CStringizeable0, class CStringizeable1 > inline
void set_string(Profile& pr, CStringizeable0 const& valueName, CStringizeable1 const& value)
{
    TCHAR const *pszValueName = gravy::c_str(valueName);
    TCHAR const *pszValue = gravy::c_str(value);

    using namespace set_string_detail;

    typedef typename
    boost::mpl::if_< detail::has_pstade_pizza_profile<Profile>,
        member_function,
        adl_customization
    >::type impl_t;

    impl_t::call(pr, pszValueName, pszValue);
}


} } // namespace pstade::pizza


#endif
