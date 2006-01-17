
namespace pstade { namespace biscuit {

	template< class Dummy = boost::mpl::void_ >
	struct wchseq0;
	template< >
	struct wchseq0<boost::mpl::void_> :
		seq0< >
	{ };

	template< wchar_t ch0 >
	struct wchseq1 :
		seq1< wchar< ch0 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 >
	struct wchseq2 :
		seq2< wchar< ch0 > , wchar< ch1 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 >
	struct wchseq3 :
		seq3< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 >
	struct wchseq4 :
		seq4< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 >
	struct wchseq5 :
		seq5< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 >
	struct wchseq6 :
		seq6< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 >
	struct wchseq7 :
		seq7< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 >
	struct wchseq8 :
		seq8< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 >
	struct wchseq9 :
		seq9< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 >
	struct wchseq10 :
		seq10< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 >
	struct wchseq11 :
		seq11< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 >
	struct wchseq12 :
		seq12< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 >
	struct wchseq13 :
		seq13< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 >
	struct wchseq14 :
		seq14< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 , wchar_t ch14 >
	struct wchseq15 :
		seq15< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > , wchar< ch14 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 , wchar_t ch14 , wchar_t ch15 >
	struct wchseq16 :
		seq16< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > , wchar< ch14 > , wchar< ch15 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 , wchar_t ch14 , wchar_t ch15 , wchar_t ch16 >
	struct wchseq17 :
		seq17< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > , wchar< ch14 > , wchar< ch15 > , wchar< ch16 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 , wchar_t ch14 , wchar_t ch15 , wchar_t ch16 , wchar_t ch17 >
	struct wchseq18 :
		seq18< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > , wchar< ch14 > , wchar< ch15 > , wchar< ch16 > , wchar< ch17 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 , wchar_t ch14 , wchar_t ch15 , wchar_t ch16 , wchar_t ch17 , wchar_t ch18 >
	struct wchseq19 :
		seq19< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > , wchar< ch14 > , wchar< ch15 > , wchar< ch16 > , wchar< ch17 > , wchar< ch18 > >
	{ };

	template< wchar_t ch0 , wchar_t ch1 , wchar_t ch2 , wchar_t ch3 , wchar_t ch4 , wchar_t ch5 , wchar_t ch6 , wchar_t ch7 , wchar_t ch8 , wchar_t ch9 , wchar_t ch10 , wchar_t ch11 , wchar_t ch12 , wchar_t ch13 , wchar_t ch14 , wchar_t ch15 , wchar_t ch16 , wchar_t ch17 , wchar_t ch18 , wchar_t ch19 >
	struct wchseq20 :
		seq20< wchar< ch0 > , wchar< ch1 > , wchar< ch2 > , wchar< ch3 > , wchar< ch4 > , wchar< ch5 > , wchar< ch6 > , wchar< ch7 > , wchar< ch8 > , wchar< ch9 > , wchar< ch10 > , wchar< ch11 > , wchar< ch12 > , wchar< ch13 > , wchar< ch14 > , wchar< ch15 > , wchar< ch16 > , wchar< ch17 > , wchar< ch18 > , wchar< ch19 > >
	{ };

} } 
