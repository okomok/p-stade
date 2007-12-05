#ifndef PSTADE_SAUSAGE_CUSTOMIZATION_HPP
#define PSTADE_SAUSAGE_CUSTOMIZATION_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/oven/range_reference.hpp>


namespace pstade { namespace sausage {


template< class T, class = void >
struct customization;


template< class T >
struct which :
    boost::enable_if<T>
{ };


// predefined customizations
//

PSTADE_HAS_TYPE(pstade_sausage_enumerate_argument_type)

template< class T >
struct customization<T, typename which< has_pstade_sausage_enumerate_argument_type<T> >::type>
{
    template< class HasType >
    struct enumerate_argument
    {
        // insensitive to const-qualification
        typedef typename HasType::pstade_sausage_enumerate_argument_type type;
    };

    template< class Argument, class HasType, class EnumFtor >
    EnumFtor enumerate(HasType& x, EnumFtor fun)
    {
        return x.template pstade_sausage_enumerate<Argument>(fun);
    }
};


template< class T, class = void >
struct as_boost_range : // for overlapping enabler conditions
    apple::is_boost_range<T>
{ };

template< class T >
struct customization<T, typename which< as_boost_range<T> >::type>
{
    template< class Range >
    struct enumerate_argument :
        oven::range_reference<Range>
    { };

    template< class Argument, class Range, class EnumFtor >
    EnumFtor enumerate(Range& rng, EnumFtor fun)
    {
        BOOST_FOREACH (Argument arg, rng) {
            if (!fun(arg))
                break;
        }

        return fun;
    }
};


} } // namespace pstade::sausage


#endif
