

#ifndef __VGMVGFILEREADERMOD_H__
#define __VGMVGFILEREADERMOD_H__

#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkRendererManager.h>

#include <vgMod/vgFileDefinitionVG.h>
#include <vgMod/vgNode.h>
#include <vgMod/vgObjNode.h>

#include <vgPhys/vgphPhysManager.h>

namespace vgMod{

	using namespace vgCore;
	
	/**
	@date 	2009/03/03  14:12	
	@author  lss

	@brief 	

	@see    
	*/
	class	 VGDEP_EXPORT FileReaderMOD
	{

	public:
		FileReaderMOD();
		~FileReaderMOD();

		bool	read( const String& open_absolute_path, 
			NodeAbsPtrVec* pNodeIndexList,
			NodePtrVec* pNodeList,
			ModItemPtrVec* pModListTemp);
		
		
		struct TraverseVecForAddRender
		{
			inline void operator() ( Node* item) 
			{
				vgKernel::Renderer* renderer = dynamic_cast<vgKernel::Renderer*>(item);

				if( renderer!=NULL )
				{
					vgKernel::RendererManager::getSingleton().addRenderer(renderer);
				}

				vgPhys::CollisionObject *pObject = dynamic_cast<vgPhys::CollisionObject*> (item);
				if (pObject != NULL)
				{
					vgPhys::PhysMananger::getSingleton().addCollisionObject(pObject);
				}
			}
		};

	protected:
		bool	readObjectNodeFromMOD();

		bool	generateNodeIndex();
		bool	addModNodeToManager( );
		//bool	addModNodeToUI( );

		// 读取Mod 时,通过名称"tree-"判断,转换Mod树为BillBoard 树
		bool	convertModTree2Billbaoard( ObjectNode*	pObjectNode );	// Add By FengYK @2010-03-15 20:21
		
	protected:
		vgKernel::StreamReaderPtr m_pfile;
		String	m_strFilePath;
		
		MODFileHeader	m_fileHeader;
		NodeAbsPtrVec*	m_pNodeIndexList;
		NodePtrVec*		m_pNodeList;

		NodeAbsPtrVec*  m_pTempNodeIndexList;
		NodePtrVec*		m_pTempNodeList;
		ModItemPtrVec*	m_pModListTemp;
	};
}//namespace vgMod

#endif//__VGMVGFILEREADERMOD_H__
