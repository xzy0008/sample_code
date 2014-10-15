


#ifndef __VGTERRITORY_TVGTRGENERATOR_H__
#define __VGTERRITORY_TVGTRGENERATOR_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgVgtrFile.h>

	
namespace vgTerritory {

	/**
		@date 	2008/09/02  10:14	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGT_EXPORT VgtrGenerator
	{
	private:
		VgtrGenerator()
		{
			
		}
		~VgtrGenerator()
		{
			
		}
	
	public:


		/**
			通过整个的vgtr块生成vgtr序列.
			参数:
				layer: 指代那一层.如 layer==0时,将产生最精细一层的切块
				N: 指代渲染时候的mesh层级,以此参数来切块
		*/
		static VgtrFilePtrVec* generateSpecificLayer( const VgtrFilePtr wholevgtr , 
			const long& layer );
	


		/**
			若成功,返回的是所有的文件名的列表
		*/
		static vgKernel::StringVectorPtr generateLayers( const VgtrFilePtr wholevgtr ,
			const String& output_path );


		/**
			得到层级数目
		*/
		static long getLayerNum( const VgtrFilePtr vgtr , const long& N );

	private:

		static inline float getFromTable( float* data , long width , long height, 
			long x , 	long y )
		{
			if ( x > (width - 1) || y > ( height -1 ) )
			{
				return 0.0f;
			}

			return data[ width * y + x ];
		}

	
	};
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TVGTRGENERATOR_H__