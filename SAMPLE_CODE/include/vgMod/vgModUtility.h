




#ifndef __VGDMODUTILITY_H__
#define __VGDMODUTILITY_H__

#include <vgKernel/vgkForward.h>
#include <vgMod/vgNode.h>
#include <vgMod/vgObjNode.h>
#include <vgTex/tvgTextureManager.h>
#include <vgTex/tvgArchiveDeclaration.h>

namespace vgMod {

	/**
		@date 		2009/05/19  19:42	
		@author  	lss
	
		@brief 	
	
		@see    
		*/

	class Node;
	class NodeAbstract;

	class  VGDEP_EXPORT ModUtility
	{
	private:
		ModUtility()
		{
		}
		~ModUtility()
		{
			
		}
	
	public:

		/*!
		... 读mod ...
		*/
		static bool	AddModelToScene( const string& strFilePath );//{return true;}
	
		/*!
		... 写vg ...
		*/		
		static bool	saveSceneToVG( const string& filepath ,
			unsigned int uiUpdateTime);

		static bool	saveSceneToVGDirectly( const string& filepath ,
			unsigned int uiUpdateTime);

		/*!
		... 读vg ...
		*/		
		static bool	readSceneFromVG( const string& strFilePath ,
			unsigned int uiUpdateTime);

		static bool readSceneFromVGDirectly( const string& strFilePath , 
			unsigned int uiUpdateTime);

		/*!
		... 由Node生成NodeAbstract ...
		*/		
		static void	generateNodeIndexFromNode( Node* pNodeIn, NodeAbstract** pNodeAbsOut );

		static bool generateNodeIndexFromRender( const vgKernel::RendererQueue& renderQuene, 
			NodeAbsPtrVec* pNodeAbsPtrVec );

		static bool generateSelectTexNameVec( const NodeAbsPtrVec* pNodeAbsPtrVec, 
			TextureNameMap* pTexNameMap );

		static bool	chenkVersionAndUpdate( const string& strFilePath );


		static const vector<vgCore::MetaFile>& getMetaFileInfo() { return m_metaFileInfoVec; }

	public:
		static void setFlagReadVg( bool bReadFlag ) { b_readVgOrMod = bReadFlag; }
		static bool getFlagReadVg()	{	return b_readVgOrMod;}
		static bool getFlagReadDirectly()	{	return b_readDirectly;}
		static void setFlagReadDirectly(bool bDirect)	{ b_readDirectly = bDirect;}
		
		static bool getSaveMode() { return m_bSaveSelectNode; }
		static void setSaveMode( bool bMode ) { m_bSaveSelectNode = bMode; }

		static void readVGIMG( const string& strFilePath );
		static void saveVGIMG( const string& strFilePath );

	private:
		static bool	b_readVgOrMod;

		static bool b_readDirectly;

		static bool  m_bSaveSelectNode;   // 用于场景切块保存，标识保存选定节点或是全部节点

		static vector<vgCore::MetaFile> m_metaFileInfoVec;

	};
	
	
}// end of namespace vgMod



#endif // end of __VGDMODUTILITY_H__