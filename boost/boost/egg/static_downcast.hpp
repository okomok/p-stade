#ifndef BOOST_EGG_STATIC_DOWNCAST_HPP
#define BOOST_EGG_STATIC_DOWNCAST_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Same as 'boost::smart_cast' without crosscast.
// Notice RTTI(/GR option) is required in debug mode.


#include <boost/cast.hpp> // polymorphic_downcast
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/detail/affect.hpp>
#include <boost/egg/detail/const_overloaded.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/detail/explicit.hpp>


namespace boost { namespace egg {


    namespace static_downcast_detail {


        namespace here = static_downcast_detail;


        template<class Derived, class Base> inline
        Derived *aux_(Base *pbase, typename disable_if_<is_polymorphic<Base> >::type = 0)
        {
            BOOST_MPL_ASSERT((is_base_of<
                typename remove_cv<Base>::type,
                typename remove_cv<Derived>::type
            >));

            return static_cast<Derived *>(pbase);
        }

        template<class Derived, class Base> inline
        Derived *aux_(Base *pbase, typename enable_if_< is_polymorphic<Base> >::type = 0)
        {
            return boost::polymorphic_downcast<Derived *>(pbase);
        }


        template<class Derived>
        struct little
        {
            template<class Me, class Base>
            struct apply :
                details::affect<Base &, Derived>
            { };

            template<class Re, class Base>
            Re call(Base &base) const
            {
                return *here::aux_<typename remove_reference<Re>::type>(boost::addressof(base));
            }
        };


    } // namespace static_downcast_detail


    template<class Derived>
    struct X_static_downcast :
        function<static_downcast_detail::little<Derived>, by_perfect>
    { };


    BOOST_EGG_EXPLICIT1(static_downcast, X_static_downcast, (class))


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
