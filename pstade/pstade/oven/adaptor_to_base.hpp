#ifndef PSTADE_OVEN_ADAPTOR_TO_BASE_HPP
#define PSTADE_OVEN_ADAPTOR_TO_BASE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: 'iterator_cast' of Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// 'is_convertible' is too permissive?
// Meanwhile, 'iterator_cast' uses 'is_same'.
//
// Can this function be used for more generic usage?
// If ad can, give ad a better name?
//
// This implementation is slightly complicated than
// 'iterator_cast' in order to support a reference
// type as 'Base'. Any pitfalls?


#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade { namespace oven {


namespace adaptor_to_detail {


    template< class Base, class Adaptor >
    Base base_of(Adaptor const& ad)
    {
        
    }


} // namespace adaptor_to_detail

// Note:
// <pstade/const_overloaded.hpp> shows the reason
// why 'is_const' check is required.
// Also note that the 'const_overloaded' couldn't
// be used here, because 'const_overloaded' itself
// uses 'enable_if/disable_if'?
//

template< class Base, class Adaptor > inline
typename boost::enable_if<
    boost::mpl::and_<
        boost::is_convertible<Adaptor&, Base>,
        boost::mpl::not_< boost::is_const<Adaptor> >
    >,
    Base
>::type
adaptor_to(Adaptor& ad)
{
    return ad;
}

    template< class Base, class Adaptor > inline
    typename boost::enable_if<
        boost::is_convertible<Adaptor const&, Base>,
        Base
    >::type
    adaptor_to(Adaptor const& ad)
    {
        return ad;
    }


// The forward declaration of 'const' version
// seems necessary for conforming code.
template< class Base, class Adaptor > inline
typename boost::disable_if<
    boost::is_convertible<Adaptor const&, Base>,
    Base
>::type
adaptor_to(Adaptor const& ad);


template< class Base, class Adaptor > inline
typename boost::disable_if<
    boost::mpl::or_<
        boost::is_convertible<Adaptor&, Base>,
        boost::is_const<Adaptor>
    >,
    Base
>::type
adaptor_to(Adaptor& ad)
{
    return oven::adaptor_to<Base>(ad.base());
}

    template< class Base, class Adaptor > inline
    typename boost::disable_if<
        boost::is_convertible<Adaptor const&, Base>,
        Base
    >::type
    adaptor_to(Adaptor const& ad)
    {
        return oven::adaptor_to<Base>(ad.base());
    }


// Note:
// This cannot support a reference type as 'Base',
// because of the weird behavior...
//

struct adaptor_to_class
{
    template< class Base, class Adaptor >
    static Base call(Adaptor const& ad)
    {
        return oven::adaptor_to<Base>(ad);
    }
};

PSTADE_EGG_PIPABLE(to_base, egg::baby_auto<adaptor_to_class>)


} } // namespace pstade::oven


#endif
