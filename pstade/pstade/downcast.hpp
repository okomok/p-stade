#ifndef PSTADE_DOWNCAST_HPP
#define PSTADE_DOWNCAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cast.hpp> // polymorphic_downcast
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/cast_function.hpp>
#include <pstade/constant.hpp>
#include <pstade/nonassignable.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // VC7.1
    // VC7.1 occasionally fails if using 'PSTADE_CAST_FUNCTION1'.
    // I couldn't find a minimal condition of this behavior,
    // though the unit test of 'oven::any_range' actually failed.
    // The problem seems around 'PSTADE_DEDUCED_CONST', which calls 'add_const'.
    // 'boost::result_of' fails to 'add_const' under weird situation.
    // That is to say, array type prefers 'add_const<Array>::type' to 'Array const',
    // while 'boost::result_of' prefers 'Array const' to 'add_const<Array>::type'.
    // It is a dead-end. Hence, We have to define this from scratch'.
    // Fortunately, this bug seems to occur only in namespace scope; class scope is fine.
    #define PSTADE_DOWNCAST_RESULT_OF_NEEDS_CONST_QUALIFIED_PARAM
#endif


#if defined(__GNUC__)
    // Without a named object, GCC3.4.4 tries to convert 'Base' to
    // 'downcasted_detail::temp' using the conversion operator template.
    #define PSTADE_DOWNCASTED_NEEDS_NAMED_RETURN_VALUE
#endif


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


#if !defined(PSTADE_DOWNCAST_RESULT_OF_NEEDS_CONST_QUALIFIED_PARAM)
    PSTADE_CAST_FUNCTION1(static_downcast, op_static_downcast, 1)
    PSTADE_CAST_FUNCTION1(polymorphic_downcast, op_polymorphic_downcast, 1)
#else
    template<class Derived, class Base> inline
    typename boost::result_of<op_static_downcast<Derived>(Base&)>::type
    static_downcast(Base& base)
    {
        return op_static_downcast<Derived>()(base);
    }

    template<class Derived, class Base> inline
    typename boost::result_of<op_polymorphic_downcast<Derived>(Base&)>::type
    polymorphic_downcast(Base& base)
    {
        return op_polymorphic_downcast<Derived>()(base);
    }
#endif


    // 'PSTADE_DOWNCASTED_NEEDS_NAMED_RETURN_VALUE' makes "./pipable.hpp" useless.
    // So we must define from scratch...


    namespace downcasted_detail {


        struct static_pipe :
            private boost::noncopyable
        { };

        struct polymorphic_pipe :
            private boost::noncopyable
        { };


        template<class Base, template<class> class F>
        struct temp :
            private nonassignable
        {
            explicit temp(Base& base) :
                m_base(base)
            { };

            template<class Derived>
            operator Derived& () const
            {
                return F<Derived>()(m_base);
            }

            // No pointer-style conversion; VC7.1 can't compile.
            // template< class Derived > operator Derived *() const;

        private:
            Base& m_base;
        };


        template<class Base> inline
        temp<Base, op_static_downcast> const
        operator|(Base& base, static_pipe const&)
        {
        #if !defined(PSTADE_DOWNCASTED_NEEDS_NAMED_RETURN_VALUE)
            return temp<Base, op_static_downcast>(base);
        #else
            temp<Base, op_static_downcast> nrv(base);
            return nrv;
        #endif
        }

        template<class Base> inline
        temp<Base, op_polymorphic_downcast> const
        operator|(Base& base, polymorphic_pipe const&)
        {
        #if !defined(PSTADE_DOWNCASTED_NEEDS_NAMED_RETURN_VALUE)
            return temp<Base, op_polymorphic_downcast>(base);
        #else
            temp<Base, op_polymorphic_downcast> nrv(base);
            return nrv;
        #endif
        }


    } // namespace downcasted_detail


    PSTADE_CONSTANT(static_downcasted, (downcasted_detail::static_pipe))
    PSTADE_CONSTANT(polymorphic_downcasted, (downcasted_detail::polymorphic_pipe))


} // namespace pstade


#endif
