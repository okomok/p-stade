

#if defined(_WIN32_WCE)
	#pragma warning(push)
	#pragma warning(disable: 4530) // C++ exception handler used
#endif


#if (_MSC_VER < 1300)
	#pragma warning(push)
	#pragma warning(disable: 4097) // typename used as synonym for class-name
	#pragma warning(disable: 4100) // unreferenced formal parameter
	#pragma warning(disable: 4201) // nameless struct/union
	#pragma warning(disable: 4510) // copy constructor could not be generated
	#pragma warning(disable: 4512) // assignment operator could not be generated
	#pragma warning(disable: 4610) // user defined constructor required
	#pragma warning(disable: 4663) // C++ language change: to explicitly specialize class template
#endif


#if (_MSC_VER < 1400)
	#pragma warning(push)
	#pragma warning(disable: 4675) // resolved overload was found by argument-dependent lookup
#endif


#if (_MSC_VER >= 1400)
	#pragma warning(push)
	// #pragma warning(disable: 4512) // assignment operator could not be generated
	#pragma warning(disable: 4819) // character that cannot be represented in the current code page
	#if !defined(_SCL_SECURE_NO_DEPRECATE)
		#define _SCL_SECURE_NO_DEPRECATE
	#endif
#endif
