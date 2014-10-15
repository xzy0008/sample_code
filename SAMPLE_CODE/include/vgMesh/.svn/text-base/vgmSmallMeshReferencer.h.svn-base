


#ifndef __VGMSMALLMESHREFERENCER_H__
#define __VGMSMALLMESHREFERENCER_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgMesh/vgmDefinition.h>

	
namespace vgMesh {

	class Mesh;
	/**
		@date 	2009/04/28  11:12	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	


#define  VGM_SMALLMESH_DEFAULT_THRESHOLD	VGM_CONF_SMALLMESHREF_LOADTHRESHOLD_DEFAULT

	/**
		@date 	2009/04/28  10:00	
		@author  leven

		@brief 	对于小型Mesh一次性载入即可。

		@see    
	*/
	class VGM_EXPORT SmallMeshReferencer
	{
		typedef std::vector<Mesh*> MeshPtrVector;
	public:
		SmallMeshReferencer();
		~SmallMeshReferencer();

	public:

		bool filterSmallMeshes( MeshItem* itm );

		// unref并且删除掉所持有的textureitm
		void unRefAllSmallMeshes();


		void deleteSmallMesh( MeshItem* itm );


		int getLoadFileSizeThreshold() const
		{
			return _loadFileSizeThreshold;
		}

		void setLoadFileSizeThreshold( int new_threshold )
		{
			assert( new_threshold > 0 );
			_loadFileSizeThreshold = new_threshold;
		}

		const bool getFilterEnable() const { return _filterEnable; }
		bool getFilterEnable() { return _filterEnable; }
		void setFilterEnable( const bool& val );

		void unRefBecauseOfImage();

		void addRefBecauseOfImage();

	private:

		bool checkExist( Mesh* itm );

	private:

		// 因为载入都是一次性的，所以依次遍历带来的效率损失也不大
		MeshPtrVector _smallMeshes;

		// 是否addref的文件大小，以字节计算
		// 可以写入vgConf
		int _loadFileSizeThreshold;

		bool _filterEnable;


	};
	
}// end of namespace vgMesh
	


#endif // end of __VGMSMALLMESHREFERENCER_H__