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


#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade { namespace oven {


template< class Base, class Adaptor > inline
typename boost::enable_if<boost::is_convertible<Adaptor, Base>,
Base const>::type
adaptor_to(Adaptor const& it)
{
    return it;
}


template< class Base, class Adaptor > inline
typename boost::disable_if<boost::is_convertible<Adaptor, Base>,
Base const>::type
adaptor_to(Adaptor const& it)
{
    return oven::adaptor_to<Base>(it.base());
}


struct adaptor_to_class
{
    template< class Base, class Adaptor >
    static Base call(Adaptor const& it)
    {
        return oven::adaptor_to<Base>(it);
    }
};


PSTADE_EGG_PIPABLE(to_base, egg::baby_auto<adaptor_to_class>)


} } // namespace pstade::oven


#endif
