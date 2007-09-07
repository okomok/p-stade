#ifndef PSTADE_EGG_MONAD_CORE_HPP
#define PSTADE_EGG_MONAD_CORE_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


//////////////////////////////////////////////////////////////////////
// Monad concepts
//////////////////////////////////////////////////////////////////////
// Here we outline the C++ concepts necessary for monads to work in the
// framework.
/*
   concept Monad {
      // unit :: a -> m a
      // bind :: m a -> ( a -> m b ) -> m b
      typedef Unit;           // a full functoid type
      static Unit unit;
      typedef Bind;           // a full functoid type
      static Bind bind;
   }
   //////////////////////////////
   // Inferrable Monads let you use bind() instead of bindM<Monad>()(), and
   // are also the only Monads that work with do-notation (doM).
   concept InferrableMonad models Monad {
      // type constructor: pass an 'a', get back an 'M a'
      template <class A>  struct Rep   { typedef Type; };
      // type deconstructor: pass an 'M a', get back an 'a'
      template <class MA> struct UnRep { typedef Type; };
   }
   and also
   template <> struct MonadTraitsSpecializer< RepType > {
      typedef Monad;   // the monad concept class
   };
   //////////////////////////////
   // Monad zeros enable comprehension guards to work
   concept MonadWithZero models Monad {
      // zero :: m a
      typedef Zero;           // a value type
      static Zero zero;
   }
   //////////////////////////////
   // Some monads have pluses
   concept MonadWithPlus models Monad {
      // plus :: m a -> ma -> ma
      typedef Plus;           // a full functoid type
      static Plus plus;
   }
*/
//////////////////////////////////////////////////////////////////////


#include <exception>
#include <string>
#include <boost/utility/addressof.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include "../always.hpp"
#include "../copy.hpp"
#include "../function.hpp"
#include "../make_function.hpp"
#include "../use_deduced_form.hpp"


namespace pstade_egg_extension {


    template<class X>
    struct Monad_tag
    {
        typedef void type;
    };


    template<class X, class EnableIf>
    struct Monad_base;


    template<class X, class Tag = typename Monad_tag<X>::type>
    struct Monad :
        Monad_base<X, pstade::enabler>
    { };


    struct Monad_default;


    using pstade::enable_if;


} // namespace pstade_egg_extension


namespace pstade { namespace egg {


    template<class MA>
    struct xp_monad_return
    {
        typedef MA result_type;

        template<class A>
        result_type operator()(A const& a) const
        {
            typedef pstade_egg_extension::Monad<MA> extM_t;
            return extM_t().template unit<MA>(a);
        }
    };


    template<class MA>
    struct xp_monad_fail
    {
        typedef MA result_type;

        result_type operator()(std::string const& s) const
        {
            typedef pstade_egg_extension::Monad<MA> extM_t;
            return extM_t().template fail<MA>(s);
        }
    };


    namespace monad_detail {


        namespace ext = pstade_egg_extension;


        template<class A>
        struct wrapper
        {
            A const *m_pa;

            template<class MA>
            operator MA() const
            {
                return xp_monad_return<MA>()(*m_pa);
            }
        };


        struct baby_bind
        {
            template<class MA, class A_MB>
            struct apply_aux :
                result_of<
                    A_MB(typename ext::Monad<MA>::template unwrap<MA>::type)
                >
            { };

            template<class Result, class MA, class A_MB>
            Result call(boost::type<Result>, MA const& m, A_MB& f) const
            {
                typedef ext::Monad<MA> extM_t;
                return extM_t().template bind<Result>(m, f);
            }

            template<class A, class A_MB>
            struct apply_aux<wrapper<A>, A_MB> :
                result_of<
                    A_MB(A)
                >
            { };

            template<class Result, class A, class A_MB>
            Result call(boost::type<Result>, wrapper<A> const& w, A_MB& f) const
            {
                typedef ext::Monad<Result> extM_t_;
                typedef typename extM_t_::template wrap<A>::type MA_t;
                return make_function(*this)(egg::copy<MA_t>(w), f);
            }

            template<class Myself, class MA, class A_MB>
            struct apply :
                apply_aux<typename pass_by_value<MA>::type, A_MB>
            { };
        };


        struct baby_bind_
        {
            template<class Myself, class MA, class MB>
            struct apply
            {
                typedef MB type;
            };

            template<class Result, class MA, class MB>
            Result call(MA& m, MB& k) const
            {
                typedef ext::Monad<Result> extM_t_;
                return extM_t_().template bind_<Result>(m, k);
            }
        };


        struct baby_return_wrapper
        {
            template<class Myself, class A>
            struct apply
            {
                typedef
                    wrapper<typename pass_by_value<A>::type>
                type;
            };

            template<class Result, class A>
            Result call(A& a) const
            {
                Result r = { boost::addressof(a) };
                return r;
            }
        };


    } // namespace monad_detail


    typedef function<monad_detail::baby_bind, boost::use_default, use_deduced_form> op_monad_bind;
    PSTADE_POD_CONSTANT((op_monad_bind), monad_bind) = {{}};

    typedef function<monad_detail::baby_bind_> op_monad_bind_;
    PSTADE_POD_CONSTANT((op_monad_bind_), monad_bind_) = {{}};

    typedef function<monad_detail::baby_return_wrapper> op_monad_return;
    PSTADE_POD_CONSTANT((op_monad_return), monad_return) = {{}};


    struct monad_failure :
        std::exception
    {
        char const *what() const throw() // override
        {
            return "pstade::egg::monad_failure";
        }
    };


} } // namespace pstade::egg


namespace pstade_egg_extension {


    struct Monad_default
    {
        template<class MB, class MA>
        MB bind_(MA const& m, MB const& k)
        {
            namespace egg = pstade::egg;
            return egg::monad_bind(m, egg::always(k));
        }

        template<class MA>
        MA fail(std::string const& s)
        {
            throw pstade::egg::monad_failure(s);
        }
    };


} // namespace pstade_egg_extension


#endif
