

#ifndef __VGVERSIONCONTROL_H__
#define __VGVERSIONCONTROL_H__


namespace vgMod{

	//using namespace vgXXX;


	class	VGDEP_EXPORT	VersionControl
	{
	public:
		VersionControl()
		{
		}
		~VersionControl();

		// vg版本字符串
		static String	getVgVersionWrite()
		{
			//============现有插件版平台项目的vg版本记录================

			/*  版本号 | 对应项目
			/*  V2.19  | 上海新体育城(普陀项目)   

			//===========================================================

			/************************************************************************/
			/* vg版本更新记录                                                        
			/*																		
			/*	版本号	|	更新时间				|	更新者	|	更新内容及原因	
			/*	2.21	|	2010年03月27日16:57:20	|	yu		|	dll版增加信息标注节点和自定义体块节点
			/*	2.20	|	2010年03月27日16:57:20	|	yu		|	dll版增加时间轴起始点和终止点
			/*	2.19	|	2010年03月27日16:57:20	|	Fyk		|	dll版增加水流的U、V两个量控制水流的方向
			/*	2.18	|	2009年12月01日10:47:20	|	lss		|	升级到dll版本
			/*	2.17	|	2009年3月16日10:47:20	|	sc		|	增加块AutoNode的读写
			/*	2.16	|	2009年2月23日10:47:20	|	lss		|	ObjectNode 读写 m_PreRenderType(半透明功能需要)
			/*	2.15	|	2009年2月5日15:58:10	|	lss		|	关键帧物体的类型信息（是否烘焙）
			/*	2.14	|	2008年11月24日21:21:13	|	lss		|	保存层的可见性标记
			/*	2.13	|	2008年11月20日22:18:35	|	lss		|	ObjectNode 读写 UniqueID
			/*	2.12	|	2008年11月18日22:30:35	|	zhu		|	vg的地形保存和vcr偏移的保存
			/*  2.11    |   2008年11月6日10:10:35   |   lss	    |   保存场景必要时切割vgi  	
			/*	2.1		|	2008年10月17日20:58:54	|	lss		|	vgm写文件 vgObjFrameNode写vg增加内容	          
			/*	2.0		|	2008年10月9日10:11:06	|	lss		|	vgm写文件 由合并改为不合并	          
			/*	1.8		|	2008年6月26日14:01:41	|	lss		|	vrgis2.0  vg文件的基础版本	          
			/*                                                         
			/************************************************************************/
			m_strVgVersionWrite = "VRGIS.VERSION ";// 注意字符串末尾有一个空格字符
			m_strVgVersionWrite += "2.21";//yu
			//m_strVgVersionWrite += "2.20";//yu
			//m_strVgVersionWrite += "2.19";//Fyk
			//m_strVgVersionWrite += "2.18";//lss
			//m_strVgVersionWrite += "2.17";//sc
			//m_strVgVersionWrite += "2.16";//lss
			//m_strVgVersionWrite += "2.15";//lss
			//m_strVgVersionWrite += "2.14";//lss
			//m_strVgVersionWrite += "2.13";//lss
			//m_strVgVersionWrite += "2.12";//zhu
			//m_strVgVersionWrite += "2.11";
			//m_strVgVersionWrite += "2.1";
			//m_strVgVersionWrite += "2.0";
			//m_strVgVersionWrite += "1.8";

			return m_strVgVersionWrite;
		}

	public:
		static String	getVgVersionRead()	{	return m_strVgVersionRead;}

		static void	setVgVersionRead(String strVgVersionRead)	
		{	
			m_strVgVersionRead = strVgVersionRead;
		}
		static bool	isVersionCompatible()	
		{	
			if (m_strVgVersionWrite.empty())
			{
				getVgVersionWrite();
			}
			return m_strVgVersionWrite >= m_strVgVersionRead;
		}  
	private:
		static String	m_strVgVersionRead;
		static String	m_strVgVersionWrite;

	};
}//namespace vgMod

#endif//__VGVERSIONCONTROL_H__