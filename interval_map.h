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
public:
	std::map<K, V> m_map;

public:
	interval_map(V const& val) {
		m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	}

	V const& operator[](K const& key) const {
		return (--m_map.upper_bound(key))->second;
	}

private:
	inline V findLeftValue(typename std::map<K, V>::iterator itr)
	{
		if (itr != m_map.begin()) --itr;	// ADJUST TO OVERWRITE M_MAP.BEGIN() IF NECESSARY
		return itr->second;
	}

public:
	void assign(K const& keyBegin, K const& keyEnd, V const& val)
	{
		std::map<K, V>::iterator iterLower, iterUpper;
		V leftValue, rightValue;
		bool doNotExtend;

		if (!(keyBegin < keyEnd)) return;

		iterLower = m_map.lower_bound(keyBegin);
		leftValue = findLeftValue(iterLower);

		if (iterLower != m_map.end())
		{
			iterUpper = m_map.upper_bound(keyEnd);
			rightValue = findLeftValue(iterUpper);
			m_map.erase(iterLower, iterUpper);
		}
		else
			rightValue = leftValue;		// WHY: project Z to the left, WORK Z EXPANSE

		doNotExtend = (val != leftValue);
		if (doNotExtend) m_map.emplace(keyBegin, val);

		// use std::numeric_limits<K>::max() as infinity
		doNotExtend = (val != rightValue && keyEnd < std::numeric_limits<K>::max());
		if (doNotExtend) m_map.emplace(keyEnd, rightValue);
	}
};


