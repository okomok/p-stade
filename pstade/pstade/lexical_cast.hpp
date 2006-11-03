#ifndef PSTADE_LEXICAL_CAST_HPP
#define PSTADE_LEXICAL_CAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/Cryolite/20061101


#include <boost/lexical_cast.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade {


namespace lexical_cast_detail {

    template< class F >
    struct apply_meta_impl :
        F
    { };

    template< class T >
    struct apply_meta_impl< boost::type<T> >
    {
        typedef T type;
    };

    template< class F >
    struct apply_meta :
        apply_meta_impl<typename boost::remove_cv<F>::type>
    { };

    struct baby
    {
        template< class Myself, class From, class To >
        struct apply :
            apply_meta<To>
        { };

        template< class Result, class From, class To >
        Result call(From const& from, To)
        {
            return boost::lexical_cast<Result>(from);
        }
    };

} // namespace lexical_cast_detail

PSTADE_EGG_FUNCTION(lexical_cast, lexical_cast_detail::baby)


struct lexical_cast_class
{
    template< class To, class From >
    static To call(From const& from)
    {
        return boost::lexical_cast<To>(from);
    }
};

PSTADE_EGG_FUNCTION(lexical, egg::baby_auto<lexical_cast_class>)
PSTADE_EGG_PIPABLE(lexicalized, egg::baby_auto<lexical_cast_class>)


} // namespace pstade


#endif
