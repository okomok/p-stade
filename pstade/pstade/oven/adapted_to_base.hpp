#ifndef PSTADE_OVEN_ADAPTED_TO_BASE_HPP
#define PSTADE_OVEN_ADAPTED_TO_BASE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
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
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/automatic.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/enable_if.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class Base, class Adapted > inline
Base adapted_to(Adapted& ad,
    typename enable_if<
        boost::mpl::and_<
            boost::is_convertible<Adapted&, Base>,
            boost::mpl::not_< boost::is_const<Adapted> > // seems needed.
        >
    >::type = 0)
{
    return ad;
}

template< class Base, class Adapted > inline
Base adapted_to(Adapted const& ad,
    typename enable_if< boost::is_convertible<Adapted const&, Base> >::type = 0)
{
    return ad;
}

template< class Base, class Adapted > inline
Base adapted_to(Adapted const& ad,
    typename disable_if<boost::is_convertible<Adapted const&, Base> >::type = 0)
{
    return oven::adapted_to<Base>(ad.base());
}


// This cannot support a reference type as 'Base',
// because of the weird compiler behavior...

template< class To >
struct op_adapted_to
{
    typedef To result_type;

    template< class From >
    To operator()(From& from) const
    {
        return oven::adapted_to<To>(from);
    }

    template< class From >
    To operator()(From const& from) const
    {
        return oven::adapted_to<To>(from);
    }
};

PSTADE_AUXILIARY0(to_base, (automatic< op_adapted_to<boost::mpl::_1> >))


// for range
//

template< class To >
struct op_adapted_range_to
{
    typedef To result_type;

    template< class From >
    To aux(From& from) const
    {
        typedef typename range_iterator<To>::type iter_t;
        return To(
            op_adapted_to<iter_t>()(boost::begin(from)),
            op_adapted_to<iter_t>()(boost::end(from))
        );
    }

    template< class From >
    To operator()(From& from) const
    {
        return aux(from);
    }

    template< class From >
    To operator()(From const& from) const
    {
        return aux(from);
    }
};

template< class To, class From > inline
typename boost::result_of<op_adapted_range_to<To>(From&)>::type
adapted_range_to(From& from PSTADE_CONST_OVERLOADED(From))
{
    return op_adapted_range_to<To>()(from);
}

template< class To, class From > inline
typename boost::result_of<op_adapted_range_to<To>(PSTADE_DEDUCED_CONST(From)&)>::type
adapted_range_to(From const& from)
{
    return op_adapted_range_to<To>()(from);
}

PSTADE_AUXILIARY0(to_base_range, (automatic< op_adapted_range_to<boost::mpl::_1> >))


} } // namespace pstade::oven


#endif
