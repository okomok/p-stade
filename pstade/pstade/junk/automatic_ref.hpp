#ifndef PSTADE_EGG_AUTOMATIC_REF_HPP
#define PSTADE_EGG_AUTOMATIC_REF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// It is difficult to implement more generic one,
// because gcc requires a named return value of automator.


#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include <pstade/deduced_const.hpp>
#include "./detail/meta_arg.hpp"
#include "./sig_template.hpp"


namespace pstade { namespace egg {


    namespace automatic_ref_detail {


        // gcc requires this to be a named return value.
        // So, function adaptors around automatic_ref<>::type doesn't work.
        template<class Lambda, class From>
        struct automator
        {
            From& m_from;

            template<class To>
            operator To&() const
            {
                typedef typename
                    boost::mpl::apply1<Lambda, To>::type
                fun_t;

                return fun_t()(m_from);
            }
        };


        template<class Lambda, class From>
        struct result_of_make
        {
            typedef
                automator<Lambda, From> const
            type;
        };


        template<class Lambda>
        struct make
        {
            template<class Signature>
            struct result;

            template<class This, class From>
            struct result<This(From)> :
                result_of_make<Lambda, typename detail::meta_arg<From>::type>
            { };

            template<class From>
            typename result_of_make<Lambda, From>::type operator()(From& from) const
            {
                typename result_of_make<Lambda, From>::type r = {from};
                return r;
            }

            template<class From>
            typename result_of_make<Lambda, PSTADE_DEDUCED_CONST(From)>::type operator()(From const& from) const
            {
                typename result_of_make<Lambda, PSTADE_DEDUCED_CONST(From)>::type r = {from};
                return r;
            }

            #include PSTADE_EGG_SIG_TEMPLATE()
        };


    } // namespace automatic_ref_detail


    template<class Lambda>
    struct automatic_ref
    {
        typedef automatic_ref_detail::make<Lambda> type;
    };


    #define PSTADE_EGG_AUTOMATIC_REF {}


} } // namespace pstade::egg::detail


#endif
