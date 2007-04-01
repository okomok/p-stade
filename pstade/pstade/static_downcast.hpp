#ifndef PSTADE_STATIC_DOWNCAST_HPP
#define PSTADE_STATIC_DOWNCAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
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
// According to 8.5.3/5, the initializer must be lvalue for "bind directly".


#include <boost/cast.hpp> // polymorphic_downcast
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/cast_function.hpp>
#include <pstade/enable_if.hpp>


namespace pstade {


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


    } // namespace static_downcast_detail


    template<class Derived>
    struct op_static_downcast :
        callable< op_static_downcast<Derived> >
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


    PSTADE_CAST_FUNCTION1(static_downcast, op_static_downcast, 1)


} // namespace pstade


#endif
