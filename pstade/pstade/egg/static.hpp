#ifndef PSTADE_EGG_STATIC_HPP
#define PSTADE_EGG_STATIC_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <pstade/result_of.hpp>
#include "./by_perfect.hpp"
#include "./detail/mpl_placeholders.hpp" // inclusion guaranteed
#include "./detail/tuple_fuse.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace static_detail {


        template<class Fun>
        struct little
        {
            template<class Me, class Args>
            struct apply :
                result_of<
                    typename result_of<detail::T_tuple_fuse(Fun)>::type(Args&)
                >
            { };

            template<class Re, class Args>
            Re call(Args& args) const
            {
                return detail::tuple_fuse(Fun())(args);
            }
        };


    } // namespace static_detail


    template<class Expr, class Strategy = by_perfect>
    struct static_ :
        variadic<
            static_detail::little<typename boost::mpl::apply1<Expr, Strategy>::type>,
            Strategy,
            boost::use_default,
            use_nullary_result
        >
    { };

    #define PSTADE_EGG_STATIC() PSTADE_EGG_VARIADIC({})


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
