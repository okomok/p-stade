#ifndef PSTADE_OVEN_ZIPPED_WITH_HPP
#define PSTADE_OVEN_ZIPPED_WITH_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// If you have a function taking a tuple,
// you can use of course 'rng|zipped|transformed(f)'.


#include <boost/version.hpp>
#include <pstade/egg/fuse.hpp>
#include <pstade/egg/perfect.hpp>
#include <pstade/result_of.hpp>
#include "./detail/baby_to_adaptor.hpp"
#include "./fuzipped.hpp"
#include "./transformed.hpp"
#if BOOST_VERSION >= 103500
    // Lets 'boost::tuple' be FusionSequence for 'op_make_fuzipped'.
    #include <boost/fusion/sequence/adapted/boost_tuple.hpp>
#else
    #include "./zipped.hpp"
#endif


namespace pstade { namespace oven {


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct tp_make_zipped_with
{
#if BOOST_VERSION >= 103500
    typedef op_make_fuzipped zip_;
#else
    typedef op_make_zipped   zip_;
#endif

    struct baby
    {
        template< class Myself, class RangeTuple, class Function >
        struct apply :
            result_of<
                xp_make_transformed<Reference, Value>(
                    typename result_of<zip_(RangeTuple&)>::type,
                    typename result_of<
                        egg::op_fuse(typename result_of<egg::xp_perfect<Reference>(Function&)>::type)
                    >::type
                )
            >
        { };

        template< class Result, class RangeTuple, class Function >
        Result call(RangeTuple& tup, Function& fun) const
        {
            return
                xp_make_transformed<Reference, Value>()(
                    zip_()(tup),
                    egg::fuse(egg::xp_perfect<Reference>()(fun))
                );
        }
    };

    typedef egg::function<baby> type;
};


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct xp_make_zipped_with :
    tp_make_zipped_with<Reference, Value>::type
{ };


PSTADE_OVEN_BABY_TO_ADAPTOR(zipped_with, (tp_make_zipped_with<>::baby))


} } // namespace pstade::oven


#endif
