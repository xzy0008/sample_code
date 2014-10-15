#pragma once

#include <vgKernel/vgkRenderCommand.h>
#include <vgChannel/vgcChannelManager.h>

class ChannelRenderBegin : public vgKernel::RenderCommand
{
public:
	ChannelRenderBegin() : vgKernel::RenderCommand(VG_RP_CHANNEL_RENDER_BEGIN){}

	inline virtual bool render()
	{
		vgChannel::ChannelManager::getSingleton().renderBegin();
		return true;
	}
};

class ClientRenderBegin : public vgKernel::RenderCommand
{
public:
	ClientRenderBegin() : vgKernel::RenderCommand(VG_RP_CHANNEL_CLIENT){}

	inline virtual bool render()
	{
		vgChannel::ChannelManager::getSingleton().clientRenderBegin();
		return true;
	}
};

class ServerRenderBegin : public vgKernel::RenderCommand
{
public:
	ServerRenderBegin() : vgKernel::RenderCommand(VG_RP_CHANNEL_SERVER){}

	inline virtual bool render()
	{
		vgChannel::ChannelManager::getSingleton().serverRenderBegin();
		return true;
	}
};

class ChannelRenderEnd : public vgKernel::RenderCommand
{
public:
	ChannelRenderEnd() : vgKernel::RenderCommand(VG_RP_CHANNEL_RENDER_END){}

	inline virtual bool render()
	{
		vgChannel::ChannelManager::getSingleton().renderEnd();
		return true;
	}
};

class BlendAndAdjust : public vgKernel::RenderCommand
{
public:
	BlendAndAdjust() : vgKernel::RenderCommand(VG_RP_BLEND_ADJUST){}

	inline virtual bool render()
	{
		vgChannel::ChannelManager::getSingleton().blendAndAdjust();
		return true;
	}
};