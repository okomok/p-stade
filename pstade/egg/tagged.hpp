#ifndef PSTADE_EGG_TAGGED_HPP
#define PSTADE_EGG_TAGGED_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include "./ret.hpp"


namespace pstade { namespace egg {


    template<class Base, class Tag, class Strategy = boost::use_default>
    struct result_of_tagged :
        result_of_ret<Base, boost::use_default, Strategy, Tag>
    { };


    #define PSTADE_EGG_TAGGED_L PSTADE_EGG_RET_L
    #define PSTADE_EGG_TAGGED_R PSTADE_EGG_RET_R
    #define PSTADE_EGG_TAGGED(F) PSTADE_EGG_TAGGED_L F PSTADE_EGG_TAGGED_R


    // Do you need a function 'egg::tagged<...>(f)'?


    struct not_tagged;

    template<class F>
    struct tag_of
    {
        typedef not_tagged type;
    };

    template<class F>
    struct tag_of<F const> :
        tag_of<F>
    { };

    template<class F>
    struct tag_of<F volatile> :
        tag_of<F>
    { };

    template<class F>
    struct tag_of<F const volatile> :
        tag_of<F>
    { };

    template<class Base, class ResultType, class Strategy, class Tag>
    struct tag_of< function<detail::baby_ret_result<Base, ResultType, Tag>, Strategy> >
    {
        typedef Tag type;
    };


    template<class F, class Tag>
    struct has_the_tag :
        boost::is_same<typename tag_of<F>::type, Tag>
    { };


} } // namespace pstade::egg


#endif
