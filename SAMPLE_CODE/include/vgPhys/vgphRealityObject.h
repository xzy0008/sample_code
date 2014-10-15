#pragma once


namespace vgPhys
{

const static int VGPH_REALITY_TYPE_UNKOWN = 0;
const static int VGPH_REALITY_TYPE_COLLISION = 1;

	class VGPH_EXPORT RealityObject
	{
	public:

		RealityObject(int type = VGPH_REALITY_TYPE_UNKOWN)
		{
			m_objectType = type;
		}

		virtual ~RealityObject(){}

	protected:
		int m_objectType;
	};
}