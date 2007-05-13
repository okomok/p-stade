
namespace pstade { namespace biscuit {

    template< class Dummy = boost::mpl::void_ >
    struct or_0;
    template< >
    struct or_0<boost::mpl::void_>
    {
        template< class State, class UserState >
        static bool parse(State& , UserState& )
        {
            return false;
        }
    };

    template<
        class P0
    >
    struct or_1
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1
    >
    struct or_2
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2
    >
    struct or_3
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3
    >
    struct or_4
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4
    >
    struct or_5
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5
    >
    struct or_6
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6
    >
    struct or_7
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7
    >
    struct or_8
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8
    >
    struct or_9
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;
            if (P8::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9
    >
    struct or_10
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;
            if (P8::parse(s, us)) return true;
            if (P9::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10
    >
    struct or_11
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;
            if (P8::parse(s, us)) return true;
            if (P9::parse(s, us)) return true;
            if (P10::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11
    >
    struct or_12
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;
            if (P8::parse(s, us)) return true;
            if (P9::parse(s, us)) return true;
            if (P10::parse(s, us)) return true;
            if (P11::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12
    >
    struct or_13
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;
            if (P8::parse(s, us)) return true;
            if (P9::parse(s, us)) return true;
            if (P10::parse(s, us)) return true;
            if (P11::parse(s, us)) return true;
            if (P12::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13
    >
    struct or_14
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;
            if (P8::parse(s, us)) return true;
            if (P9::parse(s, us)) return true;
            if (P10::parse(s, us)) return true;
            if (P11::parse(s, us)) return true;
            if (P12::parse(s, us)) return true;
            if (P13::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14
    >
    struct or_15
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;
            if (P8::parse(s, us)) return true;
            if (P9::parse(s, us)) return true;
            if (P10::parse(s, us)) return true;
            if (P11::parse(s, us)) return true;
            if (P12::parse(s, us)) return true;
            if (P13::parse(s, us)) return true;
            if (P14::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15
    >
    struct or_16
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;
            if (P8::parse(s, us)) return true;
            if (P9::parse(s, us)) return true;
            if (P10::parse(s, us)) return true;
            if (P11::parse(s, us)) return true;
            if (P12::parse(s, us)) return true;
            if (P13::parse(s, us)) return true;
            if (P14::parse(s, us)) return true;
            if (P15::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16
    >
    struct or_17
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;
            if (P8::parse(s, us)) return true;
            if (P9::parse(s, us)) return true;
            if (P10::parse(s, us)) return true;
            if (P11::parse(s, us)) return true;
            if (P12::parse(s, us)) return true;
            if (P13::parse(s, us)) return true;
            if (P14::parse(s, us)) return true;
            if (P15::parse(s, us)) return true;
            if (P16::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17
    >
    struct or_18
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;
            if (P8::parse(s, us)) return true;
            if (P9::parse(s, us)) return true;
            if (P10::parse(s, us)) return true;
            if (P11::parse(s, us)) return true;
            if (P12::parse(s, us)) return true;
            if (P13::parse(s, us)) return true;
            if (P14::parse(s, us)) return true;
            if (P15::parse(s, us)) return true;
            if (P16::parse(s, us)) return true;
            if (P17::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17 , class P18
    >
    struct or_19
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;
            if (P8::parse(s, us)) return true;
            if (P9::parse(s, us)) return true;
            if (P10::parse(s, us)) return true;
            if (P11::parse(s, us)) return true;
            if (P12::parse(s, us)) return true;
            if (P13::parse(s, us)) return true;
            if (P14::parse(s, us)) return true;
            if (P15::parse(s, us)) return true;
            if (P16::parse(s, us)) return true;
            if (P17::parse(s, us)) return true;
            if (P18::parse(s, us)) return true;

            return false;
        }
    };

    template<
        class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17 , class P18 , class P19
    >
    struct or_20
    {
        template< class State, class UserState >
        static bool parse(State& s, UserState& us)
        {

            if (P0::parse(s, us)) return true;
            if (P1::parse(s, us)) return true;
            if (P2::parse(s, us)) return true;
            if (P3::parse(s, us)) return true;
            if (P4::parse(s, us)) return true;
            if (P5::parse(s, us)) return true;
            if (P6::parse(s, us)) return true;
            if (P7::parse(s, us)) return true;
            if (P8::parse(s, us)) return true;
            if (P9::parse(s, us)) return true;
            if (P10::parse(s, us)) return true;
            if (P11::parse(s, us)) return true;
            if (P12::parse(s, us)) return true;
            if (P13::parse(s, us)) return true;
            if (P14::parse(s, us)) return true;
            if (P15::parse(s, us)) return true;
            if (P16::parse(s, us)) return true;
            if (P17::parse(s, us)) return true;
            if (P18::parse(s, us)) return true;
            if (P19::parse(s, us)) return true;

            return false;
        }
    };

} } 
