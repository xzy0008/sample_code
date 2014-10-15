



#ifndef __VGKRENDERERDATA_H__
#define __VGKRENDERERDATA_H__

#include <vgKernel/vgkForward.h>

	
namespace vgKernel {

	typedef int RendererDataType;

	enum RendereDataType
	{
		RDT_NO_TYPE = 0,

		RDT_DATABASE_PROFILE
	};

	class RendererData
	{
	public:
		RendererData() { dataType = RDT_NO_TYPE; }

		virtual ~RendererData() {};

	public:
		RendererDataType dataType;
	};

	class DatabaseRendererData : public RendererData
	{
	public:
		DatabaseRendererData()
		{
			dataType = RDT_DATABASE_PROFILE;
		}

	public:
		String profile;

	};


	typedef std::vector<RendererData*> RendererDataPtrVec;

	
	
}// end of namespace vgKernel
	


#endif // end of __VGKRENDERERDATA_H__

