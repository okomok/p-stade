#ifndef PSTADE_EGG_DETAIL_TUPLE_PREPEND_HPP
#define PSTADE_EGG_DETAIL_TUPLE_PREPEND_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/derived_from.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_const.hpp>
#include "../forward.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Bytag>
    struct little_tuple_prepend
    {
        template<class Me, class Tuple, class A>
        struct apply
        {
            typedef
                boost::tuples::cons<
                    typename result_of_forward<Bytag, A>::type,
                    typename boost::remove_const<Tuple>::type
                >
            type;
        };

        template<class Re, class Tuple, class A>
        Re call(Tuple& t, A& a) const
        {
            return Re(a, t);
        }
    };

    template<class Bytag>
    struct X_tuple_prepend : derived_from<
        function<little_tuple_prepend<Bytag>, Bytag>
    >
    { };


} } } // namespace pstade::egg::detail


#endif
