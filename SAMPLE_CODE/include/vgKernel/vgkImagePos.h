


#ifndef __VGKIMAGEPOS_H__
#define __VGKIMAGEPOS_H__

#include <vgKernel/vgkForward.h>

	
namespace vgKernel {


	/**
		@date 	2007/04/28  21:04	
		@author  xy
			
		@brief 	
			ͼ��2D������.���Ա���ͼ���ϵ�ĳ����.ע��ʹ��ʱ������������.
			
		@note �Ժ���Զ���ͨ�õ�template vector2 ��,��������ʡȥ��Ϊ��λ���������д�鷳.
			
		@see    
	*/
	class  VGK_EXPORT ImagePos 
	{
	//private:
	public:

		/**
			����Ϊunion,ʹ���ʵķ�ʽ������.
		*/
		union
		{
			struct
			{  long x , y ;  };
			long v[2];
		};	

	public:

		inline ImagePos()
			: x( 0 ), y( 0 )
		{
		}

		inline ImagePos(const long fX, const long fY )
			: x( fX ), y( fY )
		{
		}
		inline explicit ImagePos( const long scaler )
			: x( scaler), y( scaler )
		{
		}

		/**
			����[]��,����assert���.
		*/
		inline long operator [] ( const size_t i ) const;
		inline long& operator [] ( const size_t i );

		/**
			��ֵ�����������.
		*/
		inline ImagePos& operator = ( const ImagePos& rkVector );
		inline ImagePos& operator = ( const long fScalar);

		/**
			�Ƚ������������.
		*/
		inline bool operator == ( const ImagePos& rkVector ) const;
		inline bool operator != ( const ImagePos& rkVector ) const;


		// arithmetic operations
		inline ImagePos operator + ( const ImagePos& rkVector ) const;
		inline ImagePos operator - ( const ImagePos& rkVector ) const;
		inline ImagePos operator * ( const long fScalar ) const;
		inline ImagePos operator * ( const ImagePos& rhs) const;
		inline ImagePos operator / ( const long fScalar ) const;
		inline ImagePos operator / ( const ImagePos& rhs) const;
		inline const ImagePos& operator + () const;
		inline ImagePos operator - () const;

		/**
			�����������.
		*/
		inline friend ImagePos operator * ( const long fScalar, const ImagePos& rkVector );
		inline friend ImagePos operator / ( const long fScalar, const ImagePos& rkVector );
		inline friend ImagePos operator + (const ImagePos& lhs, const long rhs);
		inline friend ImagePos operator + (const long lhs, const ImagePos& rhs);
		inline friend ImagePos operator - (const ImagePos& lhs, const long rhs);
		inline friend ImagePos operator - (const long lhs, const ImagePos& rhs);

		/**
			�߼����������������.
		*/
		inline ImagePos& operator += ( const ImagePos& rkVector );
		inline ImagePos& operator += ( const long fScaler );
		inline ImagePos& operator -= ( const ImagePos& rkVector );
		inline ImagePos& operator -= ( const long fScaler );
		inline ImagePos& operator *= ( const long fScalar );
		inline ImagePos& operator *= ( const ImagePos& rkVector );
		inline ImagePos& operator /= ( const long fScalar );
		inline ImagePos& operator /= ( const ImagePos& rkVector );


		/**
			�Ƚ������������.
		*/
		inline bool operator < ( const ImagePos& rhs ) const;
		inline bool operator > ( const ImagePos& rhs ) const;

		inline bool operator <= ( const ImagePos& rhs ) const;
		inline bool operator >= ( const ImagePos& rhs ) const;


		inline ImagePos floorProduct( const ImagePos& c ) const
		{
			ImagePos cmp = c;
			if( cmp.x > x ) cmp.x = x;
			if( cmp.y > y ) cmp.y = y;
			return cmp;
		}

		inline ImagePos ceilProduct( const ImagePos& c ) const
		{
			ImagePos cmp = c;
			if( cmp.x < x ) cmp.x = x;
			if( cmp.y < y ) cmp.y = y;
			return cmp;
		}

		/**
			�õ��������Ϣ.
		*/
		String getDetails() const;

	public:

		/// ����.ԭ��ֵ.
		static const ImagePos ZERO;

		/// ����.���ֵ.
		static const ImagePos MAX;

		/// ����.��Сֵ.
		static const ImagePos MIN;
	};
	
	#include "vgkImagePos.inl"
	
}// end of namespace vgKernel
	


#endif // end of __VGKIMAGEPOS_H__