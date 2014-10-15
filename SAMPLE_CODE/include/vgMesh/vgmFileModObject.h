


#ifndef __VGMFILEDEFINITIONMOD_H__
#define __VGMFILEDEFINITIONMOD_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgMesh/vgmFileDefinitionMod.h>
#include <vgKernel/vgkBox.h>
#include <vgKernel/vgkSharePtr.h>

namespace vgMesh {

	using namespace vgKernel;

	/**
		∂‘”¶ObjectNode
	*/
	class ModObject
	{
	public:
		ModObject()
		{
			setDefault();
		}
		~ModObject()
		{
			destroy();
		}
	
	public:


		bool readFromMemory( char* buf, const int& buf_size,
			const uint& fileversion, const bool& isbaked );

		void destroy();


		// only for testing
		void render();

	private:

		void setDefault();
		
	private:
	public:

		bool _isValid;

		bool _isBaked;

		Box _box;
		long	_numberOfFaces;

		int		_renderType;
		char	_name[20];

		// Data
		int		_numberOfMaterial;
		long _sizeOfMaterialStruct;
		void* _material;
		MaterialFaces* _materialFaces;

		int		_numberOfNoMaterial;
		FaceIndex*	_faceIndexOfNoMaterial;

		int		_numberOfVertices;
		void* _vertexElements;

		// DataPlus
		int		_shadowNumberOfFaces;
		Vec3*	_shadowNormalOfFaces;
		int		_shadowNumberOfVertices;
		Vec3*	_shadowVerticesOfFaces;
		ShadowFaceIndex*	_shadowIndicesOfFaces;
	};


	typedef vgKernel::SharePtr< ModObject > ModObjectPtr;
	typedef std::vector<ModObjectPtr>	ModObjPtrVector;
	
	
	
}// end of namespace vgMesh

#endif // end of __VGMFILEDEFINITIONMOD_H__