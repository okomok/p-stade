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
// Notice RTTI(/GR option) is required in debug mode.


#include <boost/cast.hpp> // polymorphic_downcast
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/affect.hpp>
#include <pstade/enable_if.hpp>
#include "./by_perfect.hpp"
#include "./specified.hpp"


namespace pstade { namespace egg {


    namespace static_downcast_detail {


        namespace here = static_downcast_detail;


        template<class Derived, class Base> inline
        Derived *aux(Base *pbase, typename disable_if<boost::is_polymorphic<Base> >::type = 0)
        {
            BOOST_MPL_ASSERT((boost::is_base_of<
                typename boost::remove_cv<Base>::type,
                typename boost::remove_cv<Derived>::type
            >));

            return static_cast<Derived *>(pbase);
        }

        template<class Derived, class Base> inline
        Derived *aux(Base *pbase, typename enable_if< boost::is_polymorphic<Base> >::type = 0)
        {
            return boost::polymorphic_downcast<Derived *>(pbase);
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
                return *here::aux<typename boost::remove_reference<Result>::type>(boost::addressof(base));
            }
        };


        template<class Derived>
        struct pod_
        {
            typedef function<baby<Derived>, by_perfect> type;
        };


    } // namespace static_downcast_detail


    template<class Derived>
    struct X_static_downcast :
        static_downcast_detail::pod_<Derived>::type
    {
        typedef typename static_downcast_detail::pod_<Derived>::type pod_type;
    };


    PSTADE_EGG_SPECIFIED1(static_downcast, X_static_downcast, (class))


} } // namespace pstade::egg


#endif
