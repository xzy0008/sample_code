


#include <vgStableHeaders.h>
#include <vgImage/vgiTextureIoRequestDispatcher.h>
#include <vgAsyn/vgaIoRequest.h>
#include <vgImage/vgiIoRequestTextureLod.h>
#include <vgImage/vgiTexture.h>

#include <vgImage/vgiRenderCommand.h>
namespace vgImage {

	TextureIoRequestDispatcher::TextureIoRequestDispatcher() 
		: Singleton<TextureIoRequestDispatcher>( 
		VGK_SINGLETON_LEFE_TEXIODISPATCHER ) 
	{
		_asynMode = true;
		VGK_TRACE(_T("TextureIoRequestDispatcher created."));

		pTexIoCommand = new TextureIoCommand;

		vgKernel::RenderCommandFacade::AddCommand(pTexIoCommand);

	}

	TextureIoRequestDispatcher::~TextureIoRequestDispatcher()
	{
		vgKernel::RenderCommandFacade::RemoveCommand(pTexIoCommand);

		VGK_TRACE(_T("TextureIoRequestDispatcher destroyed."));
	}
	//----------------------------------------------------------------
	void TextureIoRequestDispatcher::dealWithUpdateInfoEveryFrame()
	{

		if ( _asynMode == true )
		{
			// 异步模式下的处理
			const int max_deal_num = 10;

			int i = 0;
			while ( i != max_deal_num )
			{
				if ( _texPipe.empty() == true )
				{
					break;
				}

				TexturePipe::iterator iter = _texPipe.begin();
				Texture* curtex = *iter;
				_texPipe.erase( iter );

				// 处理这个Texture
				dealWithTexture(curtex);

				++i;
			}
		}
		else
		{
			//------------------------------------------
			// 同步模式下的处理
			//------------------------------------------
			dealWithAllTextures();
		}

		return;
	}
	
	bool TextureIoRequestDispatcher::initialise()
	{


		return true;
	}

	bool TextureIoRequestDispatcher::shutdown() 
	{
		return true;
	}

	//----------------------------------------------------------------
	bool TextureIoRequestDispatcher::addTextureUpdate( Texture* texture )
	{
		TexPipeInsertResult res = _texPipe.insert( texture );

		return res.second;
	}
	//----------------------------------------------------------------
	bool TextureIoRequestDispatcher::loadTextureAndSendIoRequest( 
		Texture* texture , const bool& asyn_mode )
	{
		vgAsyn::IoRequest* rq = texture->getIoRequest();

		if ( rq == NULL )
		{
			return false;
		}

		if ( texture->getLodNumber() == VGLOD_CLEAR )
		{
			// 设置高优先级.
			rq->setPriority( true );
		}

		// 启用同步或者模式.注意,
		// 同步的时候IOCP还是多线程
		rq->setAsynchronousMode( asyn_mode );

		rq->sendRequestAndDoAsynHandlerFunc();

		return true;
	}
	//----------------------------------------------------------------
	void TextureIoRequestDispatcher::unloadTexture( Texture* texture )
	{
		texture->unloadTextureData();
	}
	//----------------------------------------------------------------
	void TextureIoRequestDispatcher::dealWithTexture( Texture* curtex )
	{
		const int& ref = curtex->getReferenceCounter();
		const bool& isempty = curtex->isEmptyTextrue();

		if ( ref > 0 && isempty == true )
		{
			// now load
			loadTextureAndSendIoRequest( curtex , _asynMode );
		}
		else if ( ref == 0 && isempty == false )
		{
			unloadTexture( curtex );
		}

		return;
	}
	//----------------------------------------------------------------
	void TextureIoRequestDispatcher::dealWithAllTextures()
	{
		TexturePipe::iterator iter = _texPipe.begin();
		TexturePipe::iterator iter_end = _texPipe.end();

		for ( ; iter != iter_end ; ++iter )
		{
			dealWithTexture( *iter );
		}

		_texPipe.clear();
	}
	//----------------------------------------------------------------
	void TextureIoRequestDispatcher::setAsynMode( const bool& set_asyn_mode )
	{
		if ( _asynMode == set_asyn_mode )
		{
			return;
		}

		//------------------------------------------
		// 不论从异步调整到同步或者反之,都需要先
		// 把原来的那些Request清空,然后设置_asynMode
		//------------------------------------------
		dealWithAllTextures();

		_asynMode = set_asyn_mode;
	}
	//----------------------------------------------------------------
	
	
	
}// end of namespace vgImage
