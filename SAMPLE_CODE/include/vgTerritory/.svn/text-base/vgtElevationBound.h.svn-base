


#ifndef __VGTELEVATIONBOUND_H__
#define __VGTELEVATIONBOUND_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkVec2.h>


	
namespace vgTerritory {

	using namespace vgKernel;


	class  VGT_EXPORT ElevationBound
	{
	public:
		ElevationBound()
		{
		}
		ElevationBound( const Vec2 Fmin , const Vec2 Fmax )
			: minPos(Fmin) , maxPos(Fmax) 
		{
		}
		ElevationBound( const float Fminx , const float Fminy , const float Fmaxx , const float Fmaxy )
		{
			minPos = Vec2( Fminx , Fminy );
			maxPos = Vec2( Fmaxx , Fmaxy );
		}
		~ElevationBound()
		{
		}

		inline ElevationBound& operator = ( const ElevationBound& rkrect )
		{
			minPos = rkrect.minPos;
			maxPos = rkrect.maxPos;
			return *this;
		}

		inline ElevationBound operator - () const
		{
			return ElevationBound( -minPos , -maxPos );
		}

		inline ElevationBound& operator /= ( const float fScalar )
		{
			maxPos /= fScalar;
			minPos /= fScalar;

			return *this;
		}
		inline bool operator == ( const ElevationBound& rkrect ) const
		{
			return rkrect.minPos == minPos && rkrect.maxPos == maxPos;
		}
		inline bool operator != ( const ElevationBound& rkrect ) const
		{
			return rkrect.minPos != minPos || rkrect.maxPos != maxPos;
		}

		/// 平移函数.给出一个坐标,平移到此处.
		inline ElevationBound& translate(const Vec2& rkpos)
		{
			minPos += rkpos;
			maxPos += rkpos;
			return *this;
		}

		/// 平移函数.给出一个坐标,平移到此处.
		inline ElevationBound translateCopy(const Vec2& rkpos) const
		{
			ElevationBound copy;
			copy.minPos = this->minPos + rkpos;
			copy.maxPos = this->maxPos + rkpos;
			return copy;
		}



		/// 测试2个ElevationBound是否有重叠.
		/// 注意:对于坐标这里和下面的findIntersection有注意的地方:
		/// 在矢量系统中,下面的情况应该算上相交.
		/// 举个例子:
		///		ElevationBound  bb( Vec2(0) , Vec2(100) );
		///		ElevationBound  cc ( Vec2(100) , Vec2(200) ) ;
		inline bool testIntersection (const ElevationBound& rkBox) const
		{
			assert( isSafe() && "The ElevationBound is not safe.");
			for (int i = 0; i < 2; i++)
			{
				if (maxPos[i] < rkBox.minPos[i] || minPos[i] > rkBox.maxPos[i])
				{
					return false;
				}
			}
			return true;
		} 

		/// 相交测试.若this和rkBox有重叠,则返回true,并将重叠部分的RECT保存在rkIntr中.
		bool findIntersection (const ElevationBound& rkBox,
			ElevationBound& rkIntr) const
		{
			int i;
			if ( testIntersection( rkBox ) == false )
			{
				return false;
			}

			for (i = 0; i < 2; i++)
			{
				if (maxPos[i] <= rkBox.maxPos[i])
				{
					rkIntr.maxPos[i] = maxPos[i];
				}
				else
				{
					rkIntr.maxPos[i] = rkBox.maxPos[i];
				}

				if (minPos[i] <= rkBox.minPos[i])
				{
					rkIntr.minPos[i] = rkBox.minPos[i];
				}
				else
				{
					rkIntr.minPos[i] = minPos[i];
				}
			}
			return true;
		}


		/// 查看点是否在本rect内.
		inline bool testInside(const Vec2& point) const
		{
			assert( isSafe() && "The ElevationBound is not safe.");
			for (int i = 0; i < 2; i++)
			{
				if (maxPos[i] <= point[i] || minPos[i] >= point[i])
				{
					return false;
				}
			}
			return true;
		}

		/// 查看参数rect是否在本rect内部,注意本rect和参数Rect的关系.
		/// 注意:重合时的情况也计算在内.
		/// 即重合时,返回true.
		inline bool testInside(const ElevationBound& testRect) const
		{
			if( isSafe() == false )
			{
				assert( isSafe() && "The ElevationBound is not safe.");
			}
			for (int i = 0; i < 2; i++)
			{
				if (maxPos[i] < testRect.maxPos[i] || minPos[i] > testRect.minPos[i])
				{
					return false;
				}
			}
			return true;
		}


		inline float getWidth() const
		{
			assert( isSafe() && "The ElevationBound is not safe.");
			return maxPos.x - minPos.x;
		}

		inline Vec2 getCenter() const
		{
			return Vec2(( maxPos + minPos )/2.0f);
		}

		inline float getHeight() const 
		{
			assert( isSafe() && "The ElevationBound is not safe.");
			return maxPos.y - minPos.y;
		}

		inline bool isSafe() const
		{
			return minPos.x <= maxPos.x && minPos.y <= maxPos.y;
		}

		inline void makeSafe()
		{
			Vec2 _tmin = minPos.floorProduct( maxPos );
			Vec2 _tmax = minPos.ceilProduct( maxPos );

			minPos = _tmin;
			maxPos = _tmax;
		}

		inline String getDetails() const
		{
			std::ostringstream o;

			o << "ElevationBound( minPos = " << minPos.getDetails()
				<< " , maxPos = " << maxPos.getDetails() 
				<< " , width = " << this->getWidth()
				<< " , height = " << this->getHeight()
				<< " )";

			return o.str();
		}

		inline void merge( const ElevationBound& rect )
		{
			assert( isSafe() );

			this->minPos = rect.minPos.floorProduct( this->minPos );
			this->maxPos = rect.maxPos.ceilProduct( this->maxPos );
		}

		bool isEmpty() const
		{
			return *this == ZERO;
		}

	public:

		/// 注意生成相应的set 和get函数.
		Vec2 minPos;
		Vec2 maxPos;

		static const ElevationBound ZERO;

		static const ElevationBound UNIT_BOUND;

	};


	
}// end of namespace vgTerritory
	


#endif // end of __VGTELEVATIONBOUND_H__