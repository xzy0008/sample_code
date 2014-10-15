



#include <vgStableHeaders.h>
#include <vgImage/vgiBatchProcessor.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgImage/vgiFreeImageWrapper.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>


namespace vgImage {
	
	
	
	
	//----------------------------------------------------------------
	vgKernel::StringVectorPtr BatchProcessor::process( 
		const StringVectorPtr src_img_list , const String& temppath,
		const String& out_extension , const GLenum& dds_format ,
		vgKernel::ProcessNotifier* notifier,
		const bool& remove_input_files , 
		const float& resize_ratio /*= 1.0f */,
		const bool& use_ext_as_name /*= false */)
	{
		assert( resize_ratio > 0.0f && resize_ratio <= 1.0f );

		if ( resize_ratio <= 0.0f || resize_ratio > 1.0f )
		{
			return StringVectorPtr();
		}

		using namespace HugeProcess;

		assert( out_extension == "dds" );

		if ( src_img_list.isNull() == true || src_img_list->empty() == true )
		{
			return StringVectorPtr();
		}

		StringVectorPtr ret( new StringVector );

		HugeJobsStringVector boss( ret.getPointer() , notifier );

		StringVector::iterator iter = src_img_list->begin();
		StringVector::iterator iter_end = src_img_list->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			PieceJobString* job = new DealOneImage( *iter , temppath , out_extension , 
				dds_format , &boss , notifier , remove_input_files ,
				resize_ratio , use_ext_as_name );

			boss.submit( job );      //放入堆栈
		}

		boss.doAndWait();

		if ( ret->empty() == true )
		{
			return StringVectorPtr();
		}

		return ret;
	}
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	String BatchProcessor::DealOneImage::doJobRetString()
	{
		String ret = doJobImpl();


		if ( ret != "" )
		{
			if ( _removeFiles == true )
			{
				vgKernel::SystemUtility::removeFile( _src , false );
			}
		}

		return ret;
	}

	String BatchProcessor::DealOneImage::doJobImpl()
	{
		String metaname;
		String dst;
		
		if ( _useExtAsName == true )
		{
			String oldext = StringUtility::getFileExtension( _src );
			metaname = StringUtility::getFilenameWithoutExtFromAbsPath( _src );
			metaname += "_";
			metaname += oldext;
		}
		else
		{
			metaname = StringUtility::getFilenameWithoutExtFromAbsPath( _src );
		}

		dst = _temp + "\\" + metaname + "." + _ext;


		FreeImageWrapper img;
		bool loadok = img.loadFromFile( _src );
		if ( loadok == false )
		{
			return "";
		}

		long oldwidth = img.getWidth();
		long oldheight = img.getHeight();

		long newwidth = oldwidth * _resizeRatio;
		newwidth = ( newwidth > 0 ? newwidth : 1 );
		newwidth = ( newwidth > 2048 ? 2048 : newwidth );

		long newheight  = oldheight * _resizeRatio;
		newheight = ( newheight > 0 ? newheight : 1 );
		newheight = ( newheight > 2048 ? 2048 : newheight );

		if ( newwidth != oldwidth || newheight != oldheight )
		{
			//------------------------------------------
			// 这个时候需要resize
			//------------------------------------------
			bool resizeok = img.resize( ImageSize( newwidth , newheight ) );
			assert( resizeok == true );
		}

		if ( _ext == "dds" )
		{
			bool saveok = img.saveToDdsFile( dst , _format , true );
			if ( saveok == false )
			{
				return "";
			}
		}
		else
		{
			bool saveok = img.saveToFile( dst );
			if ( saveok == false )
			{
				return "";
			}
		}

		return dst;
	}
}// end of namespace vgImage
