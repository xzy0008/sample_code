

#ifndef __TVGSTREAMREADERFACTORY_H__
#define __TVGSTREAMREADERFACTORY_H__

#include <vgCore/vgPrerequisites.h>
#include <vgTex/tvgStreamReader.h>
#include <vgTex/tvgFileStreamReader.h>
#include <vgTex/tvgStreamWriter.h>

namespace vgCore {


	class StreamFactory
	{
	public:

		static StreamWriterPtr createWriterFromFile( const String& filename )
		{
			StreamWriterPtr ppstream( new FileStreamWriter( filename ) );

			return ppstream;
		}

		static StreamReaderPtr createReaderFromFile( const String& filename )
		{

			//StreamReaderPtr p( new FileStreamReader );

			FileStreamReader *p = new FileStreamReader();

			assert( p != NULL );

			if( p->create( filename ) == true )
			{
				assert( p->isValid() == true );
				return StreamReaderPtr(p);
			}

			VG_WARN(Warning::WARN_FILE_NOT_FOUND ,
				Warning::BUTTON_NONE ,
				filename + " is not found , create StreamReaderPtr failed.",
				"StreamFactory::createReaderFromFile");
			
			//p.setNull();
			delete p;

			// return null smart pointer
			return StreamReaderPtr();
		}

		static FileStreamReaderPtr createFileStreamReader( const String& filename )
		{

			FileStreamReaderPtr p( new FileStreamReader );

			if( p->create( filename ) == true )
			{
				assert( p->isValid() == true );
				return p;
			}

			VG_WARN(Warning::WARN_FILE_NOT_FOUND ,
				Warning::BUTTON_NONE ,
				filename + " is not found , create StreamReaderPtr failed.",
				"StreamFactory::createReaderFromFile");

			p.setNull();
			return p;
		}
	
	};
	
	
}// end of namespace vgCore

#endif // end of __TVGSTREAMREADERFACTORY_H__