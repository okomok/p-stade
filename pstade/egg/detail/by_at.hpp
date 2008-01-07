#ifndef PSTADE_EGG_DETAIL_BY_AT_HPP
#define PSTADE_EGG_DETAIL_BY_AT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/at.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <pstade/has_xxx.hpp>
#include "../function_fwd.hpp"


namespace pstade { namespace egg { namespace detail {


    namespace by_at_detail{
        PSTADE_HAS_TYPE(type)
    }


    template<class Strategy, int N>
    struct get_by_at
    {
        typedef typename Strategy::type seq_t;
        typedef typename boost::mpl::at_c<seq_t, N>::type type;
    };


    template<class Strategy, int N>
    struct by_at :
        boost::mpl::eval_if< by_at_detail::has_type<Strategy>,
            get_by_at<Strategy, N>,
            boost::mpl::identity<by_perfect>
        >
    { };

    template<int N>
    struct by_at<by_perfect, N>
    {
        typedef by_perfect type;
    };

    template<int N>
    struct by_at<by_ref, N>
    {
        typedef by_ref type;
    };

    template<int N>
    struct by_at<by_cref, N>
    {
        typedef by_cref type;
    };

    template<int N>
    struct by_at<by_value, N>
    {
        typedef by_value type;
    };


} } } // namespace pstade::egg::detail


#endif
