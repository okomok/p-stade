#ifndef PSTADE_EGG_DETAIL_BYTAG_AT_HPP
#define PSTADE_EGG_DETAIL_BYTAG_AT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/static_assert.hpp>
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

    template<int Arity, int Index>
    struct bytag_at_impl<by_perfect, Arity, Index>
    {
        BOOST_STATIC_ASSERT(Arity <= PSTADE_EGG_MAX_ARITY);
        typedef by_perfect type;
    };

    template<int Arity, int Index>
    struct bytag_at_impl<by_ref, Arity, Index>
    {
        BOOST_STATIC_ASSERT(Arity <= PSTADE_EGG_MAX_LINEAR_ARITY);
        typedef by_ref type;
    };

    template<int Arity, int Index>
    struct bytag_at_impl<by_cref, Arity, Index>
    {
        BOOST_STATIC_ASSERT(Arity <= PSTADE_EGG_MAX_LINEAR_ARITY);
        typedef by_cref type;
    };

    template<int Arity, int Index>
    struct bytag_at_impl<by_value, Arity, Index>
    {
        BOOST_STATIC_ASSERT(Arity <= PSTADE_EGG_MAX_LINEAR_ARITY);
        typedef by_value type;
    };


    template<class Strategy, int Arity, int Index>
    struct bytag_at
    {
        BOOST_STATIC_ASSERT(Index < Arity);
        typedef typename bytag_at_impl<Strategy, Arity, Index>::type type;
        BOOST_STATIC_ASSERT(is_bytag<type>::value);
    };


} } } // namespace pstade::egg::detail


#endif
