
namespace pstade { namespace biscuit {

	template< class Dummy = boost::mpl::void_ >
	struct chseq0;
	template< >
	struct chseq0<boost::mpl::void_> :
		seq0< >
	{ };

	template< char ch0 >
	struct chseq1 :
		seq1< char_< ch0 > >
	{ };

	template< char ch0 , char ch1 >
	struct chseq2 :
		seq2< char_< ch0 > , char_< ch1 > >
	{ };

	template< char ch0 , char ch1 , char ch2 >
	struct chseq3 :
		seq3< char_< ch0 > , char_< ch1 > , char_< ch2 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 >
	struct chseq4 :
		seq4< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 >
	struct chseq5 :
		seq5< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 >
	struct chseq6 :
		seq6< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 >
	struct chseq7 :
		seq7< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 >
	struct chseq8 :
		seq8< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 >
	struct chseq9 :
		seq9< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 >
	struct chseq10 :
		seq10< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 >
	struct chseq11 :
		seq11< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 >
	struct chseq12 :
		seq12< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 >
	struct chseq13 :
		seq13< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 >
	struct chseq14 :
		seq14< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 >
	struct chseq15 :
		seq15< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > , char_< ch14 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 >
	struct chseq16 :
		seq16< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > , char_< ch14 > , char_< ch15 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 , char ch16 >
	struct chseq17 :
		seq17< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > , char_< ch14 > , char_< ch15 > , char_< ch16 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 , char ch16 , char ch17 >
	struct chseq18 :
		seq18< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > , char_< ch14 > , char_< ch15 > , char_< ch16 > , char_< ch17 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 , char ch16 , char ch17 , char ch18 >
	struct chseq19 :
		seq19< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > , char_< ch14 > , char_< ch15 > , char_< ch16 > , char_< ch17 > , char_< ch18 > >
	{ };

	template< char ch0 , char ch1 , char ch2 , char ch3 , char ch4 , char ch5 , char ch6 , char ch7 , char ch8 , char ch9 , char ch10 , char ch11 , char ch12 , char ch13 , char ch14 , char ch15 , char ch16 , char ch17 , char ch18 , char ch19 >
	struct chseq20 :
		seq20< char_< ch0 > , char_< ch1 > , char_< ch2 > , char_< ch3 > , char_< ch4 > , char_< ch5 > , char_< ch6 > , char_< ch7 > , char_< ch8 > , char_< ch9 > , char_< ch10 > , char_< ch11 > , char_< ch12 > , char_< ch13 > , char_< ch14 > , char_< ch15 > , char_< ch16 > , char_< ch17 > , char_< ch18 > , char_< ch19 > >
	{ };

} } 
