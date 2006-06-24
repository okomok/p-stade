#ifndef PSTADE_OVEN_RANGE_ADAPTOR_HPP
#define PSTADE_OVEN_RANGE_ADAPTOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Why not: 'boost::result_of'
//
// An array reference doesn't work under weird VC++7.1.


#include <boost/utility/addressof.hpp> // for lambda functors
#include <boost/type_traits/add_const.hpp>
#include <pstade/egg/baby_result_type.hpp>
#include <pstade/comma_protect.hpp>
#include <pstade/instance.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace oven { namespace range_adaptor_detail {


    // 0ary
    //
    template< class BabyAdaptor >
    struct adaptor0
    { };


    template< class Range, class BabyAdaptor > inline
    typename egg::baby_result1<BabyAdaptor, Range>::type
    operator|(Range& rng, adaptor0<BabyAdaptor> ad)
    {
        pstade::unused(ad);
        return egg::baby_call<BabyAdaptor>(rng);
    }

    template< class Range, class BabyAdaptor > inline
    typename egg::baby_result1<BabyAdaptor, typename boost::add_const<Range>::type>::type
    operator|(const Range& rng, adaptor0<BabyAdaptor> ad)
    {
        pstade::unused(ad);
        return egg::baby_call<BabyAdaptor>(rng);
    }


    // 1ary
    //
    template< class BabyAdaptor, class A0 >
    struct adaptor1
    {
        explicit adaptor1(A0& a0) :
            m_pa0(boost::addressof(a0))
        { }

        A0 *m_pa0;
    };


    template< class Range, class BabyAdaptor, class A0 > inline
    typename egg::baby_result2<BabyAdaptor, Range, A0>::type
    operator|(Range& rng, adaptor1<BabyAdaptor, A0> ad)
    {
        return egg::baby_call<BabyAdaptor>(rng, *ad.m_pa0);
    }

        template< class Range, class BabyAdaptor, class A0 > inline
        typename egg::baby_result2<BabyAdaptor, typename boost::add_const<Range>::type, A0>::type
        operator|(const Range& rng, adaptor1<BabyAdaptor, A0> ad)
        {
            return egg::baby_call<BabyAdaptor>(rng, *ad.m_pa0);
        }


    // 2ary
    //
    template< class BabyAdaptor, class A0, class A1 >
    struct adaptor2
    {
        explicit adaptor2(A0& a0, A1& a1) :
            m_pa0(boost::addressof(a0)), m_pa1(boost::addressof(a1))
        { }

        A0 *m_pa0;
        A1 *m_pa1;
    };


    template< class Range, class BabyAdaptor, class A0, class A1 > inline
    typename egg::baby_result3<BabyAdaptor, Range, A0, A1>::type
    operator|(Range& rng, adaptor2<BabyAdaptor, A0, A1> ad)
    {
        return egg::baby_call<BabyAdaptor>(rng, *ad.m_pa0, *ad.m_pa1);
    }

        template< class Range, class BabyAdaptor, class A0, class A1 > inline
        typename egg::baby_result3<BabyAdaptor, typename boost::add_const<Range>::type, A0, A1>::type
        operator|(const Range& rng, adaptor2<BabyAdaptor, A0, A1> ad)
        {
            return egg::baby_call<BabyAdaptor>(rng, *ad.m_pa0, *ad.m_pa1);
        }


    // 3ary
    //
    template< class BabyAdaptor, class A0, class A1, class A2 >
    struct adaptor3
    {
        explicit adaptor3(A0& a0, A1& a1, A2& a2) :
            m_pa0(boost::addressof(a0)), m_pa1(boost::addressof(a1)), m_pa2(boost::addressof(a2))
        { }

        A0 *m_pa0;
        A1 *m_pa1;
        A2 *m_pa2;
    };


    template< class Range, class BabyAdaptor, class A0, class A1, class A2 > inline
    typename egg::baby_result4<BabyAdaptor, Range, A0, A1, A2>::type
    operator|(Range& rng, adaptor3<BabyAdaptor, A0, A1, A2> ad)
    {
        return egg::baby_call<BabyAdaptor>(rng, *ad.m_pa0, *ad.m_pa1, *ad.m_pa2);
    }

        template< class Range, class BabyAdaptor, class A0, class A1, class A2 > inline
        typename egg::baby_result4<BabyAdaptor, typename boost::add_const<Range>::type, A0, A1, A2>::type
        operator|(const Range& rng, adaptor3<BabyAdaptor, A0, A1, A2> ad)
        {
            return egg::baby_call<BabyAdaptor>(rng, *ad.m_pa0, *ad.m_pa1, *ad.m_pa2);
        }


} } } // namespace pstade::oven::range_adaptor_detail


#include "./detail/adaptor.hpp"

/*
template< class BabyAdaptor >
struct range_adaptor
{
    // 0ary
    //
    range_adaptor_detail::adaptor0<BabyAdaptor>
    operator()() const
    {
        return range_adaptor_detail::adaptor0<BabyAdaptor
        >();
    }

    // 1ary
    //
    template< class A0 >
    range_adaptor_detail::adaptor1<BabyAdaptor,
        A0
    >
    operator()(
        A0& a0
    ) const
    {
        return range_adaptor_detail::adaptor1<BabyAdaptor,
            A0
        >(a0);
    }

    template< class A0 >
    range_adaptor_detail::adaptor1<BabyAdaptor,
        typename boost::add_const<A0>::type
    >
    operator()(
        const A0& a0
    ) const
    {
        return range_adaptor_detail::adaptor1<BabyAdaptor,
            typename boost::add_const<A0>::type
        >(a0);
    }

    // 2ary
    //

    // ...
};
*/


namespace pstade { namespace oven {


// passed as is
//
template< class Range, class BabyAdaptor > inline
typename egg::baby_result1<BabyAdaptor, Range>::type
operator|(Range& rng, range_adaptor<BabyAdaptor> ad)
{
    pstade::unused(ad);
    return egg::baby_call<BabyAdaptor>(rng);
}

template< class Range, class BabyAdaptor > inline
typename egg::baby_result1<BabyAdaptor, typename boost::add_const<Range>::type>::type
operator|(const Range& rng, range_adaptor<BabyAdaptor> ad)
{
    pstade::unused(ad);
    return egg::baby_call<BabyAdaptor>(rng);
}


} } // namespace pstade::oven


#define PSTADE_OVEN_RANGE_ADAPTOR(Name, Baby) \
    PSTADE_INSTANCE( \
        const pstade::oven::range_adaptor< pstade::comma_protect<void(Baby)>::type >, \
        Name, value \
    ) \
/**/


#endif
