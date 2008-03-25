#ifndef BOOST_PP_IS_ITERATING


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(BOOST_EGG_XXX_PACK_PARAMS)
    #error Please define BOOST_EGG_XXX_PACK_PARAMS.
#endif
#define name      BOOST_PP_TUPLE_ELEM(3, 0, BOOST_EGG_XXX_PACK_PARAMS)
#define template_ BOOST_PP_TUPLE_ELEM(3, 1, BOOST_EGG_XXX_PACK_PARAMS)
#define max_size  BOOST_PP_TUPLE_ELEM(3, 2, BOOST_EGG_XXX_PACK_PARAMS)


    namespace boost { namespace egg {


        namespace BOOST_PP_CAT(name, _detail) {


            template<class Strategy>
            struct little
            {
            // 0ary
                typedef template_(0)<> nullary_result_type;

                template<class Re>
                Re call() const
                {
                    return Re();
                }

            // 1ary-
                template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(max_size, A)>
                struct BOOST_EGG_APPLY_DECL;

                #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, max_size, <boost/egg/detail/xxx_pack_include.hpp>))
                #include BOOST_PP_ITERATE()
            };


        } // namespace name_detail


        template<class Strategy = by_perfect>
        struct BOOST_PP_CAT(X_, name) : details::derived_from<
            function<BOOST_PP_CAT(name, _detail)::little<Strategy>, Strategy> >
        { };

        typedef BOOST_PP_CAT(X_, name)<>::base_class BOOST_PP_CAT(T_, name);
        BOOST_EGG_CONST((BOOST_PP_CAT(T_, name)), name) = {{}};


    } } // namespace boost::egg


    BOOST_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(boost::egg::BOOST_PP_CAT(X_, name), (class))


#undef  max_size
#undef  template_
#undef  name
#undef  BOOST_EGG_XXX_PACK_PARAMS


#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef
            template_(n)<
                BOOST_EGG_FORWARDING_META_ARGS(n, A, Strategy const)
            >
        type;
    };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        return Re(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef  n
#endif
