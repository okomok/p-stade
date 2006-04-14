
namespace pstade { namespace biscuit {

	template< class Dummy = boost::mpl::void_ >
	struct seq0;
	template< >
	struct seq0<boost::mpl::void_>
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
	struct seq1
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1
	>
	struct seq2
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2
	>
	struct seq3
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3
	>
	struct seq4
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4
	>
	struct seq5
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5
	>
	struct seq6
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6
	>
	struct seq7
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7
	>
	struct seq8
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8
	>
	struct seq9
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }
			if ( !P8::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9
	>
	struct seq10
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }
			if ( !P8::parse(s, us)) { return false; }
			if ( !P9::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10
	>
	struct seq11
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }
			if ( !P8::parse(s, us)) { return false; }
			if ( !P9::parse(s, us)) { return false; }
			if ( !P10::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11
	>
	struct seq12
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }
			if ( !P8::parse(s, us)) { return false; }
			if ( !P9::parse(s, us)) { return false; }
			if ( !P10::parse(s, us)) { return false; }
			if ( !P11::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12
	>
	struct seq13
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }
			if ( !P8::parse(s, us)) { return false; }
			if ( !P9::parse(s, us)) { return false; }
			if ( !P10::parse(s, us)) { return false; }
			if ( !P11::parse(s, us)) { return false; }
			if ( !P12::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13
	>
	struct seq14
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }
			if ( !P8::parse(s, us)) { return false; }
			if ( !P9::parse(s, us)) { return false; }
			if ( !P10::parse(s, us)) { return false; }
			if ( !P11::parse(s, us)) { return false; }
			if ( !P12::parse(s, us)) { return false; }
			if ( !P13::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14
	>
	struct seq15
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }
			if ( !P8::parse(s, us)) { return false; }
			if ( !P9::parse(s, us)) { return false; }
			if ( !P10::parse(s, us)) { return false; }
			if ( !P11::parse(s, us)) { return false; }
			if ( !P12::parse(s, us)) { return false; }
			if ( !P13::parse(s, us)) { return false; }
			if ( !P14::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15
	>
	struct seq16
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }
			if ( !P8::parse(s, us)) { return false; }
			if ( !P9::parse(s, us)) { return false; }
			if ( !P10::parse(s, us)) { return false; }
			if ( !P11::parse(s, us)) { return false; }
			if ( !P12::parse(s, us)) { return false; }
			if ( !P13::parse(s, us)) { return false; }
			if ( !P14::parse(s, us)) { return false; }
			if ( !P15::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16
	>
	struct seq17
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }
			if ( !P8::parse(s, us)) { return false; }
			if ( !P9::parse(s, us)) { return false; }
			if ( !P10::parse(s, us)) { return false; }
			if ( !P11::parse(s, us)) { return false; }
			if ( !P12::parse(s, us)) { return false; }
			if ( !P13::parse(s, us)) { return false; }
			if ( !P14::parse(s, us)) { return false; }
			if ( !P15::parse(s, us)) { return false; }
			if ( !P16::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17
	>
	struct seq18
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }
			if ( !P8::parse(s, us)) { return false; }
			if ( !P9::parse(s, us)) { return false; }
			if ( !P10::parse(s, us)) { return false; }
			if ( !P11::parse(s, us)) { return false; }
			if ( !P12::parse(s, us)) { return false; }
			if ( !P13::parse(s, us)) { return false; }
			if ( !P14::parse(s, us)) { return false; }
			if ( !P15::parse(s, us)) { return false; }
			if ( !P16::parse(s, us)) { return false; }
			if ( !P17::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17 , class P18
	>
	struct seq19
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }
			if ( !P8::parse(s, us)) { return false; }
			if ( !P9::parse(s, us)) { return false; }
			if ( !P10::parse(s, us)) { return false; }
			if ( !P11::parse(s, us)) { return false; }
			if ( !P12::parse(s, us)) { return false; }
			if ( !P13::parse(s, us)) { return false; }
			if ( !P14::parse(s, us)) { return false; }
			if ( !P15::parse(s, us)) { return false; }
			if ( !P16::parse(s, us)) { return false; }
			if ( !P17::parse(s, us)) { return false; }
			if ( !P18::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17 , class P18 , class P19
	>
	struct seq20
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			state_cur_guard<State> gd(s);

			if ( !P0::parse(s, us)) { return false; }
			if ( !P1::parse(s, us)) { return false; }
			if ( !P2::parse(s, us)) { return false; }
			if ( !P3::parse(s, us)) { return false; }
			if ( !P4::parse(s, us)) { return false; }
			if ( !P5::parse(s, us)) { return false; }
			if ( !P6::parse(s, us)) { return false; }
			if ( !P7::parse(s, us)) { return false; }
			if ( !P8::parse(s, us)) { return false; }
			if ( !P9::parse(s, us)) { return false; }
			if ( !P10::parse(s, us)) { return false; }
			if ( !P11::parse(s, us)) { return false; }
			if ( !P12::parse(s, us)) { return false; }
			if ( !P13::parse(s, us)) { return false; }
			if ( !P14::parse(s, us)) { return false; }
			if ( !P15::parse(s, us)) { return false; }
			if ( !P16::parse(s, us)) { return false; }
			if ( !P17::parse(s, us)) { return false; }
			if ( !P18::parse(s, us)) { return false; }
			if ( !P19::parse(s, us)) { return false; }

			gd.dismiss(); return true;
		}
	};

} } 
