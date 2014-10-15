

#include <vgStableHeaders.h>
#include <vgTerritory/vgMeshDrawingData.h>


namespace vgTerritory {
	
	
	
	

	void MeshDrawingData::draw()
	{
		if ( _indices == NULL )
		{
			return;
		}



		glMultiDrawElements( GL_TRIANGLES, _counts , GL_UNSIGNED_SHORT, 
			(const GLvoid**)_indices , _primcount );
	}
}// end of namespace vgTerritory
