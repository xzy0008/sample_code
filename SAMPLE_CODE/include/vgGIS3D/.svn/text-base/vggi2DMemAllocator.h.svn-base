// 2DMemAllocator.h: interface for the C2DMemAllocator class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

namespace vgGIS3D
{
	class C2DMemAllocator  
	{
	public:
		C2DMemAllocator();
		~C2DMemAllocator();


		/*~~~~~~~~~分配函数~~~~~~~~~~~~~~~~~*/
		//三个参数：
		//   p: [out],该函数分配成功的指针设置给p
		//rows: [in], 行数
		//cols: [in], 列数
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		static BOOL AllocMemory2D(float ** &p,int rows,int cols);


		/*~~~~~~~~~释放函数~~~~~~~~~~~~~~~~~*/
		//释放由AllocMemory2D()分配成功的内存空间
		//一个参数：
		//   pp: [in],由AllocMemory2D()分配的内存指针
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		static void FreeMemory2D(float **&pp);

	};

}