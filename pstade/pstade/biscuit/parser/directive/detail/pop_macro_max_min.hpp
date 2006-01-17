
#if defined(_MSC_VER)
	#if defined(BISCUIT_max_defined)
		#pragma pop_macro("max")
		#undef BISCUIT_max_defined
	#endif
	#if defined(BISCUIT_min_defined)
		#pragma pop_macro("min")
		#undef BISCUIT_min_defined
	#endif
#endif
