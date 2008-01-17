#ifndef PSTADE_EGG_TAGGED_HPP
#define PSTADE_EGG_TAGGED_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>
#include "./return.hpp"


namespace pstade { namespace egg {


    template<class Base, class Tag, class Strategy = boost::use_default>
    struct result_of_tagged :
        result_of_return<Base, boost::use_default, Strategy, Tag>
    { };


    #define PSTADE_EGG_TAGGED_L PSTADE_EGG_RETURN_L
    #define PSTADE_EGG_TAGGED_R PSTADE_EGG_RETURN_R
    #define PSTADE_EGG_TAGGED(F) PSTADE_EGG_TAGGED_L F PSTADE_EGG_TAGGED_R


    template<class Tag, class Strategy = boost::use_default>
    struct X_tagged :
        X_return<boost::use_default, Strategy, Tag>
    { };

    template<class Tag, class Base> inline
    typename result_of<X_tagged<Tag>(Base&)>::type tagged(Base f)
    {
        return X_tagged<Tag>()(f);
    }


    struct no_tag_tag;

    template<class F>
    struct tag_of
    {
        typedef no_tag_tag type;
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
    struct tag_of< function<detail::little_return_result<Base, ResultType, Strategy, Tag>, Strategy> >
    {
        typedef Tag type;
    };


    template<class F, class Tag>
    struct is_tagged_with :
        boost::is_same<typename tag_of<F>::type, Tag>
    { };


} } // namespace pstade::egg


#endif
