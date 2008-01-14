#ifndef PSTADE_EGG_KEYWORD_HPP
#define PSTADE_EGG_KEYWORD_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/enable_if.hpp>
#include "./bll_bindable.hpp"
#include "./detail/named_arg.hpp"
#include "./detail/unref.hpp"


namespace pstade { namespace egg {


    namespace keyword_detail {

        struct default_tag;

    }


    template<int DefaultIndex, class Tag = keyword_detail::default_tag>
    struct keyword
    {
        typedef boost::mpl::int_<DefaultIndex> default_index_type;
        typedef Tag tag_type;

        template<class Signature>
        struct result;

        template<class Self, class Arg>
        struct result<Self(Arg)>
        {
            typedef
                detail::named_arg<keyword, typename detail::unref<by_perfect, Arg>::type> const
            type;
        };

        template<class Arg>
        detail::named_arg<keyword, Arg> const
        operator()(Arg& arg) const
        {
            detail::named_arg<keyword, Arg> r = {arg};
            return r;
        }

        template<class Arg>
        detail::named_arg<keyword, PSTADE_DEDUCED_CONST(Arg)> const
        operator()(Arg const& arg) const
        {
            detail::named_arg<keyword, PSTADE_DEDUCED_CONST(Arg)> r = {arg};
            return r;
        }

        template<class Arg>
        typename disable_if<boost::is_same<Arg, keyword>, detail::named_arg<keyword, Arg> const>::type
        operator=(Arg& arg) const
        {
            return (*this)(arg);
        }

        template<class Arg>
        detail::named_arg<keyword, PSTADE_DEDUCED_CONST(Arg)> const
        operator=(Arg const& arg) const
        {
            return (*this)(arg);
        }

        #include PSTADE_EGG_BLL_BINDABLE()
    };


    #define PSTADE_EGG_KEYWORD() {}


} } // namespace pstade::egg


#endif
