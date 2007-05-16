
#if !defined(BOOST_PP_IS_ITERATING)

        #include <boost/preprocessor/cat.hpp>
        #include <boost/preprocessor/iteration/local.hpp>
        #include <boost/preprocessor/iteration/iterate.hpp>
        #include <boost/preprocessor/repetition/enum_params.hpp>

        #if !defined(PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_make_body)
            #define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_make_body(z, i, data)
        #endif

        #if !defined(PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_header)
            #define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_header
        #endif

        #if !defined( PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_footer)
            #define PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_footer
        #endif

        namespace pstade { namespace biscuit {

// empty
template< class Dummy = boost::mpl::void_ >
struct BOOST_PP_CAT(PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_typename, 0);

template<>
struct BOOST_PP_CAT(PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_typename, 0)<boost::mpl::void_>
{
    template< class State, class UserState >
    static bool parse(State&, UserState&)
    {
        PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_make_empty_body()
    }
};

        #define BOOST_PP_ITERATION_LIMITS (1, PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_limits)
        #define BOOST_PP_FILENAME_1 "./numbered_parsers.hpp"
        #include BOOST_PP_ITERATE()

        } } // namespace pstade::biscuit

        #undef PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_typename
        #undef PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_limits
        #undef PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_param
        #undef PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_arg
        #undef PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_make_empty_body
        #undef PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_make_body
        #undef PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_header
        #undef PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_footer

#else // BOOST_PP_IS_ITERATING

    #define i BOOST_PP_ITERATION()

template<
    BOOST_PP_ENUM_PARAMS(i, PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_param PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_arg)
>
struct BOOST_PP_CAT(PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_typename, i)
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_header

        #define BOOST_PP_LOCAL_MACRO(i) PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_make_body(~, i, ~)
        #define BOOST_PP_LOCAL_LIMITS (0, i-1)
        #include BOOST_PP_LOCAL_ITERATE()
        #undef BOOST_PP_LOCAL_MACRO

        PSTADE_BISCUIT_NUMBERED_PARSERS_ARG_body_footer
    }
};

    #undef i

#endif // BOOST_PP_IS_ITERATING
