#pragma once
#include <vector>
#include <cassert>

template<typename T, typename Comparator = std::less<T>>
class PriorityVector {
public:
	using Iterator = std::vector<T>::iterator;
	using cIterator = std::vector<T>::const_iterator;

	void AddValue(const T& value)
	{
		Iterator iter = std::lower_bound(vector.begin(), vector.end(),
										 value, Comparator());

		if (iter != vector.end())
			vector.insert(iter, value);
		else
			vector.push_back(value);
	}

	void Erase(const T& value)
	{
		Iterator iter = std::find(vector.begin(), vector.end(), value);

		if (iter != vector.end())
			vector.erase(iter);
	}

	void Erase(Iterator iter)
	{
		vector.erase(iter);
	}

	void Erase(cIterator iter)
	{
		vector.erase(iter);
	}

	T& operator[](size_t index) {
		assert(index > 0 && index < vector.size());
		return vector[index];
	}

	Iterator begin() {
		return vector.begin();
	}

	Iterator end() {
		return vector.end();
	}

	cIterator cbegin() const {
		return vector.cbegin();
	}

	cIterator cend() const {
		return vector.cend();
	}

private:
	std::vector<T> vector;
};