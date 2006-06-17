// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#if !BOOST_PP_IS_ITERATING
# ifndef BOOST_DETAIL_CALLABLE_DWA2006516_HPP
#  define BOOST_DETAIL_CALLABLE_DWA2006516_HPP

#  include <boost/utility/result_of.hpp>
#  include <boost/preprocessor/cat.hpp>
#  include <boost/preprocessor/iteration/iterate.hpp>
#  include <boost/preprocessor/punctuation/comma_if.hpp>
#  include <boost/preprocessor/repetition/enum_params.hpp>
#  include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#  include <boost/preprocessor/repetition/repeat.hpp>
#  include <boost/preprocessor/seq/for_each_i.hpp>
#  include <boost/preprocessor/seq/for_each_product.hpp>

#  ifndef BOOST_CALLABLE_MAX_ARITY
#   define BOOST_CALLABLE_MAX_ARITY 5
#  endif

namespace boost { namespace detail { 

// CRTP base class that handles the forwarding problem.  Derived must
// only supply a call const member function and ensure a functioning
// result_of for it.  Thanks to Paul Mensonides for fast operator()
// overload generation.
template <class Derived, class NullaryResult = void>
struct callable
{
    typedef Derived const derived_const;

    NullaryResult operator()() const
    {
        return static_cast<Derived const*>(this)->call();
    }

#  define call_operator(r, constness)                                   \
    template <BOOST_PP_ENUM_PARAMS(n, class A)>                         \
    typename boost::result_of<                                          \
        derived_const(                                                  \
            BOOST_PP_SEQ_FOR_EACH_I_R(r,arg_type,~,constness)           \
        )                                                               \
    >::type                                                             \
    operator()(BOOST_PP_SEQ_FOR_EACH_I_R(r,param,~,constness)) const    \
    {                                                                   \
        return static_cast<Derived const*>(this)->call(                 \
            BOOST_PP_ENUM_PARAMS(n,x)                                   \
        );                                                              \
    }

#  define arg_type(r,_,i,b)                                     \
    BOOST_PP_COMMA_IF(i) BOOST_PP_CAT(A,i) BOOST_PP_CAT(c,b) &

#  define param(r,_,i,b) BOOST_PP_COMMA_IF(i)               \
    BOOST_PP_CAT(A,i) BOOST_PP_CAT(c,b) & BOOST_PP_CAT(x,i)
               
#  define c0
#  define c1 const

#  define bits(z, n, _) ((0)(1))
    
#  define BOOST_DETAIL_CALLABLE <boost/detail/callable.hpp>
#  define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_CALLABLE_MAX_ARITY, BOOST_DETAIL_CALLABLE))
    
#  include BOOST_PP_ITERATE()

#  undef BOOST_DETAIL_CALLABLE
#  undef bits
#  undef c1
#  undef c0
#  undef param
#  undef arg_type
#  undef call_operator
    
};
    
}} // namespace boost::detail

# endif // BOOST_DETAIL_CALLABLE_DWA2006516_HPP
#else

# define n BOOST_PP_ITERATION()

    BOOST_PP_SEQ_FOR_EACH_PRODUCT(
        call_operator
      , BOOST_PP_REPEAT(n, bits, ~)
    )


# undef n

#endif
