#ifndef PSTADE_MOVE_TO_AUTO_PTR_HPP
#define PSTADE_MOVE_TO_AUTO_PTR_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 'std::auto_ptr' isn't copy-initializable from one which has
// a different 'element_type'. See http://tinyurl.com/yo8a7w (defect report #84)


#include <memory> // auto_ptr


namespace pstade {


    template<class Element>
    struct op_move_to_auto_ptr
    {
        typedef
            std::auto_ptr<Element>
        result_type;

        template<class Ptr>
        result_type operator()(Ptr p) const
        {
            return result_type(p.release());
        }
    };


    // <pstade/specified.hpp> is useless here; See <pstade/callable_by_value.hpp>.

    template<class Element, class Ptr> inline
    std::auto_ptr<Element> move_to_auto_ptr(Ptr p)
    {
        // We can't call 'op_move_to_auto_ptr<>()(p)' here,
        // because 'move_ptr' doesn't allow implicit-move from lvalue.
        return std::auto_ptr<Element>(p.release());
    }


    // Hmm, move_ptr can't be automatically moved from lvalue.


} // namespace pstade


#endif
