


#ifndef __VGMO_MESHITEM_H__
#define __VGMO_MESHITEM_H__



#include <vgModel/vgmoDefinition.h>
#include <vgKernel/vgkForward.h> 
#include <vgKernel/vgkBox.h>
#include <vgKernel/vgkUniqueID.h>
#include <vgModel/vgmoModelData.h>

#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkMat4.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgKernel/vgkShadowCastObject.h>
#include <vgKernel/vgkTransparentObject.h>
#include <vgKernel/vgkColorableObject.h>


namespace vgModel {

	using namespace vgKernel;

	class ModelData;
	class VmdBrief;
	class FileHandleVmd;


	/*
	5010 -- 5030之间为QuadTreeSceneMananger的管辖范围之内
	*/
	const vgKernel::RendererType RENDERER_TYPE_MODEL = 15000;


	/**
		@date 	2008/07/01  20:58	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGMO_EXPORT ModelItem 
		: public vgKernel::Renderer,
		public vgKernel::ShadowCastObject,
		public vgKernel::TransparentObject,
		public vgKernel::ColorableObject
	{
		VGK_RENDERER_IN_DECLARE( ModelItem )
	public:
		ModelItem();
		~ModelItem();
	
	public:



		// 光影的方向在第一次的时候进行设置
		// 包括光的方向变更的时候，也使用此函数进行通知。
		virtual void onLightDirectionChanged( const vgKernel::Vec3& light_dir );

		// 渲染shadow的caster
		virtual void renderInShadowMode();

		virtual void turnOffShadowCast();

		virtual void turnOnShadowCast( const vgKernel::Vec3& light_dir,
			bool force_to_load );



		// 数据load和dump操作
		virtual bool load( VmdBrief* vgmbrief , FileHandleVmd* filehandle ,
			int version );
		virtual bool dumpInfoToVmdBrief( VmdBrief* vgmbrief );
		virtual bool dumpFileInfoToBuffer( char*& whole_file , long& file_length );


		void destroy();

		String getDetails();

		/**
			继承Renderer而来的接口
		*/
		virtual void setVisible( const bool& visible )
		{
			_isVisible = visible; 
		}

		virtual void render();

		virtual bool getVisible()
		{
			return _isVisible;
		}
		virtual UniqueID getUniqueID()
		{
			return _uniqueID;
		}
		virtual String getName()
		{
			return _modelName;
		}
		virtual String* getNamePtr()
		{
			return &_modelName;
		}
		virtual void setName( const String& newname )
		{
			_modelName = newname;
		}
		void translate(const float& x, const float& y, const float& z);
		void rotateSelf(const float& angle, const float& x, const float& y, const float& z);
		void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z);
		void rotate(const float& angle, const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z); 

		virtual vgKernel::Box getBoundingBox()
		{
			return _dynamicBox;
		}
		virtual std::pair<bool, float> testIntersectWithTriangles(
			const vgKernel::Ray& ray );
		virtual bool testIntersectWithTriangles( 
			const vgKernel::Segment3& segment );
		virtual long getNumOfTriangles()
		{
			return _numberOfTriangles;
		}
		virtual float setDistanceToViewer( const Vec3& viewer_pos  );
		virtual Vec3 getPosition()
		{
			return _dynamicBox.getCenter();
		}

		// 继承TransparentObject的接口
		virtual bool isTransparent();

		// 继承TransparentObject的接口
		virtual void setTransparent( bool set_to_transp = true );

		vgAsyn::FileInfo* getDataFileInfoRef()
		{
			return _meshDataFileInfo;
		}

		void invalidateTextures();

	private:

		void setDefault();

	private:

		float _squareDistNear;
		float _squareDistFar;

		float _squaredDistanceToViewer;

		// 通过_distanceToViewer计算出来lod
		int		_distanceLod;


		// 当前的Lod,注意,当_currentLod与_distanceLod
		// 相当于_preLod
		// 相比发生变化时,才发生addRef和releaseRef操作 
		// 默认的为最不清晰一级,即_currentLod = 0;
		int		_currentLod;

		UniqueID _uniqueID;
	
		// 注意,最多64个字节长度.
		String _modelName;
		bool _isVisible;
		vgKernel::Box _dynamicBox;
		vgKernel::Box _staticBox;

		vgKernel::Mat4 _matrix;

		long	_numberOfTriangles;

		vgAsyn::FileInfo* _wholeFileInfo;

		bool _isTransparent;

		//----------------------------------------------------------------
		ModelData* _meshData;
		vgAsyn::FileInfo* _meshDataFileInfo;
	};
	

	typedef std::vector<ModelItem*> ModelItemPtrVec;

	typedef std::map<UniqueID, ModelItem*> ModelItemMap;
	typedef std::pair<ModelItemMap::iterator, bool> ModelItemInsertRes;

	VGK_RENDERER_OUT_DECLARE( ModelItem )
	
}// end of namespace vgModel

#endif // end of __VGMO_MESHITEM_H__