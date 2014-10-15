#pragma once

#include <vgGis/vggisDefinition.h>

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>

#include <vgGIS3D/vggiContour.h>
#include <vgKernel/vgkRenderCommand.h>

namespace vgGIS3D
{
	class VGG_EXPORT ContourManager : public vgKernel::Singleton<ContourManager>
	{
		friend class vgKernel::Singleton<ContourManager>;
	
	public :
		ContourManager();

		virtual ~ContourManager();

	public:

		bool addContour(Contour *newContour);

		bool removeContourByName(string name);

		bool removeContour(Contour *pContour);

		Contour *getContourByName(string name);

		Contour *getContour(int i);

		int getNumOfContour() { return m_contourArray.size(); }

		void render();

		void traceAllContour();

		void setRenderFlag(bool flag) { m_enableRender = flag; }

		bool getRenderFlag() { return m_enableRender; }

	protected:
		
		virtual bool initialise();

		virtual bool shutdown();

		vector<Contour*> m_contourArray;
		
		vgKernel::RenderCommand *m_pContourRenderCommand;

		bool	m_enableRender;
		
	};
}