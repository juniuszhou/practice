/*
 * public/ann/annlib.cpp
 * 2004-05-11 by ShanLanshan
 */
#include "public/ann/annbase.h"
#include "public/ann/annlib.h"
#include "public/ann/annfunc/annfunc.h"

namespace ann {

	AnnLib::AnnLib():m_inited(false) {}

	AnnLib::~AnnLib()
	{
	}

	bool AnnLib::init()
	{
		if (m_inited)
			return true;

		if (!g_func_factory.init())
			return false;

		m_inited = true;

		return true;
	}

	void AnnLib::finalize()
	{
		if (!m_inited)
			return;

		g_func_factory.finalize();
		m_inited = false;
	}

} // namespace ann
