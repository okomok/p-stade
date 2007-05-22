#ifndef PSTADE_OVEN_ZIPPED_WITH_HPP
#define PSTADE_OVEN_ZIPPED_WITH_HPP


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


#include <boost/utility/result_of.hpp>
#include <boost/version.hpp>
#include <pstade/fuse.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/perfect.hpp>
#include <pstade/pipable.hpp>
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
struct op_make_zipped_with :
    callable< op_make_zipped_with<Reference, Value> >
{
#if BOOST_VERSION >= 103500
    typedef op_make_fuzipped zip_;
#else
    typedef op_make_zipped   zip_;
#endif

    template< class Myself, class RangeTuple, class Function >
    struct apply :
        boost::result_of<
            op_make_transformed<Reference, Value>(
                typename boost::result_of<zip_(RangeTuple&)>::type,
                typename boost::result_of<
                    op_fuse(typename boost::result_of<op_perfect<Reference>(Function&)>::type)
                >::type
            )
        >
    { };

    template< class Result, class RangeTuple, class Function >
    Result call(RangeTuple& tup, Function& fun) const
    {
        return
            op_make_transformed<Reference, Value>()(
                zip_()(tup),
                fuse(op_perfect<Reference>()(fun))
            );
    }
};


PSTADE_CONSTANT(make_zipped_with, (op_make_zipped_with<>))
PSTADE_PIPABLE(zipped_with, (op_make_zipped_with<>))


} } // namespace pstade::oven


#endif
