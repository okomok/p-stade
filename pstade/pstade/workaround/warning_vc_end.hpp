

#if (_MSC_VER >= 1400)
	#pragma warning(pop)
	#if defined(_SCL_SECURE_NO_DEPRECATE)
		#undef _SCL_SECURE_NO_DEPRECATE
	#endif
#endif


#if (_MSC_VER < 1400)
	#pragma warning(pop)
#endif


#if (_MSC_VER < 1300)
	#pragma warning(pop)
#endif


#if defined(_WIN32_WCE)
	#pragma warning(pop)
#endif

