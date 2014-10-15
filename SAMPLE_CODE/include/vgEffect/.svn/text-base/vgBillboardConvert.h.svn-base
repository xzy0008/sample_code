/*#pragma once*/
#ifndef __VGConvertBillboard_H__
#define __VGConvertBillboard_H__

#include <vgMod/vgModelStruct.h>
#include <vgTex/tvgBillGpuProgram.h>
#include "vgBillBoard.h"

namespace vgMod
{

	struct vFaceIndex 
	{
		int x;
		int y;
		int z;
		int v;

		inline void operator = (const vFaceIndex & aa)
		{

			this->x = aa.x;

			this->y = aa.y;

			this->z = aa.z;

			this->v = aa.v;
		}
	};

	class  BillSetData
	{
	public:

		TexturePtr pTexture;

		int texid;

		string m_texname;

		int m_numOfbill;

		vgCore::VertexElementStruct *pVertex;

		vector<VertexElementStruct>  tempvertexbuffer;

		vFaceIndex *pFaceNoMat;

		vector<vFaceIndex> tempface;

		GLuint _vertexBufferObjectID;

		bool _isReadyForVBORender;

		GLuint _elementBufferObjectID;

		BillSetData()
		{
			pVertex = NULL;
			pFaceNoMat = NULL;
			m_numOfbill = 0;

			_vertexBufferObjectID = -1;
			_elementBufferObjectID = -1;
			//_vboReadBufPos = NULL;

			/*	_elementBufferNoMat  = -1;*/
			_isReadyForVBORender = false;
		}

		//BillSetData( const BillSetData &p)
  //		{
  //			pTexture = p.pTexture;
  //			texid = p.texid;
  //			m_texname = p.m_texname;
  //			pVertex = p.pVertex;
  //			pFaceNoMat = p.pFaceNoMat;
  //			m_numOfbill = p.m_numOfbill;
  //			_vertexBufferObjectID = p._vertexBufferObjectID;
  //			_elementBufferObjectID = p._elementBufferObjectID;
  //			_isReadyForVBORender = p._isReadyForVBORender;
  //		}

		inline void operator = (const BillSetData &p)
		{
			pTexture = p.pTexture;
			texid = p.texid;
			m_texname = p.m_texname;
			pVertex = p.pVertex;
			pFaceNoMat = p.pFaceNoMat;
			m_numOfbill = p.m_numOfbill;
			_vertexBufferObjectID = p._vertexBufferObjectID;
			_elementBufferObjectID = p._elementBufferObjectID;
			_isReadyForVBORender = p._isReadyForVBORender;
		}
		~BillSetData()
		{
			delete pVertex;

			pVertex = NULL;

			delete pFaceNoMat;

			pFaceNoMat = NULL;
		}
	};
	class vgConvertBillboard
	{
	public:
		vgConvertBillboard(void);
		~vgConvertBillboard(void);

	public:

		vector<BillSetData*> BillSet;
		
		BillSetData	temp;

		void AddBillboard(BillboardNode &node);

		void AddBillboardToBillSet(BillboardNode &node, BillSetData *billset);

		void convert();
//////////////////////////////////////////////////////////////////////////
		///////////////////////////VBO///////////////////////////////////////////////

		bool b_render;

		void Render();

		void SetRender(bool brender);

		void WriteToFile(CFile &fp);

		void PreWriteProc(BillSetData *billset);
		
		void ReadFromFile(CFile &fp);

		void AfterWritefile(BillSetData *billset);
		
		//cg
		BillGpuProgram *mpWaterProgram;
	};

}

#endif