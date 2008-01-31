#ifndef PSTADE_EGG_AUTO_OBJECT_HPP
#define PSTADE_EGG_AUTO_OBJECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <pstade/any.hpp> // any_movable
#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./fuse.hpp"
#include "./new.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace auto_object_detail {


        // 'automatic' doesn't work; 'auto_ptr' is not CopyConstructible.
        // Note also 'operator auto_ptr_ref<X>()' can't be of help, because
        // some implementations require "move sequence" to be in the same scope.
        // After all, we need a conversion operator to return "lvalue".


        template<class Args>
        struct automator
        {
            explicit automator(Args const& args) :
                m_args(args)
            { }

            template<class X>
            operator std::auto_ptr<X>& ()
            {
                std::auto_ptr<X> ptr(fuse(X_new<X>())(m_args));
                m_any = ptr;
                return m_any.content< std::auto_ptr<X> >();
            }

        private:
            Args m_args;
            any_movable m_any;

            automator& operator=(automator const&);
        };


        struct little
        {
            template<class Me, class Args>
            struct apply
            {
                typedef
                    automator<Args>
                type;
            };

            template<class Re, class Args>
            Re call(Args& args) const
            {
                return Re(args); 
            }
        };


    } // namespace auto_object_detail


    typedef
        variadic<
            auto_object_detail::little,
            by_perfect,
            boost::use_default,
            use_nullary_result
        >::type
    T_auto_object;

    PSTADE_POD_CONSTANT((T_auto_object), auto_object) = PSTADE_EGG_VARIADIC({});


} } // namespace pstade::egg


#endif
