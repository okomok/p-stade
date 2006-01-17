
namespace pstade { namespace biscuit {

	template< class Dummy = boost::mpl::void_ >
	struct valseq0;
	template< >
	struct valseq0<boost::mpl::void_> :
		seq0< >
	{ };

	template< class ValueFtor0 >
	struct valseq1 :
		seq1< value< ValueFtor0 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 >
	struct valseq2 :
		seq2< value< ValueFtor0 > , value< ValueFtor1 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 >
	struct valseq3 :
		seq3< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 >
	struct valseq4 :
		seq4< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 >
	struct valseq5 :
		seq5< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 >
	struct valseq6 :
		seq6< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 >
	struct valseq7 :
		seq7< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 >
	struct valseq8 :
		seq8< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 , class ValueFtor8 >
	struct valseq9 :
		seq9< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > , value< ValueFtor8 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 , class ValueFtor8 , class ValueFtor9 >
	struct valseq10 :
		seq10< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > , value< ValueFtor8 > , value< ValueFtor9 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 , class ValueFtor8 , class ValueFtor9 , class ValueFtor10 >
	struct valseq11 :
		seq11< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > , value< ValueFtor8 > , value< ValueFtor9 > , value< ValueFtor10 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 , class ValueFtor8 , class ValueFtor9 , class ValueFtor10 , class ValueFtor11 >
	struct valseq12 :
		seq12< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > , value< ValueFtor8 > , value< ValueFtor9 > , value< ValueFtor10 > , value< ValueFtor11 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 , class ValueFtor8 , class ValueFtor9 , class ValueFtor10 , class ValueFtor11 , class ValueFtor12 >
	struct valseq13 :
		seq13< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > , value< ValueFtor8 > , value< ValueFtor9 > , value< ValueFtor10 > , value< ValueFtor11 > , value< ValueFtor12 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 , class ValueFtor8 , class ValueFtor9 , class ValueFtor10 , class ValueFtor11 , class ValueFtor12 , class ValueFtor13 >
	struct valseq14 :
		seq14< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > , value< ValueFtor8 > , value< ValueFtor9 > , value< ValueFtor10 > , value< ValueFtor11 > , value< ValueFtor12 > , value< ValueFtor13 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 , class ValueFtor8 , class ValueFtor9 , class ValueFtor10 , class ValueFtor11 , class ValueFtor12 , class ValueFtor13 , class ValueFtor14 >
	struct valseq15 :
		seq15< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > , value< ValueFtor8 > , value< ValueFtor9 > , value< ValueFtor10 > , value< ValueFtor11 > , value< ValueFtor12 > , value< ValueFtor13 > , value< ValueFtor14 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 , class ValueFtor8 , class ValueFtor9 , class ValueFtor10 , class ValueFtor11 , class ValueFtor12 , class ValueFtor13 , class ValueFtor14 , class ValueFtor15 >
	struct valseq16 :
		seq16< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > , value< ValueFtor8 > , value< ValueFtor9 > , value< ValueFtor10 > , value< ValueFtor11 > , value< ValueFtor12 > , value< ValueFtor13 > , value< ValueFtor14 > , value< ValueFtor15 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 , class ValueFtor8 , class ValueFtor9 , class ValueFtor10 , class ValueFtor11 , class ValueFtor12 , class ValueFtor13 , class ValueFtor14 , class ValueFtor15 , class ValueFtor16 >
	struct valseq17 :
		seq17< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > , value< ValueFtor8 > , value< ValueFtor9 > , value< ValueFtor10 > , value< ValueFtor11 > , value< ValueFtor12 > , value< ValueFtor13 > , value< ValueFtor14 > , value< ValueFtor15 > , value< ValueFtor16 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 , class ValueFtor8 , class ValueFtor9 , class ValueFtor10 , class ValueFtor11 , class ValueFtor12 , class ValueFtor13 , class ValueFtor14 , class ValueFtor15 , class ValueFtor16 , class ValueFtor17 >
	struct valseq18 :
		seq18< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > , value< ValueFtor8 > , value< ValueFtor9 > , value< ValueFtor10 > , value< ValueFtor11 > , value< ValueFtor12 > , value< ValueFtor13 > , value< ValueFtor14 > , value< ValueFtor15 > , value< ValueFtor16 > , value< ValueFtor17 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 , class ValueFtor8 , class ValueFtor9 , class ValueFtor10 , class ValueFtor11 , class ValueFtor12 , class ValueFtor13 , class ValueFtor14 , class ValueFtor15 , class ValueFtor16 , class ValueFtor17 , class ValueFtor18 >
	struct valseq19 :
		seq19< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > , value< ValueFtor8 > , value< ValueFtor9 > , value< ValueFtor10 > , value< ValueFtor11 > , value< ValueFtor12 > , value< ValueFtor13 > , value< ValueFtor14 > , value< ValueFtor15 > , value< ValueFtor16 > , value< ValueFtor17 > , value< ValueFtor18 > >
	{ };

	template< class ValueFtor0 , class ValueFtor1 , class ValueFtor2 , class ValueFtor3 , class ValueFtor4 , class ValueFtor5 , class ValueFtor6 , class ValueFtor7 , class ValueFtor8 , class ValueFtor9 , class ValueFtor10 , class ValueFtor11 , class ValueFtor12 , class ValueFtor13 , class ValueFtor14 , class ValueFtor15 , class ValueFtor16 , class ValueFtor17 , class ValueFtor18 , class ValueFtor19 >
	struct valseq20 :
		seq20< value< ValueFtor0 > , value< ValueFtor1 > , value< ValueFtor2 > , value< ValueFtor3 > , value< ValueFtor4 > , value< ValueFtor5 > , value< ValueFtor6 > , value< ValueFtor7 > , value< ValueFtor8 > , value< ValueFtor9 > , value< ValueFtor10 > , value< ValueFtor11 > , value< ValueFtor12 > , value< ValueFtor13 > , value< ValueFtor14 > , value< ValueFtor15 > , value< ValueFtor16 > , value< ValueFtor17 > , value< ValueFtor18 > , value< ValueFtor19 > >
	{ };

} } 
