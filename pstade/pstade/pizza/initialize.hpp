#ifndef PSTADE_PIZZA_INITIALIZE_HPP
#define PSTADE_PIZZA_INITIALIZE_HPP


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
#include <pstade/tomato/diet/valid.hpp>
#include "./access.hpp"
#include "./detail/has_pstade_pizza_profile.hpp"


namespace pstade { namespace pizza {


namespace initialize_detail {


    struct member_function
    {
        template< class Profile > static
        void call(Profile& pr, const TCHAR *pszName)
        {
            access::detail_initialize(pr, pszName);
        }
    };


    struct adl_customization
    {
        template< class Profile > static
        void call(Profile& pr, const TCHAR *pszName)
        {
            pstade_pizza_initialize(pr, pszName, overload<>());
        }
    };


} // namespace initialize_detail


template< class Profile, class CStringizable >
void initialize(Profile& pr, const CStringizable& name)
{
    const TCHAR *pszName = tomato::c_str(name);
    BOOST_ASSERT(diet::valid(pszName));


    using namespace initialize_detail;

    typedef typename
    boost::mpl::if_< detail::has_pstade_pizza_profile<Profile>,
        member_function,
        adl_customization
    >::type impl_t;

    impl_t::call(pr, pszName);
}


} } // namespace pstade::pizza


#endif
