
/*
#define POOST_pp_header
#define POOST_pp_footer
#define POOST_pp_name
#define POOST_pp_limit_params_size
#define POOST_pp_param
#define POOST_pp_arg
#define POOST_pp_base_fun
#define POOST_pp_definition_fun
*/

#ifndef BOOST_PP_IS_ITERATING

        #include <boost/preprocessor/cat.hpp>
        #include <boost/preprocessor/iteration/iterate.hpp>
        #include <boost/preprocessor/iteration/local.hpp>
        #include <boost/preprocessor/repetition/enum_params.hpp>
        #include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

        #ifndef POOST_pp_header
            #define POOST_pp_header
        #endif

        #ifndef POOST_pp_footer
            #define POOST_pp_header
        #endif

        #ifndef POOST_pp_base_fun
            #define POOST_pp_base_fun(name, n)
        #endif

        #ifndef POOST_pp_definition_fun
            #define POOST_pp_definition_fun(name, n)
        #endif

        POOST_pp_header
        
// primary
template<
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(POOST_pp_limit_params_size, POOST_pp_param POOST_pp_arg, POOST_pp_def_arg)
>
struct POOST_pp_name :
    BOOST_PP_CAT(POOST_pp_name, POOST_pp_limit_params_size)<
        BOOST_PP_ENUM_PARAMS(POOST_pp_limit_params_size, POOST_pp_arg)
    >
{
    POOST_pp_definition_fun(POOST_pp_name, POOST_pp_limit_params_size)
};

        #define BOOST_PP_ITERATION_LIMITS (1, POOST_pp_limit_params_size-1)
        #define BOOST_PP_FILENAME_1 "./poost_pp_variadic_forms.ipp"
        #include BOOST_PP_ITERATE()

        POOST_pp_footer

        #undef POOST_pp_header
        #undef POOST_pp_footer
        #undef POOST_pp_name
        #undef POOST_pp_limit_params_size
        #undef POOST_pp_param
        #undef POOST_pp_arg
        #undef POOST_pp_def_arg
        #undef POOST_pp_base_fun
        #undef POOST_pp_definition_fun

#else // BOOST_PP_IS_ITERATING

    #define n BOOST_PP_ITERATION()

template<
    BOOST_PP_ENUM_PARAMS(n, POOST_pp_param POOST_pp_arg)
>
struct POOST_pp_name<
    BOOST_PP_ENUM_PARAMS(n, POOST_pp_arg)
> :
    BOOST_PP_CAT(POOST_pp_name, n)<
        BOOST_PP_ENUM_PARAMS(n, POOST_pp_arg)
    >
{
    POOST_pp_definition_fun(POOST_pp_name, n)
};

    #undef n

#endif // BOOST_PP_IS_ITERATING
