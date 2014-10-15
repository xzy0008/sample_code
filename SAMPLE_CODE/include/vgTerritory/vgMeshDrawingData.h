


#ifndef __VGTERRITORY_MESHDRAWINGDATA_H__
#define __VGTERRITORY_MESHDRAWINGDATA_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>


namespace vgTerritory {

	/**
		@date 	2008/04/18  10:30	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class MeshDrawingData
	{
	public:
		MeshDrawingData()
		{
			setNull();
		}

		~MeshDrawingData()
		{
			
		}


	public:

		void setNull()
		{
			_indices = NULL;
			_counts = NULL;
			_primcount = 0;
		}

		void draw();

	public:

		GLvoid** _indices;
		GLsizei* _counts;

		int _primcount;

		GLsizei _splitCount;

		// »¹ÓÐtexture?
	};
	
	
	
}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_MESHDRAWINGDATA_H__