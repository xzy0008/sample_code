


#ifndef __VGEDITUTILITY_H__
#define __VGEDITUTILITY_H__

#include <vgGlobal/vgglDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkRendererManager.h>

using namespace vgKernel;

namespace vgGlobal{

	/**
		@date    2009/10/21  14:08
		@author  zzy

		@brief   

		@see
	*/	

	class	VGGL_EXPORT EditUtility
	{
	public:
		EditUtility()	{}
		~EditUtility()	{}


		static bool     translate();                 //平移
		static bool     rotate();                    //旋转
		static bool     scale();                     //缩放
		static bool     updateTranslate();
		static bool     updateRotate();
		static bool     updateScale();

		static bool     undo();                      //撤消
		static bool     redo();                      //重做

		static bool     selectionAll();              //全部选择
		static bool     clearSelection();            //取消选择
		static bool     selectionReverse();          //反向选择
		static bool     FindObject();                //查找物体
		static bool     selectShapeRect();           //矩形框选择
		static bool     selectShapePolygon();        //多边形选择
		static bool     selectRegionNew();           //新建选区
		static bool     selectRegionAdd();           //添加到选区
		static bool     selectRegionSubtract();      //从选区减去
		static bool     selectRegionIntersect();     //与选区交叉
		static bool     selectModeInclude();         //全包围模式
		static bool     selectModeIntersect();       //半包围模式  

		static bool     translateAll();              //平移所有物体 
		static bool     translateSeleted();          //平移选中物体

		static bool     setSelTransparent();         //选中物体半透明
		static bool     setSelUnTransparent();       //选中物体取消半透明
		static bool     updateSetSelTransprant();
		static bool     updateSetSelUnTransprant();

		static bool     SingleFaceRenderSelected();  //选中物体单面渲染  
		static bool     SingleFaceRenderAll();       //所有物体双面渲染
		static bool     updateSingleFaceRenderSelect();
		static bool     updateSingleFaceRenderAll();

		//带参接口
		static bool     translateRenderers( RendererQueue* queue, const Vec3& trans_vec );

	private:
		static bool     setSelectNodesToTransparent( bool bSet );
		
		
	private:
		static bool m_bSetSelTransprent;      //标志选中节点半透明
		static bool m_bSetSelUnTransprent;    //标志选中节点不半透明

		static bool m_bSingleFaceRenderSel;   //标志选中节点是否单面渲染
		static bool m_bSingleFaceRenderAll;   //标志所有节点是否单面渲染

		static bool m_bTranslateMode;
		static bool m_bRotateMode;
		static bool m_bScaleMode;

		static bool m_bSelectModeInclude;
		static bool m_bSelectModeIntersect;

	};
}//namespace vgGlobal

#endif//__VGEDITUTILITY_H__
