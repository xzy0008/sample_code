
#ifndef _COMMANDFACTORY_H_INCLUDED_
#define _COMMANDFACTORY_H_INCLUDED_

#include <vgTrigger/vgtrCommandAbstract.h>
#include <vgTrigger/vgtrDefinition.h>


namespace vgTrigger
{
	class VGTRI_EXPORT CommandFactory
	{
	public:
		CommandFactory();
		~CommandFactory(); 

	public:
		static CommandPtr generateCommand(CommandID id,
			string name = "", void* param=NULL);
	};//class

}//namespace

#endif//_COMMANDFACTORY_H_INCLUDED_