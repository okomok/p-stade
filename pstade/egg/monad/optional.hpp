#ifndef PSTADE_EGG_MONAD_OPTIONAL_HPP
#define PSTADE_EGG_MONAD_OPTIONAL_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional/optional_fwd.hpp>
#include "./core.hpp"


namespace pstade_egg_extension {


    template<class T>
    struct Monad< boost::optional<T> > :
        Monad_default
    {
        // MA == boost::optional<T>
        template<class MA>
        struct unwrap
        {
            typedef T type;
        };

        // Notice: A != T
        template<class A>
        struct wrap
        {
            typedef boost::optional<A> type;
        };

        template<class MB, class MA, class A_MB>
        MB bind(MA const& m, A_MB f)
        {
            if (m)
                return f(*m);
            else
                return MB();
        }

        template<class MA, class A>
        MA unit(A const& a)
        {
            return MA(a);
        }
    };


} // namespace pstade_egg_extension


#endif
