#ifndef RANGE_H
#define RANGE_H
namespace zr
{
	struct Range
	{
		float min, max;
		Range() {}
		bool overlaps(Range r)
		{
			return min <= r.max && max >= r.min;
		}
	};
}
#endif