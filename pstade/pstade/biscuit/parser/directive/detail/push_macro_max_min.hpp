
#if defined(_MSC_VER)
	#if defined(max)
		#pragma push_macro("max")
		#undef max
		#define BISCUIT_max_defined
	#endif
	#if defined(min)
		#pragma push_macro("min")
		#undef min
		#define BISCUIT_min_defined
	#endif
#endif
