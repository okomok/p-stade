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
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/result_of.hpp>
#include "./detail/unspecified.hpp"
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
    typename result_of<X_tagged<Tag>(Base&)>::type tagged(Base base)
    {
        return X_tagged<Tag>()(base);
    }


    namespace tag_of_detail {


        template<class F>
        struct aux_
        {
            typedef unspecified type;
        };

        template<class Base, class Return, class Strategy, class Tag>
        struct aux_< function<detail::little_return_result<Base, Return, Strategy, Tag>, Strategy> >
        {
            typedef Tag type;
        };


    } // namespace tag_of_detail


    template<class F>
    struct tag_of :
        tag_of_detail::aux_<typename boost::remove_cv<F>::type>
    { };


    template<class F, class Tag>
    struct is_tagged_with :
        boost::is_same<typename tag_of<F>::type, Tag>
    { };


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
