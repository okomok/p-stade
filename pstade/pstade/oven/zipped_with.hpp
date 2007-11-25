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
#include <pstade/egg/ret.hpp>
#include <pstade/result_of.hpp>
#include "./detail/baby_to_adaptor.hpp"
#include "./transformed.hpp"
#if BOOST_VERSION >= 103500
    // Lets 'boost::tuple' be FusionSequence for 'T_make_fuzipped'.
    #include <boost/fusion/include/boost_tuple.hpp>
    #include "./fuzipped.hpp"
#else
    #include "./zipped.hpp"
#endif


namespace pstade { namespace oven {


namespace zipped_with_detail {


    template< class Reference, class Value >
    struct baby
    {
#if BOOST_VERSION >= 103500
        typedef T_make_fuzipped zip_;
#else
        typedef T_make_zipped   zip_;
#endif

        typedef egg::X_ret< boost::mpl::always<Reference> > ret_Reference;

        template< class Myself, class RangeTuple, class Function >
        struct apply :
            result_of<
                X_make_transformed<Reference, Value>(
                    typename result_of<zip_(RangeTuple&)>::type,
                    typename result_of<
                        egg::T_fuse(typename result_of<ret_Reference(Function&)>::type)
                    >::type
                )
            >
        { };

        template< class Result, class RangeTuple, class Function >
        Result call(RangeTuple& tup, Function& fun) const
        {
            return
                X_make_transformed<Reference, Value>()(
                    zip_()(tup),
                    egg::fuse(ret_Reference()(fun))
                );
        }
    };


} // namespace zipped_with_detail


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct X_make_zipped_with :
    egg::function< zipped_with_detail::baby<Reference, Value> >
{ };


PSTADE_OVEN_BABY_TO_ADAPTOR(zipped_with, (X_make_zipped_with<>::baby_type))


} } // namespace pstade::oven


#endif
