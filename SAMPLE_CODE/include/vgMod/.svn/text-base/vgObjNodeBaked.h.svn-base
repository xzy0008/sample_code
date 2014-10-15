
/*< //------------------------------------------------------------------------------

	filename: vgObjNodeBaked.h

	usage	: define a kind of node (class ObjectNodeBaked) for baked-object

	designer: lss

	date	: 2008-3-12 11:44:25

	!!! Prerequisite: a)  Add a definition to the file "vgGlobalDefinition.h" ;
						#define VG_OBJECT_BAKED 7

					  b)  Add a function to the class SceneManeger from the file "vgSceneManager.h";
					  void AddObjectFromVgFile(ObjectNodeBaked *Object)
					  {
						m_oCurrentScene.vgLayerList[0]->m_ObjectArray.SetAtGrow(obj->m_id,obj);
					  }

					  c)  Do not forget ot include the file "vgObjNodeBaked.h" where mentioned

>*/ //------------------------------------------------------------------------------

#ifndef __VGOBJNODEBAKED_H__
#define __VGOBJNODEBAKED_H__

#include <vgMod/vgModelStruct.h>
#include <vgMod/vgObjNode.h>
#include <vgMath/vgfBoundingBox.h>
#include <vgMod/vgObjFrameNode.h>

namespace vgMod{

	//using namespace vgCore;

	class  VGDEP_EXPORT ObjectNodeBaked : public ObjFrameNode  
	{
	public:
		//	Part 0 :新增属性，相对class vgObjFrameNode(无)
		//	Part 1 :新增数据块，相对class vgObjFrameNode

		//	点数据	
		VertexElementStruct2*	pVertexElementStruct2;	// Vertex array		

		//	材质面数据
		MaterialStruct2*		pMaterialStruct2;				// Faces with material			

	public:
		//	Part 2 :新增状态变量
		int				m_nOffsetForTexCoorForLit;

		//	Part 3 :访问属性（无）
		//	Part 4 :重载基类的纯虚函数			

	public:
		//	Part 5 :重载父类的虚函数
		virtual void	configureCommonData();

		//	DisplayList
		virtual void	renderToDisplaylistOnce();

		//	VBO
		virtual void	sendVetexToVBOOnce();
		virtual void	clearUnvboDataExtra();

		virtual void	mapVertexBuffer();
		virtual void	unmapVertexBuffer();
		
		virtual void	assignTexture(int i );
		virtual void	resetTexture();
		virtual void	assignColor(int i);

		//	mod
		virtual	long	readMaterial(char	*pBytes);
		virtual	long	readVetex(char	*pBytes);

		//	edit
		virtual	void	translateVetexArray( Vector3 offset );
		virtual	void	rotateVetexArray( short axis, float angle ,Vector3 centerVec  );
		virtual	void	scaleVetexArray( Vector3 scale  , Vector3 centerVec);
	
		//	vg
		virtual	void	writeMaterialToVG(CFile &fp);
		virtual	void	writeVertexToVG(CFile &fp);
		virtual	void	readMaterialFromVG(CFile &fp);
		virtual	void	readVertexFromVG(CFile &fp);

		//	testIntersection
		virtual	Vector3	getVertexElementPosition(int i);

	public:
		virtual bool doLevellingVertexArray( const vgKernel::Polygon2D& polygons , float level_height );

		virtual void flip( bool x, bool y, bool z );
		
		virtual bool cloneMtlFromObjectNode(ObjectNode* src_node);
		virtual bool cloneVertexFromObjectNode(ObjectNode* src_node);

	protected:
		//	Part 6 :新增虚函数（无）
		//	Part 7 :新增其它函数（无）

	
	public:
		//	构造/析构
		ObjectNodeBaked( int nVersionMod = VERSION_1);
		virtual ~ObjectNodeBaked();
		

	};//class ObjectNodeBaked : public Node  

}//namespace vgCore

#endif // end of __VGOBJNODE_H__
