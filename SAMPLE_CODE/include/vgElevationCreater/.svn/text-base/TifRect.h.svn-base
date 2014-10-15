#pragma once

#include <string>

using std::string;

class TifRect
{
public:
	TifRect(CPoint point, CSize size, string name="Empty");
	
	TifRect(int x, int y, int width, int height, string name="Empty");

	~TifRect(void);

	const CPoint& GetTopLeft();
	
	const CSize&  GetSize();

private:
	CPoint _topLeft;
	
	CSize  _size;

	string _name;

	void   *name;
};

inline const CPoint& TifRect::GetTopLeft()
{
	return _topLeft;
}

inline const CSize& TifRect::GetSize()
{
	return _size;
}
