
namespace pstade { namespace biscuit {

    template< class Dummy = boost::mpl::void_ >
    struct wchset0;
    template< >
    struct wchset0<boost::mpl::void_> :
        or_0< >
    { };

    template< wchar_t ch0 >
    struct wchset1 :
        or_1< wchar< ch0 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 >
    struct wchset2 :
        or_2< wchar< ch0 > , wchar< ch1 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 >
    struct wchset3 :
        or_3< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 >
    struct wchset4 :
        or_4< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 >
    struct wchset5 :
        or_5< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 >
    struct wchset6 :
        or_6< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 >
    struct wchset7 :
        or_7< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 >
    struct wchset8 :
        or_8< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 >
    struct wchset9 :
        or_9< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 >
    struct wchset10 :
        or_10< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 >
    struct wchset11 :
        or_11< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 >
    struct wchset12 :
        or_12< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 >
    struct wchset13 :
        or_13< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 >
    struct wchset14 :
        or_14< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 , wchar_t ch14 >
    struct wchset15 :
        or_15< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > , wchar< ch14 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 , wchar_t ch14 , wchar_t ch15 >
    struct wchset16 :
        or_16< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > , wchar< ch14 > , wchar< ch15 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 , wchar_t ch14 , wchar_t ch15 , wchar_t ch16 >
    struct wchset17 :
        or_17< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > , wchar< ch14 > , wchar< ch15 > , wchar< ch16 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 , wchar_t ch14 , wchar_t ch15 , wchar_t ch16 , wchar_t ch17 >
    struct wchset18 :
        or_18< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > , wchar< ch14 > , wchar< ch15 > , wchar< ch16 > , wchar< ch17 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 , wchar_t ch14 , wchar_t ch15 , wchar_t ch16 , wchar_t ch17 , wchar_t ch18 >
    struct wchset19 :
        or_19< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > , wchar< ch14 > , wchar< ch15 > , wchar< ch16 > , wchar< ch17 > , wchar< ch18 > >
    { };

    template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 , wchar_t ch14 , wchar_t ch15 , wchar_t ch16 , wchar_t ch17 , wchar_t ch18 , wchar_t ch19 >
    struct wchset20 :
        or_20< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > , wchar< ch14 > , wchar< ch15 > , wchar< ch16 > , wchar< ch17 > , wchar< ch18 > , wchar< ch19 > >
    { };

} } 
