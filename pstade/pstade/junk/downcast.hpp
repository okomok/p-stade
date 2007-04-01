#ifndef PSTADE_DOWNCAST_HPP
#define PSTADE_DOWNCAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// RTTI(/GR option) is required in debug mode.
// 'downcast' can't support virtual-base downcast.
//
// 'Derived& d = automatic_downcast(b);' seems impossible.
// According to 8.5.3/5, the initializer must be lvalue for "bind directly".


#include <boost/cast.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/cast_function.hpp>


namespace pstade {


    namespace downcast_detail {


        template<class Reference>
        struct to_pointer
        {
            typedef typename
                boost::remove_reference<Reference>::type *
            type;
        };


    } // namespace downcast_detail


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
            BOOST_MPL_ASSERT((boost::is_base_of<
                typename boost::remove_cv<Base>::type,
                typename boost::remove_cv<Derived>::type
            >));

            return static_cast<Result>(base);
        }
    };

    template<class Derived>
    struct op_polymorphic_downcast :
        callable< op_polymorphic_downcast<Derived> >
    {
        template<class Myself, class Base>
        struct apply :
            affect<Base&, Derived>
        { };

        template<class Result, class Base>
        Result call(Base& base) const
        {
            return *boost::polymorphic_downcast<
                typename downcast_detail::to_pointer<Result>::type
            >(boost::addressof(base));
        }
    };

    // This could be called from 'downcast' with "has_virtual_base".
    template<class Derived>
    struct op_virtual_downcast :
        callable< op_virtual_downcast<Derived> >
    {
        template<class Myself, class Base>
        struct apply :
            affect<Base&, Derived>
        { };

        template<class Result, class Base>
        Result call(Base& base) const
        {
            return *boost::polymorphic_cast<
                typename downcast_detail::to_pointer<Result>::type
            >(boost::addressof(base));
        }
    };


    // This is the same as 'boost::smart_cast' without "crosscast".
    template<class Derived>
    struct op_downcast :
        callable< op_downcast<Derived> >
    {
        template<class Myself, class Base>
        struct apply
        {
            typedef typename
                boost::mpl::if_< boost::is_polymorphic<typename boost::remove_cv<Base>::type>,
                    op_polymorphic_downcast<Derived>,
                    op_static_downcast<Derived>
                >::type
            op_t;

            typedef typename
                boost::result_of<op_t(Base&)>::type
            type;
        };

        template<class Result, class Base>
        Result call(Base& base) const
        {
            return typename apply<void, Base>::op_t()(base);
        }
    };


    PSTADE_CAST_FUNCTION1(static_downcast, op_static_downcast, 1)
PSTADE_ADL_BARRIER(polymorphic_downcast) { // for 'boost'
    PSTADE_CAST_FUNCTION1(polymorphic_downcast, op_polymorphic_downcast, 1)
}
    PSTADE_CAST_FUNCTION1(downcast, op_downcast, 1)


} // namespace pstade


#endif
