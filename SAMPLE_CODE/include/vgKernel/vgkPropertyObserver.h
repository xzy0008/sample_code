#pragma once

#include <vgKernel/vgkObserver.h>

namespace vgKernel
{
	const unsigned int PROPERTY_ON_CHANGE = 1;

	class PropertyObserver : public Observer
	{
	public:
		virtual void onEvent(unsigned int eventId, void *param) {}
	};
}