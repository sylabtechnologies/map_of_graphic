// make 2nd version for testing

#pragma once
#include <iostream>
#include <map>
#include <limits>
#include <stdexcept>

class interval_map
{
	friend std::ostream& operator<< (std::ostream& os, const interval_map &map);

private:
	std::map<int, char> m_map;

public:
	~interval_map() = default;							// OK to default
	interval_map(const interval_map&) = delete;			// no to copy and assignment
	interval_map &operator=(const interval_map&) = delete;

	interval_map(const char &val)
	{
		m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<int>::lowest(), val));
	}

	char const& operator[](const int key) const
	{
		return (--m_map.upper_bound(key))->second;
	}


	//void print()
	//{
	//	for (const auto &elem : m_map)
	//	{
	//		std::cout << "[" << elem.first << ", " << elem.second << "]" << std::endl;
	//	}

	//	std::cout << std::endl;
	//}
	
	void assign(const int keyBegin, const int keyEnd, const char val)
	{
		// if (!(keyBegin < keyEnd)) return; // ok throw illegal arg?
		// OK TO RESTRICT NUM LIMITS SIMILARLY?

		auto iterBegin = m_map.lower_bound(keyBegin);
		
		char leftValue;
		if (iterBegin == m_map.end())
		{
			auto res = m_map.emplace(keyBegin, val);
			leftValue = findLeftValue(res.first);
			m_map.emplace(keyEnd, leftValue);
			return;
		}
		else
		{
			leftValue = findLeftValue(iterBegin);
		}

		auto iterEnd = m_map.upper_bound(keyEnd);

		if (iterBegin != iterEnd)		// save 2 bin searches
			m_map.erase(iterBegin, iterEnd);

		m_map.emplace(keyBegin, val);
		m_map.emplace(keyEnd, leftValue);

	}

private:
	inline char findLeftValue(typename std::map<int, char>::iterator itr)
	{
		if (itr != m_map.begin()) --itr;  // seems like the corner case
		return itr->second;
	}

};

std::ostream& operator<< (std::ostream& os, const interval_map &map)
{
	auto iter = map.m_map.begin();

	while (iter != map.m_map.end())
	{
		os << "[" << iter->first << ", " << iter->second << "]";

		iter++;
		if (iter != map.m_map.end())
			os << std::endl;
	}

	return os;
}

