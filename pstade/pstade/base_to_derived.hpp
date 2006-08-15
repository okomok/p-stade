#ifndef PSTADE_BASE_TO_DERIVED_HPP
#define PSTADE_BASE_TO_DERIVED_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/instance.hpp>
#include <pstade/nonassignable.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    // The weird VC7.1 fails the second call of pointer-style auto-conversion.
    // VC7.1 maybe saves the conversion operator of the first call,
    // and then makes the ambiguity error by the second call.
    #define PSTADE_TO_DERIVED_NO_POINTER_CONVERSION
#endif


#if defined(__GNUC__)
    // Without a named object, GCC3.4.4 tries to convert 'Base' to
    // 'to_derived_detail::temp' using the conversion operator template.
    // I don't know why.
    #define PSTADE_TO_DERIVED_NEEDS_NAMED_RETURN_VALUE
#endif


namespace pstade {


template< class Derived, class Base > inline
Derived& base_to(Base& base)
{
    BOOST_MPL_ASSERT((boost::is_base_of<Base, Derived>));
    return static_cast<Derived&>(base);
}


// Note:
// 'PSTADE_TO_DERIVED_NEEDS_NAMED_RETURN_VALUE' makes Egg useless.
//

namespace to_derived_detail {


    template< class Base >
    struct temp :
        private nonassignable
    {
        explicit temp(Base& base) :
            m_base(base)
        { };

        template< class Derived >
        operator Derived& () const
        {
            return pstade::base_to<Derived>(m_base);
        }

    #if !defined(PSTADE_TO_DERIVED_NO_POINTER_CONVERSION)
        template< class Derived >
        operator Derived *() const
        {
            return boost::addressof( pstade::base_to<Derived>(m_base) );
        }
    #endif

    private:
        Base& m_base;
    };


    struct pipe :
        private boost::noncopyable
    { };


    template< class Base > inline
    temp<Base> const
    operator|(Base& base, pipe const&)
    {
    #if !defined(PSTADE_TO_DERIVED_NEEDS_NAMED_RETURN_VALUE)
        return temp<Base>(base);
    #else
        temp<Base> tmp(base);
        return tmp;
    #endif
    }


} // namespace to_derived_detail


PSTADE_INSTANCE(to_derived_detail::pipe const, to_derived, value)


} // namespace pstade


#endif
