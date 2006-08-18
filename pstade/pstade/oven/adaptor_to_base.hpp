#ifndef PSTADE_OVEN_ADAPTOR_TO_BASE_HPP
#define PSTADE_OVEN_ADAPTOR_TO_BASE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: 'iterator_cast' of Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/nonassignable.hpp>


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


namespace to_base_detail {


    template< class Adaptor >
    struct temp :
        private nonassignable
    {
        explicit temp(Adaptor& it) :
            m_it(it)
        { }

        template< class Base >
        operator Base() const
        {
            return oven::adaptor_to<Base>(m_it);
        }

    private:
        Adaptor& m_it;
    };


    struct baby
    {
        template< class Unused, class Adaptor >
        struct result
        {
            typedef temp<Adaptor> const type;
        };

        template< class Result, class Adaptor >
        Result call(Adaptor& it)
        {
            return Result(it);
        }
    };


} // namespace to_base_detail


PSTADE_EGG_PIPABLE(to_base, to_base_detail::baby)


} } // namespace pstade::oven


#endif
