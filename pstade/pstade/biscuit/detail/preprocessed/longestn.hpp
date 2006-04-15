
namespace pstade { namespace biscuit {

	template< class Dummy = boost::mpl::void_ >
	struct longest0;
	template< >
	struct longest0<boost::mpl::void_>
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
	struct longest1
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1
	>
	struct longest2
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2
	>
	struct longest3
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3
	>
	struct longest4
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4
	>
	struct longest5
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5
	>
	struct longest6
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6
	>
	struct longest7
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7
	>
	struct longest8
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8
	>
	struct longest9
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P8::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9
	>
	struct longest10
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P8::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P9::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10
	>
	struct longest11
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P8::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P9::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P10::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11
	>
	struct longest12
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P8::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P9::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P10::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P11::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12
	>
	struct longest13
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P8::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P9::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P10::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P11::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P12::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13
	>
	struct longest14
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P8::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P9::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P10::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P11::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P12::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P13::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14
	>
	struct longest15
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P8::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P9::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P10::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P11::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P12::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P13::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P14::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15
	>
	struct longest16
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P8::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P9::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P10::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P11::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P12::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P13::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P14::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P15::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16
	>
	struct longest17
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P8::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P9::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P10::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P11::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P12::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P13::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P14::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P15::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P16::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17
	>
	struct longest18
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P8::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P9::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P10::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P11::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P12::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P13::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P14::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P15::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P16::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P17::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17 , class P18
	>
	struct longest19
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P8::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P9::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P10::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P11::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P12::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P13::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P14::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P15::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P16::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P17::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P18::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

	template<
		class P0 , class P1 , class P2 , class P3 , class P4 , class P5 , class P6 , class P7 , class P8 , class P9 , class P10 , class P11 , class P12 , class P13 , class P14 , class P15 , class P16 , class P17 , class P18 , class P19
	>
	struct longest20
	{
		template< class State, class UserState >
		static bool parse(State& s, UserState& us)
		{
			typedef typename boost::range_result_iterator<State> ::type iter_t; typedef typename boost::iterator_difference<iter_t> ::type diff_t; bool ret = false; iter_t const marker = s.get_cur(); diff_t d = 0;

			if (P0::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P1::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P2::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P3::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P4::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P5::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P6::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P7::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P8::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P9::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P10::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P11::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P12::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P13::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P14::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P15::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P16::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P17::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P18::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);
			if (P19::parse(s, us)) { ret = true; d = std::max(std::distance(marker, s.get_cur()), d); } s.set_cur(marker);

			if (ret) { biscuit::state_advance(s, d); } return ret;
		}
	};

} } 
