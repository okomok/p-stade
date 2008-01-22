#ifndef PSTADE_EGG_DETAIL_PUSH_FRONT_HPP
#define PSTADE_EGG_DETAIL_PUSH_FRONT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_perfect.hpp"
#include "../forward.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Bytag>
    struct little_push_front
    {
        template<class Myself, class Tuple, class A>
        struct apply
        {
            typedef
                boost::tuples::cons<
                    typename result_of_forward<Bytag, A>::type,
                    typename boost::remove_cv<Tuple>::type
                >
            type;
        };

        template<class Result, class Tuple, class A>
        Result call(Tuple& t, A& a) const
        {
            return Result(a, t);
        }
    };


    template<class Bytag = by_perfect>
    struct X_push_front :
        function<little_push_front<Bytag>, Bytag>
    { };

    typedef X_push_front<>::function_type T_push_front;
    PSTADE_POD_CONSTANT((T_push_front), push_front) = {{}};


} } } // namespace pstade::egg::detail


#endif
