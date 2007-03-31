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


#include <boost/cast.hpp> // polymorphic_downcast
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
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
#include <pstade/constant.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/provide_sig.hpp>
#include <pstade/unused.hpp>


#if defined(__GNUC__)
    // Without a named object, GCC3.4.4 tries to convert 'Base' to
    // 'to_derived_detail::temp' using the conversion operator template.
    #define PSTADE_DOWNCAST_AUTOMATIC_CONVERSION_NEEDS_NRV
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


    PSTADE_CAST_FUNCTION1(static_downcast, op_static_downcast, 1)
PSTADE_ADL_BARRIER(polymorphic_downcast) { // for 'boost'
    PSTADE_CAST_FUNCTION1(polymorphic_downcast, op_polymorphic_downcast, 1)
}


    // "./automatic.hpp" doesn't support reference conversion.
    // Also, PSTADE_DOWNCAST_AUTOMATIC_CONVERSION_NEEDS_NRV makes
    // "./callable.hpp" useless. So we must define everything from scratch...


    namespace to_derived_detail {


        // See also <boost/smart_cast.hpp>.


        template<class Base, template<class> class Cast>
        struct temp :
            private nonassignable
        {
            explicit temp(Base& base) :
                m_base(base)
            { };

            template<class Derived>
            operator Derived& () const
            {
                return Cast<Derived>()(m_base);
            }

            // No pointer-style conversion; VC7.1 can't compile.
            // template<class Derived> operator Derived *() const;

        private:
            Base& m_base;
        };


        struct op :
            provide_sig
        {

            typedef // for callable macro
                op const&
            nullary_result_type;

            op const& operator()() const
            {
                return *this;
            }

            template<class FunCall>
            struct result;

            template<class Fun, class Base>
            struct result<Fun(Base&)> :
                boost::mpl::if_< boost::is_polymorphic<typename boost::remove_cv<Base>::type>,
                     temp<Base, op_polymorphic_downcast> const,
                     temp<Base, op_static_downcast> const
                >
            { };

            template<class Base>
            typename result<void(Base&)>::type operator()(Base& base) const
            {
                typedef typename result<void(Base&)>::type result_t;

        #if !defined(PSTADE_DOWNCAST_AUTOMATIC_CONVERSION_NEEDS_NRV)
                return result_t(base);
        #else
                result_t nrv(base);
                return nrv;
        #endif
            }
        };


        template<class Base> inline
        typename boost::result_of<op(Base&)>::type
        operator|(Base& base, op const& f)
        {
        #if !defined(PSTADE_DOWNCAST_AUTOMATIC_CONVERSION_NEEDS_NRV)
            return f(base);
        #else
            unused(f);
            typename boost::result_of<op(Base&)>::type nrv(base);
            return nrv;
        #endif
        }


    } // namespace to_derived_detail


    PSTADE_CONSTANT(to_derived, (to_derived_detail::op))


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TYPE(pstade::to_derived_detail::op)


#endif
