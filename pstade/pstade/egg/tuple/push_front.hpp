#ifndef PSTADE_EGG_TUPLE_PUSH_FRONT_HPP
#define PSTADE_EGG_TUPLE_PUSH_FRONT_HPP
#include "../detail/prefix.hpp"


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


namespace pstade { namespace egg {


    namespace tuple_push_front_detail {


        template<class Bytag>
        struct little
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


    } // namespace tuple_push_front_detail


    template<class Bytag = by_perfect>
    struct X_tuple_push_front :
        function<tuple_push_front_detail::little<Bytag>, Bytag>
    { };

    typedef X_tuple_push_front<>::function_type T_tuple_push_front;
    PSTADE_POD_CONSTANT((T_tuple_push_front), tuple_push_front) = {{}};


} } // namespace pstade::egg


#endif
