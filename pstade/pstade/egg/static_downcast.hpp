#ifndef PSTADE_EGG_STATIC_DOWNCAST_HPP
#define PSTADE_EGG_STATIC_DOWNCAST_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Same as 'boost::smart_cast' without crosscast.


// Note:
//
// RTTI(/GR option) is required in debug mode.
//
// 'Derived& d = automatic_static_downcast(b);' seems impossible.
// According to 8.5.3/5, the initializer must be lvalue to "bind directly".


#include <boost/cast.hpp> // polymorphic_downcast
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/affect.hpp>
#include <pstade/enable_if.hpp>
#include "./function.hpp"
#include "./specified.hpp"


namespace pstade { namespace egg {


    namespace static_downcast_detail {


        template<class Derived, class Base> inline
        Derived& aux(Base& base, typename disable_if<boost::is_polymorphic<Base> >::type = 0)
        {
            BOOST_MPL_ASSERT((boost::is_base_of<
                typename boost::remove_cv<Base>::type,
                typename boost::remove_cv<Derived>::type
            >));

            return static_cast<Derived&>(base);
        }

        template<class Derived, class Base> inline
        Derived& aux(Base& base, typename enable_if< boost::is_polymorphic<Base> >::type = 0)
        {
            return *boost::polymorphic_downcast<Derived *>(boost::addressof(base));
        }


        template<class Derived>
        struct baby
        {
            template<class Myself, class Base>
            struct apply :
                affect<Base&, Derived>
            { };

            template<class Result, class Base>
            Result call(Base& base) const
            {
                return static_downcast_detail::aux<
                    typename boost::remove_reference<Result>::type
                >(base);
            }
        };


    } // namespace static_downcast_detail


    template<class Derived>
    struct tp_static_downcast
    {
        typedef
            function< static_downcast_detail::baby<Derived> >
        type;
    };


    template<class Derived>
    struct xp_static_downcast :
        tp_static_downcast<Derived>::type
    { };


    PSTADE_EGG_SPECIFIED1(static_downcast, xp_static_downcast, (class))


} } // namespace pstade::egg


#endif
