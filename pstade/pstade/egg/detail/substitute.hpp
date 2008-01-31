#ifndef PSTADE_EGG_DETAIL_SUBSTITUTE_HPP
#define PSTADE_EGG_DETAIL_SUBSTITUTE_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/ref.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pod_constant.hpp>
#include "../always.hpp"
#include "../by_cref.hpp"
#include "../is_bind_expression.hpp"


namespace pstade { namespace egg { namespace detail {


    struct little_substitute
    {
        template<class Me, class X>
        struct apply :
            boost::mpl::eval_if< is_bind_expression<X>,
                boost::mpl::identity<X&>,
                result_of<T_always_ref(X&)>
            >
        { };

        template<class Re, class X>
        Re call(X& x, typename enable_if< is_bind_expression<X> >::type = 0) const
        {
            return x;
        }

        template<class Re, class X>
        Re call(X& x, typename disable_if<is_bind_expression<X> >::type = 0) const
        {
            return always_ref(x);
        }
    };

    typedef function<little_substitute, by_cref> T_substitute;
    PSTADE_POD_CONSTANT((T_substitute), substitute) = {{}};


} } } // namespace pstade::egg::detail


#endif
