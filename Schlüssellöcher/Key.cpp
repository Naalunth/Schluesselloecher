#include "Key.h"

#include <algorithm>

Schlüssellöcher::Key::Key()
{
}

Schlüssellöcher::Key::Key(size_t edgeLength)
	:_size(edgeLength),
	bits(edgeLength*edgeLength)
{
}

Schlüssellöcher::Key::~Key()
{
}

size_t Schlüssellöcher::Key::size() const
{
	return _size;
}

Schlüssellöcher::Key Schlüssellöcher::Key::flipped() const
{
	Key copy(*this);
	for (int i = 0; i < _size; ++i)
	{
		std::reverse(copy.bits.begin() + (i*_size), copy.bits.begin() + (i*_size + _size));
	}
	return copy;
}

double Schlüssellöcher::Key::differenceToKey(const Key & other) const
{
	if (size() != other.size()) return -1;
	int error = 0;
	auto a = bits.begin(), b = other.bits.begin();
	while (a != bits.end())
		if (*a++ != *b++) error++;
	return (double) error / (double) bits.size();
}

double Schlüssellöcher::Key::meanDifferenceWithFlipped(const Key & other) const
{
	const Key& a = *this, b = flipped(), c = other, d = other.flipped();
	return (a.differenceToKey(c) + a.differenceToKey(d) + b.differenceToKey(c) + b.differenceToKey(d)) / 4;
}
