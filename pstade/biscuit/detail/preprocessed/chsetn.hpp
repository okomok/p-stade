
namespace pstade { namespace biscuit {

    template< class Dummy = boost::mpl::void_ >
    struct chset0;
    template< >
    struct chset0<boost::mpl::void_> :
        or_0< >
    { };

    template< char ch0 >
    struct chset1 :
        or_1< char_< ch0 > >
    { };

    template< char ch0 , char ch1 >
    struct chset2 :
        or_2< char_< ch0 > , char_< ch1 > >
    { };

    template< char ch0 , char ch1 , char ch2 >
    struct chset3 :
        or_3< char_< ch0 > , char_< ch1 > , char_< ch2 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 >
    struct chset4 :
        or_4< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 >
    struct chset5 :
        or_5< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 >
    struct chset6 :
        or_6< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 >
    struct chset7 :
        or_7< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 >
    struct chset8 :
        or_8< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 >
    struct chset9 :
        or_9< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 >
    struct chset10 :
        or_10< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 >
    struct chset11 :
        or_11< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 >
    struct chset12 :
        or_12< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 >
    struct chset13 :
        or_13< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 >
    struct chset14 :
        or_14< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 >
    struct chset15 :
        or_15< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > , char_< ch14 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 >
    struct chset16 :
        or_16< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > , char_< ch14 > , char_< ch15 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 , char ch16 >
    struct chset17 :
        or_17< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > , char_< ch14 > , char_< ch15 > , char_< ch16 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 , char ch16 , char ch17 >
    struct chset18 :
        or_18< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > , char_< ch14 > , char_< ch15 > , char_< ch16 > , char_< ch17 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 , char ch16 , char ch17 , char ch18 >
    struct chset19 :
        or_19< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > , char_< ch14 > , char_< ch15 > , char_< ch16 > , char_< ch17 > , char_< ch18 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 , char ch16 , char ch17 , char ch18 , char ch19 >
    struct chset20 :
        or_20< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > , char_< ch14 > , char_< ch15 > , char_< ch16 > , char_< ch17 > , char_< ch18 > , char_< ch19 > >
    { };

} } 
