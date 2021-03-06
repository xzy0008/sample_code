


#ifndef __VGKIMAGERECT_H__
#define __VGKIMAGERECT_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkImagePos.h>

	
namespace vgKernel {


	class ImageRect;

	/// 封装图像大小.
	class  VGK_EXPORT ImageSize
	{
	public:
		ImageSize()
			: width (0) , height(0)
		{

		}
		ImageSize( long w , long h)
			: width (w) , height(h)
		{

		}
		~ImageSize()
		{

		}

		inline bool operator == ( const ImageSize& size ) const
		{
			return size.width == width && size.height == height;
		}
		inline bool operator != ( const ImageSize& size ) const
		{
			return size.width != width || size.height != height;
		}

		inline ImageRect getLocalRect() const;

		inline ImagePos getMaxPos() const
		{
			return ImagePos( getWidth() , getHeight() );
		}

		inline const long		getWidth() const 
		{ 
			return this->width; 
		}

		inline long&		getWidth()  
		{ 
			return this->width; 
		}

		inline void		setWidth( const long& val ) 
		{ 
			this->width = val;
		}

		inline const long		getHeight() const 
		{ 
			return this->height; 
		}

		inline long&		getHeight()  
		{ 
			return this->height; 
		}

		inline void		setHeight( const long& val ) 
		{ 
			this->height = val;
		}

		inline String getDetails() const
		{
			std::ostringstream o;
			o<< "ImageSize( width = " << width
				<< " , height = " <<  height << " )";

			return o.str();
		}

	private:
		long height;
		long width;

	};

	const ImageSize IMAGESIZE_ZERO = ImageSize(0,0);


	class  VGK_EXPORT ImageRect
	{
	public:
		ImageRect()
		{
		}
		ImageRect( const ImagePos Fmin , const ImagePos Fmax )
			: minPos(Fmin) , maxPos(Fmax) 
		{
		}
		ImageRect( const long Fminx , const long Fminy , const long Fmaxx , const long Fmaxy )
		{
			minPos = ImagePos( Fminx , Fminy );
			maxPos = ImagePos( Fmaxx , Fmaxy );
		}
		~ImageRect()
		{
		}

		inline ImageRect& operator = ( const ImageRect& rkrect )
		{
			minPos = rkrect.minPos;
			maxPos = rkrect.maxPos;
			return *this;
		}

		inline ImageRect operator - () const
		{
			return ImageRect( -minPos , -maxPos );
		}

		inline ImageRect& operator /= ( const long fScalar )
		{
			maxPos /= fScalar;
			minPos /= fScalar;

			return *this;
		}
		inline bool operator == ( const ImageRect& rkrect ) const
		{
			return rkrect.minPos == minPos && rkrect.maxPos == maxPos;
		}
		inline bool operator != ( const ImageRect& rkrect ) const
		{
			return rkrect.minPos != minPos || rkrect.maxPos != maxPos;
		}

		/// 平移函数.给出一个坐标,平移到此处.
		inline ImageRect& translate(const ImagePos& rkpos)
		{
			minPos += rkpos;
			maxPos += rkpos;
			return *this;
		}

		/// 平移函数.给出一个坐标,平移到此处.
		inline ImageRect translateCopy(const ImagePos& rkpos) const
		{
			ImageRect copy;
			copy.minPos = this->minPos + rkpos;
			copy.maxPos = this->maxPos + rkpos;
			return copy;
		}


		/// 查看x轴上是否有重叠
		inline bool hasXOverlap (const ImageRect& rkBox) const
		{
			assert( isSafe() && "The ImageRect is not safe.");
			return maxPos[0] >= rkBox.minPos[0] && minPos[0] <= rkBox.maxPos[0];
		}
		/// 查看y轴上是否有重叠
		inline bool hasYOverlap (const ImageRect& rkBox) const
		{
			assert( isSafe() && "The ImageRect is not safe.");
			return maxPos[1] >= rkBox.minPos[1] && minPos[1] <= rkBox.maxPos[1];
		}

		/// 测试2个ImageRect是否有重叠.
		/// 注意:对于坐标这里和下面的findIntersection有注意的地方:
		/// 由于是离散值系统,故相切的情况不属于相交.
		/// 举个例子:
		///		ImageRect  bb( ImagePos(0) , ImagePos(100) );
		///		ImageRect  cc ( ImagePos(100) , ImagePos(200) ) ;
		///		并没有相交,这样方便运算.
		///	但在矢量系统中,这样的情况应该算上相交.
		inline bool testIntersection (const ImageRect& rkBox) const
		{
			assert( isSafe() && "The ImageRect is not safe.");
			for (int i = 0; i < 2; i++)
			{
				if (maxPos[i] <= rkBox.minPos[i] || minPos[i] >= rkBox.maxPos[i])
				{
					return false;
				}
			}
			return true;
		} 

