#include <vgStableHeaders.h>

#include "TifRect.h"

TifRect::TifRect(CPoint point, CSize size, string name)
				:_topLeft(point), _size(size), _name(name)
{

}

TifRect::TifRect(int x, int y, int width, int height, string name)
				:_topLeft(x, y), _size(width, height), _name(name)
{

}

TifRect::~TifRect(void)
{
}
