
namespace pstade { namespace biscuit {

	template< class Dummy = boost::mpl::void_ >
	struct and_0;
	template< >
	struct and_0<boost::mpl::void_>
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
	struct and_1
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
	struct and_2
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2
	>
	struct and_3
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3
	>
	struct and_4
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4
	>
	struct and_5
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5
	>
	struct and_6
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6
	>
	struct and_7
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7
	>
	struct and_8
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8
	>
	struct and_9
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P8> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9
	>
	struct and_10
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P8> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P9> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10
	>
	struct and_11
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P8> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P9> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P10> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11
	>
	struct and_12
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P8> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P9> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P10> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P11> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12
	>
	struct and_13
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P8> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P9> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P10> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P11> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P12> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13
	>
	struct and_14
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P8> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P9> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P10> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P11> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P12> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P13> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14
	>
	struct and_15
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P8> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P9> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P10> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P11> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P12> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P13> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P14> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15
	>
	struct and_16
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P8> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P9> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P10> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P11> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P12> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P13> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P14> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P15> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16
	>
	struct and_17
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P8> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P9> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P10> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P11> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P12> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P13> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P14> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P15> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P16> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17
	>
	struct and_18
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P8> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P9> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P10> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P11> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P12> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P13> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P14> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P15> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P16> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P17> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17 , class P18
	>
	struct and_19
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P8> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P9> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P10> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P11> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P12> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P13> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P14> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P15> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P16> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P17> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P18> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17 , class P18 , class P19
	>
	struct and_20
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s); if ( !P0::parse(s, us)) { return false; }

			typedef typename boost::range_result_iterator<State> ::type iter_t; boost::iterator_range<iter_t> rng(gd.marker(), s.get_cur());
			if ( !biscuit::state_match<P1> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P2> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P3> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P4> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P5> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P6> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P7> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P8> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P9> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P10> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P11> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P12> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P13> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P14> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P15> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P16> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P17> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P18> (rng, s, us)) { return false; }
			if ( !biscuit::state_match<P19> (rng, s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

} } 
