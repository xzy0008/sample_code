


#ifndef __VGMMESH_H__
#define __VGMMESH_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgAsyn/vgaFileHandle.h>
#include <vgMesh/vgmMeshData.h>
#include <vgMesh/vgmMeshDataPlus.h>

namespace vgMesh {

	class VgmBrief;
	class MeshItem;
	class MeshData;
	class MeshDataPlus;

	/**
	@date 	2008/07/30  9:13	
	@author  leven

	@brief 	

	@see    
	*/
	class  VGM_EXPORT Mesh
	{
		friend class MeshItem;
	public:
		Mesh( MeshItem* item , VgmBrief* vgmbrief , 
			vgAsyn::FileHandle* filehandle , int lod );

		~Mesh()
		{
			destroy();
		}

	public:

		void destroy();

		// 自增的同时,检查是否需要载入
		void addRef( bool force_to_load );

		void releaseRef();

		void render( int tex_lod , bool trans_mode ,
			RgbaQuad* colorval );

		// 注意，这里强硬渲染，如果没有数据，将会创建阴影数据
		void forceRenderInShadowMode()
		{
			//------------------------------------------
			// 先这么测试看!!!
			//------------------------------------------
			if ( _meshData == NULL || _lod != VGLOD_CLEAR )
			{
				return;
			}

			forceToGenerateMeshDataPlus();

			assert( _meshDataPlus != NULL );

			_meshDataPlus->renderOnceInShadowMode();

			return;
		}

		void forceToGenerateMeshDataPlus()
		{
			assert( _meshData != NULL );

			if ( _meshDataPlus == NULL )
			{
				_meshDataPlus = new MeshDataPlus();
				bool importok = _meshDataPlus->importFromMeshData( _meshData );
				assert( importok == true );
			}

			assert( _meshDataPlus != NULL );
			return;
		}

		void changeLightDirectionImpl()
		{
			if ( _meshData == NULL || _lod != VGLOD_CLEAR )
			{
				return;
			}

			forceToGenerateMeshDataPlus();
			assert( _meshDataPlus != NULL );

			_meshDataPlus->invalidateShadowRendering();
		}


		void setMeshData( MeshData* data )
		{
			assert( _meshData == NULL );
			_meshData = data;
		}

		void setMeshDataAndPlus( MeshData* data , 
			MeshDataPlus* plusdata )
		{
			assert( _meshData == NULL );
			assert( _meshDataPlus == NULL );

			_meshData = data;
			_meshDataPlus = plusdata;
		}

		const int getReferenceCount() const
		{
			return _referenceCount;
		}

		MeshData* getMeshData() const
		{
			return _meshData;
		}

		inline int getLod() const
		{
			return _lod;
		}

		inline bool hasMeshData() const
		{
			 return _meshData != NULL ;
		}

		inline bool hasMeshPlusData() const 
		{
			return _meshDataPlus != NULL;
		}

		inline void turnOnShadowImpl()
		{
			_shadowEnabled = true;
		}

		inline void turnOffShadowImpl()
		{
			_shadowEnabled = false;
		}

		MeshItem* getFatherMeshItem() 
		{
			return _fatherItem;
		}

		vgAsyn::FileInfo* getMeshDataFileInfoRef()
		{
			return _meshDataFileInfo;
		}

	private:

		void setDefault();

	private:

		bool _shadowEnabled;

		MeshItem* _fatherItem;

		int	 _referenceCount;
		int		_lod;

		MeshData* _meshData;
		vgAsyn::FileInfo* _meshDataFileInfo;

		MeshDataPlus* _meshDataPlus;
		vgAsyn::FileInfo* _meshDataPlusFileInfo;

	};


}// end of namespace vgMesh

	


#endif // end of __VGMMESH_H__