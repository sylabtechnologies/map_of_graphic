#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <string>
#include <limits>
#include <stdexcept>

#define _MAX(a,b) (a > b ? a : b)
#define _MIN(a,b) (a < b ? a : b)

template<class K, class V> class interval_map
{
	friend void testtest();

private:
	std::map<K, V> m_map;

public:
	interval_map(V const& val) {
		m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	}

	V const& operator[](K const& key) const {
		return (--m_map.upper_bound(key))->second;
	}

	// the test
	std::vector<V> fill_it()
	{
		std::vector<V> result(300);

		auto indx = [](int i)->int { return i + 20; };

		for (auto iter = m_map.begin(); iter != m_map.end(); ++iter)
		{
			int i = _MAX(static_cast<int>(iter->first), -20);
			auto temp = iter; ++temp;

			int lim;
			if (temp != m_map.end())
				lim = _MIN(static_cast<int>(temp->first), 280);
			else
				lim = 280;

			while (i < lim)
			{
				int jj = indx(i);
				result[indx(i)] = iter->second;
				i++;
			}
		}

		return result;
	}

	// ***** THE RIGHT STUFF: BRUTE FORCE VECTOR 1-1 AND COMPARE
	// *** SEPARATION OF EACH INTERVAL ADJUSTMENT A REALLY GOOD IDEA!?
	void assign(K const& keyBegin, K const& keyEnd, V const& val)
	{
		std::map<K, V>::iterator iter_lo, iter_hi;

		if (m_map.empty()) throw std::runtime_error("interval_map::assign failure");

		// IT CANT BE EQUIVALENCE
		if (!(keyBegin < keyEnd)) throw std::runtime_error("interval_map::assign invalid argument");

		auto find_V = [](std::map<K, V>::iterator itr)->V { --itr; return itr->second; };

		// find right interval
		iter_hi = m_map.upper_bound(keyEnd);
		V rval = find_V(iter_hi);

		// find left interval
		iter_lo = m_map.lower_bound(keyBegin);
		V lval = find_V(iter_lo);

		m_map.erase(iter_lo, iter_hi);

		if (val != lval) m_map.emplace(keyBegin, val);

		if (val != rval) m_map.emplace(keyEnd, rval);
	}

};


