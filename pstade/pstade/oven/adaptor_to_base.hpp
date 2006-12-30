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
// If it can, give it a better name?
//
// This implementation is slightly complicated than
// 'iterator_cast' in order to support a reference
// type as 'Base'. Any pitfalls?


#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/auto_castable.hpp>
#include <pstade/constant.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pipable.hpp>


namespace pstade { namespace oven {


// Note:
// <pstade/const_overloaded.hpp> shows the reason
// why 'is_const' check is necessary.
// Also note that the 'const_overloaded' couldn't
// be used here, because 'const_overloaded' itself
// uses 'disable_if'.
//

template< class Base, class Adaptor > inline
Base adaptor_to(Adaptor& ad,
    typename enable_if<
        boost::mpl::and_<
            boost::is_convertible<Adaptor&, Base>,
            boost::mpl::not_< boost::is_const<Adaptor> >
        >
    >::type = 0)
{
    return ad;
}

template< class Base, class Adaptor > inline
Base adaptor_to(Adaptor const& ad,
    typename enable_if< boost::is_convertible<Adaptor const&, Base> >::type = 0)
{
    return ad;
}

template< class Base, class Adaptor > inline
Base adaptor_to(Adaptor const& ad,
    typename disable_if<boost::is_convertible<Adaptor const&, Base> >::type = 0)
{
    return oven::adaptor_to<Base>(ad.base());
}


// Note:
// This cannot support a reference type as 'Base',
// because of the weird compiler behavior...
//

template< class To >
struct op_adaptor_to
{
    typedef To result_type;

    template< class From >
    To operator()(From& from) const
    {
        return oven::adaptor_to<To>(from);
    }

    template< class From >
    To operator()(From const& from) const
    {
        return oven::adaptor_to<To>(from);
    }
};

PSTADE_PIPABLE(to_base, (auto_castable< op_adaptor_to<boost::mpl::_1> >))


} } // namespace pstade::oven


#endif
