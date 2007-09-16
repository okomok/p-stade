#ifndef PSTADE_EGG_KEYWORD_HPP
#define PSTADE_EGG_KEYWORD_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/enable_if.hpp>
#include "./detail/named_arg.hpp"


namespace pstade { namespace egg {


    namespace keyword_detail {

        struct default_tag;

    }


    template<int DefaultIndex, class Tag = keyword_detail::default_tag>
    struct keyword
    {
        typedef boost::mpl::int_<DefaultIndex> default_index_type;
        typedef Tag tag_type;

        template<class A>
        typename disable_if<boost::is_same<A, keyword>, detail::named_arg<keyword, A> const>::type
        operator=(A& a) const
        {
            detail::named_arg<keyword, A> r = {a};
            return r;
        }

        template<class A>
        detail::named_arg<keyword, PSTADE_DEDUCED_CONST(A)> const
        operator=(A const& a) const
        {
            detail::named_arg<keyword, PSTADE_DEDUCED_CONST(A)> r = {a};
            return r;
        }
    };


    #define PSTADE_EGG_KEYWORD {}


} } // namespace pstade::egg


#endif
