#ifndef PSTADE_TOMATO_GUID_HPP
#define PSTADE_TOMATO_GUID_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// But template arguments needs non-reference.


#include <pstade/apple/sdk/basetyps.hpp> // IID
#include <boost/preprocessor/cat.hpp>

template< class T, class Guid >
struct comqi_ptr :
	ATL::CComPtr<T>
{
private:
	typedef ATL::CComPtr<T> super_t;

public:
	comqi_ptr()
	{ }

	comqi_ptr(T* lp) :
		super_t(lp)
	{ }

	comqi_ptr(const comqi_ptr<T, piid>& lp) :
		super_t(lp.p)
	{
	}

	comqi_ptr(IUnknown *lp)
	{
		if (lp != NULL)
			lp->QueryInterface(*piid, (void **)&p);
	}

	T* operator=(T *lp)
	{
		return static_cast<T*>(ATL::AtlComPtrAssign((IUnknown**)&p, lp));
	}

	T* operator=(const comqi_ptr<T,piid>& lp)
	{
		return static_cast<T*>(ATL::AtlComPtrAssign((IUnknown**)&p, lp.p));
	}

	T* operator=(IUnknown *lp)
	{
		return static_cast<T*>(ATL::AtlComQIPtrAssign((IUnknown**)&p, lp, *piid));
	}
};

//Specialization to make it work
template<>
class comqi_ptr<IUnknown, &IID_IUnknown> : public CComPtr<IUnknown>
{
public:
	comqi_ptr() throw()
	{
	}
	comqi_ptr(IUnknown* lp) throw()
	{
		//Actually do a QI to get identity
		if (lp != NULL)
			lp->QueryInterface(__uuidof(IUnknown), (void **)&p);
	}
	comqi_ptr(const comqi_ptr<IUnknown,&IID_IUnknown>& lp) throw() :
		CComPtr<IUnknown>(lp.p)
	{
	}
	IUnknown* operator=(IUnknown* lp) throw()
	{
		//Actually do a QI to get identity
		return AtlComQIPtrAssign((IUnknown**)&p, lp, __uuidof(IUnknown));
	}
	IUnknown* operator=(const comqi_ptr<IUnknown,&IID_IUnknown>& lp) throw()
	{
		return AtlComPtrAssign((IUnknown**)&p, lp.p);
	}
};

typedef comqi_ptr<IDispatch, &__uuidof(IDispatch)> CComDispatchDriver;

#define com_cast ATL::comqi_ptr



#endif
