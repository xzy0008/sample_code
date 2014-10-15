


#ifndef __VGMMESHDATAPLUS_H__
#define __VGMMESHDATAPLUS_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkVec3.h>
#include <vgMesh/vgmShadowMetaFace.h>



namespace vgMesh {

	class Mesh;
	class MeshData;

	/**
		@date 	2008/07/01  20:59	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGM_EXPORT MeshDataPlus
	{
	public:
		MeshDataPlus()
		{
			_fatherMesh = NULL;
			//_wholeChunkOfData = NULL;
			//_meshData = NULL;
			_vaway = NULL;
			_shadowMetaFaces = NULL;
			_shadowDisplayListID = 0;
		}
		~MeshDataPlus()
		{
			destroy();
		}
	

		bool importFromMeshData( MeshData* meshdata );
 

		// 当载入完成之后，设置Mesh标记
		void setFatherMesh( Mesh* father )
		{
			_fatherMesh = father;
		}

		void renderOnceInShadowMode();

		
		// 对shadow进行重新渲染
		void invalidateShadowRendering();

	private:

		void calcuateForShadow( const vgKernel::Vec3& lightDir );

	public:

		void destroy();

	private:

		Mesh* _fatherMesh;

	public:

		GLuint _shadowDisplayListID;


		//MeshData* _meshData;

		MeshRenderWayVertexArray* _vaway;
		//char*	_wholeChunkOfData;
		ShadowMetaFace* _shadowMetaFaces;
	};
	
	
	
}// end of namespace vgMesh

#endif // end of __VGMMESHDATAPLUS_H__