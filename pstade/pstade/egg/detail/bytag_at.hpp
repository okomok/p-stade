#ifndef PSTADE_EGG_DETAIL_BYTAG_AT_HPP
#define PSTADE_EGG_DETAIL_BYTAG_AT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/remove_const.hpp>
#include "../config.hpp"
#include "../function_fwd.hpp"
#include "./is_bytag.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Strategy, int Arity, int Index>
    struct bytag_at_impl :
        Strategy::template apply<
            Strategy,
            // must be type parameter for MetafunctionClass.
            boost::mpl::int_<Arity>,
            boost::mpl::int_<Index>
        >
    { };


    template<class Bytag, int Arity>
    struct bytag_identity;

    template<int Arity>
    struct bytag_identity<by_perfect, Arity>
    {
        BOOST_STATIC_ASSERT(Arity <= PSTADE_EGG_MAX_ARITY);
        typedef by_perfect type;
    };

    template<int Arity>
    struct bytag_identity<by_ref, Arity>
    {
        BOOST_STATIC_ASSERT(Arity <= PSTADE_EGG_MAX_LINEAR_ARITY);
        typedef by_ref type;
    };

    template<int Arity>
    struct bytag_identity<by_cref, Arity>
    {
        BOOST_STATIC_ASSERT(Arity <= PSTADE_EGG_MAX_LINEAR_ARITY);
        typedef by_cref type;
    };

    template<int Arity>
    struct bytag_identity<by_value, Arity>
    {
        BOOST_STATIC_ASSERT(Arity <= PSTADE_EGG_MAX_LINEAR_ARITY);
        typedef by_value type;
    };


    template<class Strategy, int Arity, int Index>
    struct bytag_at :
        boost::mpl::eval_if< is_bytag<Strategy>,
            bytag_identity<typename boost::remove_const<Strategy>::type, Arity>, // no volatile specializations yet.
            bytag_at_impl<Strategy, Arity, Index>
        >
    {
        BOOST_STATIC_ASSERT(0 <= Index); 
        BOOST_STATIC_ASSERT(Index < Arity); 
    };


} } } // namespace pstade::egg::detail


#endif
