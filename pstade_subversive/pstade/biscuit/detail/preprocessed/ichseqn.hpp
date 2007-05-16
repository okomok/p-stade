
namespace pstade { namespace biscuit {

    template< class Dummy = boost::mpl::void_ >
    struct ichseq0;
    template< >
    struct ichseq0<boost::mpl::void_> :
        seq0< >
    { };

    template< char ch0 >
    struct ichseq1 :
        seq1< ichar< ch0 > >
    { };

    template< char ch0 , char ch1 >
    struct ichseq2 :
        seq2< ichar< ch0 > , ichar< ch1 > >
    { };

    template< char ch0 , char ch1 , char ch2 >
    struct ichseq3 :
        seq3< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 >
    struct ichseq4 :
        seq4< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 >
    struct ichseq5 :
        seq5< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 >
    struct ichseq6 :
        seq6< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 >
    struct ichseq7 :
        seq7< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 >
    struct ichseq8 :
        seq8< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 >
    struct ichseq9 :
        seq9< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > , ichar< ch8 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 >
    struct ichseq10 :
        seq10< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > , ichar< ch8 > , ichar< ch9 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 >
    struct ichseq11 :
        seq11< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > , ichar< ch8 > , ichar< ch9 > , ichar< ch10 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 >
    struct ichseq12 :
        seq12< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > , ichar< ch8 > , ichar< ch9 > , ichar< ch10 > , ichar< ch11 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 >
    struct ichseq13 :
        seq13< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > , ichar< ch8 > , ichar< ch9 > , ichar< ch10 > , ichar< ch11 > , ichar< ch12 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 >
    struct ichseq14 :
        seq14< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > , ichar< ch8 > , ichar< ch9 > , ichar< ch10 > , ichar< ch11 > , ichar< ch12 > , ichar< ch13 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 >
    struct ichseq15 :
        seq15< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > , ichar< ch8 > , ichar< ch9 > , ichar< ch10 > , ichar< ch11 > , ichar< ch12 > , ichar< ch13 > , ichar< ch14 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 >
    struct ichseq16 :
        seq16< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > , ichar< ch8 > , ichar< ch9 > , ichar< ch10 > , ichar< ch11 > , ichar< ch12 > , ichar< ch13 > , ichar< ch14 > , ichar< ch15 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 , char ch16 >
    struct ichseq17 :
        seq17< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > , ichar< ch8 > , ichar< ch9 > , ichar< ch10 > , ichar< ch11 > , ichar< ch12 > , ichar< ch13 > , ichar< ch14 > , ichar< ch15 > , ichar< ch16 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 , char ch16 , char ch17 >
    struct ichseq18 :
        seq18< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > , ichar< ch8 > , ichar< ch9 > , ichar< ch10 > , ichar< ch11 > , ichar< ch12 > , ichar< ch13 > , ichar< ch14 > , ichar< ch15 > , ichar< ch16 > , ichar< ch17 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 , char ch16 , char ch17 , char ch18 >
    struct ichseq19 :
        seq19< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > , ichar< ch8 > , ichar< ch9 > , ichar< ch10 > , ichar< ch11 > , ichar< ch12 > , ichar< ch13 > , ichar< ch14 > , ichar< ch15 > , ichar< ch16 > , ichar< ch17 > , ichar< ch18 > >
    { };

    template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 , char ch16 , char ch17 , char ch18 , char ch19 >
    struct ichseq20 :
        seq20< ichar< ch0 > , ichar< ch1 > , ichar< ch2 > , ichar< ch3 > , ichar< ch4 > , ichar< ch5 > , ichar< ch6 > , ichar< ch7 > , ichar< ch8 > , ichar< ch9 > , ichar< ch10 > , ichar< ch11 > , ichar< ch12 > , ichar< ch13 > , ichar< ch14 > , ichar< ch15 > , ichar< ch16 > , ichar< ch17 > , ichar< ch18 > , ichar< ch19 > >
    { };

} } 
