
#ifndef  __VGKVGKCURRENTPROGRAM_H__
#define __VGKVGKCURRENTPROGRAM_H__

#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkSingletonLifeTimeDefine.h>

namespace vgKernel{
	/*
	Author: foryond
	Time: 2010/05/06 14:01 
	*/




	class VGK_EXPORT vgkCurrentProgram:
		public vgKernel::Singleton<vgkCurrentProgram>
	{
	private:
		friend class vgKernel::Singleton<vgkCurrentProgram>;
	private:
		vgkCurrentProgram()
			:vgKernel::Singleton<vgkCurrentProgram>(VGK_SIGLETON_LEFE_PROGRAMNAME)
		{

		}
	public:
		virtual ~vgkCurrentProgram()
		{

		}

		void SetCurrentProgramName(String CurrentProgramName)
		{
			m_CurrentProgramName = CurrentProgramName;
		}
		
		String GetCurrentProgramName()
		{
			return m_CurrentProgramName;
		}

		void ClearProgramName()
		{
			m_CurrentProgramName = "";
		}
	protected:

		virtual bool initialise()
		{
			return true;
		}
		virtual bool shutdown()
		{
			return true;
		}
	private:
		String m_CurrentProgramName;
	
	};



}

#endif //endif__VGKVGKCURRENTPROGRAM_H__
