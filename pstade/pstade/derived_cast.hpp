#ifndef PSTADE_DERIVED_CAST_HPP
#define PSTADE_DERIVED_CAST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/nonassignable.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    // The weird VC7.1 fails the second call of pointer-style auto-conversion.
    // VC7.1 maybe saves the conversion operator of the first call,
    // and then makes the ambiguity error by the second call.
    #define PSTADE_DERIVED_CAST_NO_POINTER_DERIVED
#endif


namespace pstade {


template< class DerivedT, class BaseT > inline
DerivedT& derived_cast(BaseT& base)
{
    BOOST_MPL_ASSERT((boost::is_base_of<BaseT, DerivedT>));
    return static_cast<DerivedT&>(base);
}


namespace derived_cast_detail {


    template< class BaseT >
    struct temp :
        private nonassignable
    {
        explicit temp(BaseT& base) :
            m_base(base)
        { };

        template< class DerivedT >
        operator DerivedT& () const
        {
            return pstade::derived_cast<DerivedT>(m_base);
        }

#if !defined(PSTADE_DERIVED_CAST_NO_POINTER_DERIVED)
        template< class DerivedT >
        operator DerivedT *() const
        {
            return boost::addressof( pstade::derived_cast<DerivedT>(m_base) );
        }
#endif

    private:
        BaseT& m_base;
    };


} // namespace derived_cast_detail


template< class BaseT > inline
derived_cast_detail::temp<BaseT> const
derived(BaseT& base)
{
    // return derived_cast_detail::temp<BaseT>(base);

    // Workaround:
    // If 'tmp' is missing like above, GCC3.4.4 tries to convert 'temp' to
    // itself using the first conversion operator template.
    // For its constructor? I don't know why.
    derived_cast_detail::temp<BaseT> tmp(base);
    return tmp;
}


} // namespace pstade


#endif
