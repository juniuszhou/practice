typedef map<int, CDocObserver*> MAP_OBSERVER;
	MAP_OBSERVER m_mapObservers;
	typedef pair<int, CDocObserver*> PAIR_OBSERVER;

void Attach(CDocObserver* pObserver)
	{
		if (NULL == pObserver)
		{return;	}
		m_mapObservers.insert(PAIR_OBSERVER(m_nCnt, pObserver));
		pObserver->SetID(m_nCnt);
		m_nCnt++;
	}
	void Detach(CDocObserver* pObserver)
	{
		if (NULL == pObserver)
		{return;	}
		MAP_OBSERVER::iterator it;
		for (it=m_mapObservers.begin(); it!=m_mapObservers.end();)
		{
			if (pObserver == it->second)
			{
				m_mapObservers.erase(it++);
			}
			else
			{
				it++;
			}
		}
	}


