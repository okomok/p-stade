#ifndef PSTADE_EGG_MOVE_ASSIGN_HPP
#define PSTADE_EGG_MOVE_ASSIGN_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./to_ref.hpp" // to_mref


namespace pstade { namespace egg {


    // ADL customization point.
    // In fact, optimizer will do your work, though.
    // Note this is in the same namespace as below for a msvc bug.
    template<class From, class To> inline
    void pstade_egg_move_assign(From& from, To& to)
    {
        to = from;
    }


    struct T_move_assign
    {
        typedef void result_type;

        // `from` can never be a const-qualified object.
        template<class From, class To> inline
        void operator()(From const& from, To& to) const
        {
            pstade_egg_move_assign(to_mref(from), to);
        }
    };

    PSTADE_POD_CONSTANT((T_move_assign), move_assign) = {};


} } // namespace pstade::egg


#endif
