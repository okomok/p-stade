
namespace pstade { namespace biscuit {

	template< class Dummy = boost::mpl::void_ >
	struct minus0;
	template< >
	struct minus0<boost::mpl::void_>
	{
		template< class State, class UserState >
		static bool parse(State& , UserState& )
		{
			return true;
		}
	};

	template<
		class P0
	>
	struct minus1
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1
	>
	struct minus2
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2
	>
	struct minus3
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3
	>
	struct minus4
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4
	>
	struct minus5
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5
	>
	struct minus6
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6
	>
	struct minus7
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7
	>
	struct minus8
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8
	>
	struct minus9
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }
			if (biscuit::state_match<P8> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9
	>
	struct minus10
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }
			if (biscuit::state_match<P8> (rng, s, us)) { return false; }
			if (biscuit::state_match<P9> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10
	>
	struct minus11
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }
			if (biscuit::state_match<P8> (rng, s, us)) { return false; }
			if (biscuit::state_match<P9> (rng, s, us)) { return false; }
			if (biscuit::state_match<P10> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11
	>
	struct minus12
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }
			if (biscuit::state_match<P8> (rng, s, us)) { return false; }
			if (biscuit::state_match<P9> (rng, s, us)) { return false; }
			if (biscuit::state_match<P10> (rng, s, us)) { return false; }
			if (biscuit::state_match<P11> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12
	>
	struct minus13
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }
			if (biscuit::state_match<P8> (rng, s, us)) { return false; }
			if (biscuit::state_match<P9> (rng, s, us)) { return false; }
			if (biscuit::state_match<P10> (rng, s, us)) { return false; }
			if (biscuit::state_match<P11> (rng, s, us)) { return false; }
			if (biscuit::state_match<P12> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13
	>
	struct minus14
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }
			if (biscuit::state_match<P8> (rng, s, us)) { return false; }
			if (biscuit::state_match<P9> (rng, s, us)) { return false; }
			if (biscuit::state_match<P10> (rng, s, us)) { return false; }
			if (biscuit::state_match<P11> (rng, s, us)) { return false; }
			if (biscuit::state_match<P12> (rng, s, us)) { return false; }
			if (biscuit::state_match<P13> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14
	>
	struct minus15
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }
			if (biscuit::state_match<P8> (rng, s, us)) { return false; }
			if (biscuit::state_match<P9> (rng, s, us)) { return false; }
			if (biscuit::state_match<P10> (rng, s, us)) { return false; }
			if (biscuit::state_match<P11> (rng, s, us)) { return false; }
			if (biscuit::state_match<P12> (rng, s, us)) { return false; }
			if (biscuit::state_match<P13> (rng, s, us)) { return false; }
			if (biscuit::state_match<P14> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15
	>
	struct minus16
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }
			if (biscuit::state_match<P8> (rng, s, us)) { return false; }
			if (biscuit::state_match<P9> (rng, s, us)) { return false; }
			if (biscuit::state_match<P10> (rng, s, us)) { return false; }
			if (biscuit::state_match<P11> (rng, s, us)) { return false; }
			if (biscuit::state_match<P12> (rng, s, us)) { return false; }
			if (biscuit::state_match<P13> (rng, s, us)) { return false; }
			if (biscuit::state_match<P14> (rng, s, us)) { return false; }
			if (biscuit::state_match<P15> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16
	>
	struct minus17
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }
			if (biscuit::state_match<P8> (rng, s, us)) { return false; }
			if (biscuit::state_match<P9> (rng, s, us)) { return false; }
			if (biscuit::state_match<P10> (rng, s, us)) { return false; }
			if (biscuit::state_match<P11> (rng, s, us)) { return false; }
			if (biscuit::state_match<P12> (rng, s, us)) { return false; }
			if (biscuit::state_match<P13> (rng, s, us)) { return false; }
			if (biscuit::state_match<P14> (rng, s, us)) { return false; }
			if (biscuit::state_match<P15> (rng, s, us)) { return false; }
			if (biscuit::state_match<P16> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17
	>
	struct minus18
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }
			if (biscuit::state_match<P8> (rng, s, us)) { return false; }
			if (biscuit::state_match<P9> (rng, s, us)) { return false; }
			if (biscuit::state_match<P10> (rng, s, us)) { return false; }
			if (biscuit::state_match<P11> (rng, s, us)) { return false; }
			if (biscuit::state_match<P12> (rng, s, us)) { return false; }
			if (biscuit::state_match<P13> (rng, s, us)) { return false; }
			if (biscuit::state_match<P14> (rng, s, us)) { return false; }
			if (biscuit::state_match<P15> (rng, s, us)) { return false; }
			if (biscuit::state_match<P16> (rng, s, us)) { return false; }
			if (biscuit::state_match<P17> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17 , class P18
	>
	struct minus19
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }
			if (biscuit::state_match<P8> (rng, s, us)) { return false; }
			if (biscuit::state_match<P9> (rng, s, us)) { return false; }
			if (biscuit::state_match<P10> (rng, s, us)) { return false; }
			if (biscuit::state_match<P11> (rng, s, us)) { return false; }
			if (biscuit::state_match<P12> (rng, s, us)) { return false; }
			if (biscuit::state_match<P13> (rng, s, us)) { return false; }
			if (biscuit::state_match<P14> (rng, s, us)) { return false; }
			if (biscuit::state_match<P15> (rng, s, us)) { return false; }
			if (biscuit::state_match<P16> (rng, s, us)) { return false; }
			if (biscuit::state_match<P17> (rng, s, us)) { return false; }
			if (biscuit::state_match<P18> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17 , class P18 , class P19
	>
	struct minus20
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if (biscuit::state_match<P1> (rng, s, us)) { return false; }
			if (biscuit::state_match<P2> (rng, s, us)) { return false; }
			if (biscuit::state_match<P3> (rng, s, us)) { return false; }
			if (biscuit::state_match<P4> (rng, s, us)) { return false; }
			if (biscuit::state_match<P5> (rng, s, us)) { return false; }
			if (biscuit::state_match<P6> (rng, s, us)) { return false; }
			if (biscuit::state_match<P7> (rng, s, us)) { return false; }
			if (biscuit::state_match<P8> (rng, s, us)) { return false; }
			if (biscuit::state_match<P9> (rng, s, us)) { return false; }
			if (biscuit::state_match<P10> (rng, s, us)) { return false; }
			if (biscuit::state_match<P11> (rng, s, us)) { return false; }
			if (biscuit::state_match<P12> (rng, s, us)) { return false; }
			if (biscuit::state_match<P13> (rng, s, us)) { return false; }
			if (biscuit::state_match<P14> (rng, s, us)) { return false; }
			if (biscuit::state_match<P15> (rng, s, us)) { return false; }
			if (biscuit::state_match<P16> (rng, s, us)) { return false; }
			if (biscuit::state_match<P17> (rng, s, us)) { return false; }
			if (biscuit::state_match<P18> (rng, s, us)) { return false; }
			if (biscuit::state_match<P19> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

} } 
