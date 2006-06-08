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
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/utility/addressof.hpp>


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
    BOOST_STATIC_ASSERT((boost::is_base_of<BaseT, DerivedT>::value));

    return static_cast<DerivedT&>(base);
}


namespace derived_cast_detail {


    template< class BaseT >
    struct temporary
    {
        explicit temporary(BaseT& base) :
            m_pbase(boost::addressof(base))
        { };

        template< class DerivedT >
        operator DerivedT& () const
        {
            return pstade::derived_cast<DerivedT>(*m_pbase);
        }

#if !defined(PSTADE_DERIVED_CAST_NO_POINTER_DERIVED)
        template< class DerivedT >
        operator DerivedT *() const
        {
            return boost::addressof( pstade::derived_cast<DerivedT>(*m_pbase) );
        }
#endif

    private:
        BaseT *m_pbase;
    };


} // namespace derived_cast_detail


template< class BaseT > inline const
derived_cast_detail::temporary<BaseT> derived(BaseT& base)
{
    // return derived_cast_detail::temporary<BaseT>(base);

    // Workaround:
    //   If 'tmp' is missing like above, GCC3.4.4 tries to convert 'temporary' to
    //   itself using the first conversion operator template.
    //   For its constructor? I don't know why.

    derived_cast_detail::temporary<BaseT> tmp(base);
    return tmp;
}


} // namespace pstade


#endif
