/*
 * public/ann/annfunc/annfunc.cpp
 * 2004-02-16 by ShanLanshan
 */
#include <math.h>
#include "public/ann/annfunc/annfunc.h"
#include "public/ann/annfunc/hyperbola_tangent.h"
#include "public/ann/annfunc/sigmoid.h"
#include "public/ann/annfunc/sign.h"
#include "public/ann/annfunc/sin.h"
#include "public/ann/annfunc/sech6.h"

using namespace ann::annfunc;

namespace ann {

	AnnFuncGroupFactory g_func_factory;
	AnnFuncGroupFactory::AnnFuncGroupFactory():m_inited(false){}
	AnnFuncGroupFactory::~AnnFuncGroupFactory()
	{
		finalize();
	}

	void AnnFuncGroupFactory::finalize()
	{
		if (!m_inited)
			return;

		for (int i=0; i<m_funcgroup_count; ++i) {
			assert(m_funcgroup[i] != NULL);
			assert(m_funcgroup[i]->finalize != NULL);
			m_funcgroup[i]->finalize();
		}
		m_inited = false;
	}

	bool AnnFuncGroupFactory::init()
	{
		int i = 0;

		if (m_inited)
			return true;

		m_funcgroup[i++] = &hyperbola_tangent::g_funcgroup;
		m_funcgroup[i++] = &sigmoid::g_funcgroup;
		m_funcgroup[i++] = &sign::g_funcgroup;
		m_funcgroup[i++] = &sin::g_funcgroup;
		m_funcgroup[i++] = &sech6::g_funcgroup;
		m_funcgroup[i++] = &sech6::g_funcgroup_cache;
		m_funcgroup_count = i;

		for (i=0; i<m_funcgroup_count; ++i) {
			assert(m_funcgroup[i] != NULL);
			assert(m_funcgroup[i]->init != NULL);
			if (!m_funcgroup[i]->init())
				return false;
		}

		m_inited = true;

		return true;
	}


	AnnFuncGroup *annfunc_get(const char *name)
	{
		AnnFuncGroup *func;
		for (int i=0; i<g_func_factory.m_funcgroup_count; ++i) {
			func = g_func_factory.m_funcgroup[i];
			assert(func != NULL);
			if (strcmp(func->name, name))
				continue;
			return func;
		}

		return NULL;
	}

}	// namespace ann
