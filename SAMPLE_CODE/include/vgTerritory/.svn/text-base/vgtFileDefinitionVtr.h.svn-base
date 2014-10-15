





#ifndef __VGTERRITORY_TFILEDEFINITIONVTR_H__
#define __VGTERRITORY_TFILEDEFINITIONVTR_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgTerritory/vgVgtrFile.h>

	
namespace vgTerritory {




	class VtrBrief;


	class VtrHeader : public StructVtrHeader
	{
	public:
		VtrHeader()
		{
			setDefault();
		}
		~VtrHeader()
		{
			
		}
	private:

		void setDefault();
	};
	

	typedef vgKernel::SharePtr<VtrHeader> VtrHeaderPtr;


	class VtrBrief
	{
	public:
		VtrBrief()
		{
			setDefault();
		}
		~VtrBrief()
		{
			
		}

	public:

		// load from whole buffer.
		bool getInfoFromBuffer( const String& filemetaname , 
			const char* const buffer, 
			const long& buffer_size );


	private:

		void setDefault();

	public:

		// 注意,保存的都是小写形式
		char _fileName[VTR_NAME_LENGTH];

		long  _metaFileOffset;
		long  _metaFileSize;
	
		VgtrHeader _vgtrHeader;
	};


	typedef vgKernel::SharePtr<VtrBrief> VtrBriefPtr;

	typedef std::vector<VtrBriefPtr> VtrBriefPtrVec;
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TFILEDEFINITIONVTR_H__