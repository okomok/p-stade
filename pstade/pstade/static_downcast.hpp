#ifndef PSTADE_STATIC_DOWNCAST_HPP
#define PSTADE_STATIC_DOWNCAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/cast_function.hpp>
#include <pstade/constant.hpp>
#include <pstade/nonassignable.hpp>
#include <boost/type.hpp>


#if defined(__GNUC__)
    // Without a named object, GCC3.4.4 tries to convert 'Base' to
    // 'static_downcasted_detail::temp' using the conversion operator template.
    // I don't know why.
    #define PSTADE_STATIC_DOWNCASTED_NEEDS_NAMED_RETURN_VALUE
#endif


namespace pstade {


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


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // VC7.1

    // Workaround:
    // VC7.1 occasionally fails if using 'PSTADE_CAST_FUNCTION1'.
    // I couldn't find a minimal condition of this behavior,
    // though the unit test of 'oven::any_range' actually failed.
    // The problem seems around 'PSTADE_DEDUCED_CONST', which calls 'add_const'.
    // 'boost::result_of' fails to 'add_const' under weird situation.
    // That is to say, array type prefers 'add_const<Array>::type' to 'Array const',
    // while 'boost::result_of' prefers 'Array const' to 'add_const<Array>::type'.
    // It is a dead-end.
    // So, define this without 'PSTADE_DEDUCED_CONST'; 'Base' is never array.
    // Fortunately, this bug seems to occur only in namespace scope; class scope is fine.

    template<class Derived, class Base> static inline
    typename boost::result_of<op_static_downcast<Derived>(Base&)>::type
    static_downcast(Base& base)
    {
        return op_static_downcast<Derived>()(base);
    }

    template<class Derived, class Base> static inline
    typename boost::result_of<op_static_downcast<Derived>(Base const&)>::type
    static_downcast(Base const& base)
    {
        return op_static_downcast<Derived>()(base);
    }

#else

    PSTADE_CAST_FUNCTION1(static_downcast, op_static_downcast, 1)

#endif


    // 'PSTADE_STATIC_DOWNCASTED_NEEDS_NAMED_RETURN_VALUE' makes 'pipable' useless.
    // So we must define from scratch...


    namespace static_downcasted_detail {


        template<class Base>
        struct temp :
            private nonassignable
        {
            explicit temp(Base& base) :
                m_base(base)
            { };

            template<class Derived>
            operator Derived& () const
            {
                return op_static_downcast<Derived>()(m_base);
            }

            // No pointer-style conversion; VC7.1 doesn't work.
            // template< class Derived > operator Derived *() const;

        private:
            Base& m_base;
        };


        struct pipe :
            private boost::noncopyable
        { };


        template<class Base> inline
        temp<Base> const
        operator|(Base& base, pipe const&)
        {
        #if !defined(PSTADE_STATIC_DOWNCASTED_NEEDS_NAMED_RETURN_VALUE)
            return temp<Base>(base);
        #else
            temp<Base> nrv(base);
            return nrv;
        #endif
        }


    } // namespace static_downcasted_detail


    PSTADE_CONSTANT(static_downcasted, (static_downcasted_detail::pipe))


} // namespace pstade


#endif
