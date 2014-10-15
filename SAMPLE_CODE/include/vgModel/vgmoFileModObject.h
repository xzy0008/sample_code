


#ifndef __VGMO_FILEDEFINITIONMOD_H__
#define __VGMO_FILEDEFINITIONMOD_H__


#include <vgModel/vgmoDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgModel/vgmoFileDefinitionMod.h>
#include <vgKernel/vgkBox.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgModel/vgmoFileModKeyframeInfo.h>



namespace vgModel {

	using namespace vgKernel;

	/**
		对应ObjectNode
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
			uint fileversion, bool isbaked,
			bool is_keyframe );

		void destroy();


		// only for testing
		void render();

	private:

		void setDefault();
		
	public:

		bool _isValid;

		bool _isBaked;

		Box _mergedBox; // 连同keyframe一起，merge的box

		Box _unmergedBox; // 最初的box

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


		// keyframe
		ModKeyFrameInfo* _keyframeInfo;
	};


	typedef vgKernel::SharePtr< ModObject > ModObjectPtr;
	typedef std::vector<ModObjectPtr>	ModObjPtrVector;
	
	
	
}// end of namespace vgModel

#endif // end of __VGMO_FILEDEFINITIONMOD_H__