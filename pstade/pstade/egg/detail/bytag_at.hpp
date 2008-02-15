#ifndef PSTADE_EGG_DETAIL_BYTAG_AT_HPP
#define PSTADE_EGG_DETAIL_BYTAG_AT_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>


namespace pstade { namespace egg { namespace detail {


    template<class Strategy, int Arity, int Index>
    struct bytag_at :
        Strategy::template apply<
            Strategy,
            boost::mpl::int_<Arity>,
            boost::mpl::int_<Index>
        >
    { };


} } } // namespace pstade::egg::detail


#endif