		/// 举个例子:
		///		ImageRect  bb( ImagePos(0) , ImagePos(100) );
		///		ImageRect  cc ( ImagePos(100) , ImagePos(200) ) ;
		///		这应该算得上相交!!!
		inline bool testIntersection2(const ImageRect& rkBox) const
		{
			assert( isSafe() && "The ImageRect is not safe.");
			for (int i = 0; i < 2; i++)
			{
				if (maxPos[i] < rkBox.minPos[i] || minPos[i] > rkBox.maxPos[i])
				{
					return false;
				}
			}
			return true;
		}

		bool findIntersection2 (const ImageRect& rkBox,
			ImageRect& rkIntr) const
		{
			int i;
			if ( testIntersection2( rkBox ) == false )
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

		/// 相交测试.若this和rkBox有重叠,则返回true,并将重叠部分的RECT保存在rkIntr中.
		// The return value is 'true' if there is overlap.  In this case the
		// intersection is stored in rkIntr.  If the return value is 'false',
		// if there is no overlap.  In this case rkIntr is undefined.
		bool findIntersection (const ImageRect& rkBox,
			ImageRect& rkIntr) const
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
		inline bool testInside(const ImagePos& point) const
		{
			assert( isSafe() && "The ImageRect is not safe.");
			for (int i = 0; i < 2; i++)
			{
				if (maxPos[i] < point[i] || minPos[i] > point[i])
				{
					return false;
				}
			}
			return true;
		}

		/// 查看参数rect是否在本rect内部,注意本rect和参数Rect的关系.
		/// 注意:重合时的情况也计算在内.
		/// 即重合时,返回true.
		inline bool testInside(const ImageRect& testRect) const
		{
			if( isSafe() == false )
			{
				assert( isSafe() && "The ImageRect is not safe.");
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

		/**
			其实这里是不对的.
			应该为maxPos.x - minPos.x + 1
			为了兼容,保持这样
		*/
		inline long getWidth() const
		{
			assert( isSafe() && "The ImageRect is not safe.");
			return maxPos.x - minPos.x;
		}

		inline ImagePos getCenter() const
		{
			return ImagePos(( maxPos + minPos )/2);
		}

		inline long getHeight() const 
		{
			assert( isSafe() && "The ImageRect is not safe.");
			return maxPos.y - minPos.y;
		}

		inline ImageSize getImageSize() const
		{
			return ImageSize( getWidth() , getHeight() );
		}

		inline void setImageSize( const ImageSize& imgsize )
		{
			this->maxPos.x = this->minPos.x + imgsize.getWidth();
			this->maxPos.y = this->minPos.y + imgsize.getHeight();
		}

		inline bool isSafe() const
		{
			return minPos <= maxPos;
		}

		inline void makeSafe()
		{
			ImagePos _tmin = minPos.floorProduct( maxPos );
			ImagePos _tmax = minPos.ceilProduct( maxPos );

			minPos = _tmin;
			maxPos = _tmax;
		}

		/// 以下依次得到rect的四个点,方向为从左上角顺时针开始.
		/// 范围为从0-3
		/// 比如getPos(2)指的是左下角的点.
		inline ImagePos getPos( const long& n ) const
		{
			assert( n >= 0 && n <4 );
			switch( n % 4 )
			{
			case 0:
				return minPos;
			case 1:
				return ImagePos( minPos.y , maxPos.x );
			case 2:
				return maxPos;
			case 3:
				return ImagePos( minPos.x , maxPos.y );
			}
			return minPos;
		}

		inline String getDetails() const
		{
			std::ostringstream o;

			o << "ImageRect( minPos = " << minPos.getDetails()
				<< " , maxPos = " << maxPos.getDetails() 
				<< " , width = " << this->getWidth()
				<< " , height = " << this->getHeight()
				<< " )";

			return o.str();
		}

		inline void merge( const ImageRect& rect )
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
		ImagePos minPos;
		ImagePos maxPos;

		static const ImageRect ZERO;

	};


	inline ImageRect ImageSize::getLocalRect() const
	{
		return ImageRect( ImagePos::ZERO ,ImagePos( width , height ));
	}
	
	
}// end of namespace vgKernel
	


#endif // end of __VGKIMAGERECT_H__