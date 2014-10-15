#pragma once

#include <string>

using std::string;

class DEMRect
{
public:
	DEMRect(CPoint point, CSize size, string name="Empty");
	
	DEMRect(int x, int y, int width, int height, string name="Empty");

	~DEMRect(void);

	const CPoint& GetTopLeft();
	
	const CSize&  GetSize();

private:
	CPoint _topLeft;
	
	CSize  _size;

	string _name;
 
};

inline const CPoint& DEMRect::GetTopLeft()
{
	return _topLeft;
}

inline const CSize& DEMRect::GetSize()
{
	return _size;
}
