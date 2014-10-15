
#include <vgStableHeaders.h>

#include <vgTex/tvgBillboard.h>

namespace vgCore {

	Real Billboard::PIXCEL_TO_FLOAT_FACTOR = 0.01f;
	Real Billboard::DEFAULT_RECT_WIDTH = 2.0f;
	Real Billboard::DEFAULT_RECT_HEIGHT = 2.0f;

	vgMath::ColorValue Billboard::msEdgeColor = vgMath::ColorValue::Yellow;
	
	//----------------------------------------------------------------
	Billboard::Billboard()
	{
		this->setParametersDefault();
	}
	//----------------------------------------------------------------
	Billboard::~Billboard()
	{

	}
	//----------------------------------------------------------------
	void Billboard::drawUsingEyeOriented() const
	{
		const Vector3 &pos = mPosition ;
		const Real& H = mHeight * 0.5f * mScale;
		const Real& W = mWidth * 0.5f * mScale;
		const Vector3  dw = mCurrentViewRight * W;
		const Vector3  dh = mCurrentViewUp * H; 

		glTranslatef( 0 , H , 0 );

		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0,0.0);	
			glVertex3fv( (pos - dw - dh ).v );//左下点		

			glTexCoord2f(1.0,0.0);
			glVertex3fv( (pos + dw - dh ).v);//右下点

			glTexCoord2f(1.0,1.0);
			glVertex3fv( (pos + dw + dh ).v);//右上点

			glTexCoord2f(0.0,1.0);
			glVertex3fv( (pos - dw + dh ).v);//左上点
		}
		glEnd();

		/*
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_ALPHA_TEST);

		glAlphaFunc(GL_GREATER, 0);


		glPushMatrix();
		glColor3f(1,1,1);

		this->mTexturePtr->useBind();

		glBegin(GL_QUADS);
		{
			//glTexCoord2f(0.0,0.0);	
			//glVertex3fv( (pos - dw - dh ).v );//左下点		
			//
			//glTexCoord2f(1.0,0.0);
			//glVertex3fv( (pos + dw - dh ).v);//右下点
			//
			//glTexCoord2f(1.0,1.0);
			//glVertex3fv( (pos + dw + dh ).v);//右上点
			//
			//glTexCoord2f(0.0,1.0);
			//glVertex3fv( (pos - dw + dh ).v);//左上点

			//CVector3 dir()

			int size = 10;
			glTexCoord2f(0.0,0.0);	
			glVertex3f( mPosition.x  , mPosition.y , mPosition.z );//左下点		

			glTexCoord2f(1.0,0.0);
			glVertex3f( mPosition.x + size , mPosition.y , mPosition.z );//右下点

			glTexCoord2f(1.0,1.0);
			glVertex3f( mPosition.x  + size, mPosition.y + size, mPosition.z );//右上点

			glTexCoord2f(0.0,1.0);
			glVertex3f( mPosition.x  , mPosition.y + size , mPosition.z );//左上点

		}
		glEnd();
		glPopMatrix();

		glDisable(GL_ALPHA);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		*/

	}
	//----------------------------------------------------------------
	void Billboard::drawingBegin() const
	{
		glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE );
		glEnable(GL_TEXTURE_2D);

		//glDisable( GL_BLEND );
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.5f);

		glPushMatrix();
	}
	//----------------------------------------------------------------
	void Billboard::drawingEnd() const
	{
		glPopMatrix();

		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
	//----------------------------------------------------------------
	void Billboard::draw()
	{
		// 检查错误
		VG_CHECK_OPENGL_ERROR();

		this->drawingBegin();	

		this->updateCurrentViewVectors();
		
		if ( this->mIfVisible )
		{
			this->mTexturePtr->useBind();


			switch( mRenderType )
			{
			case RENDERTYPE_EYE_ORIENTED:
				{
					this->drawUsingEyeOriented();
					
					break;
				}
			case RENDERTYPE_ROTATE_Y:
				{
					this->drawUsingRotatedY();
					break;
				}
			case RENDERTYPE_HOLD_STILL:
				{
					this->drawUsingHoldStill();
					break;
				}
			default :
				this->drawUsingEyeOriented();
			}
		}

		 //draw edge
		if ( this->mIfSelected )
		{
			glColor4f( msEdgeColor.r, msEdgeColor.g, msEdgeColor.b , msEdgeColor.a );

			switch( mRenderType )
			{
			case RENDERTYPE_EYE_ORIENTED:
				{
					this->drawEdgeUsingEyeOriented();
					break;
				}
			case RENDERTYPE_ROTATE_Y:
				{
					this->drawEdgeUsingRotateY();
					break;
				}
			case RENDERTYPE_HOLD_STILL:
				{
					this->drawEdgeUsingHoldStill();
					break;
				}
			default :
				this->drawUsingEyeOriented();
			}
		}

		this->drawingEnd();

		// 检查错误
		VG_CHECK_OPENGL_ERROR();
	}
	//----------------------------------------------------------------
	void Billboard::extractVectorFromModelViewMatrix(
		Vector3& right , Vector3& up , Vector3& direction )
	{
		Real mat[16];
		glGetFloatv( GL_MODELVIEW_MATRIX, mat );

		right.reset( mat[0] , mat[4] , mat[8]);
		//livenson add 2009.01.06 for mirror effect of water
		up.reset(abs(mat[1])  ,abs( mat[5]) , abs(mat[9]));
		direction.reset( mat[2] , mat[6] , mat[10] );
	}
	//----------------------------------------------------------------
	void Billboard::updateCurrentViewVectors()
	{
		extractVectorFromModelViewMatrix(
			mCurrentViewRight , mCurrentViewUp , mCurrentViewDirection );
	}
	//----------------------------------------------------------------
	void Billboard::drawEdgeUsingEyeOriented() const
	{
		const Vector3  dw = mCurrentViewRight * mWidth * 0.5f;
		const Vector3  dh = mCurrentViewUp * mHeight * 0.5f; 

		const Vector3&  pos = this->mPosition;

		glDisable(GL_TEXTURE_2D);
		//glTranslatef( 0 , mHeight / 2 , 0 );

		glBegin(GL_LINE_LOOP);
		{
			glTexCoord2f(0.0,0.0);	
			glVertex3fv( (pos - dw - dh ).v );//左下点		

			glTexCoord2f(1.0,0.0);
			glVertex3fv( (pos + dw - dh ).v);//右下点

			glTexCoord2f(1.0,1.0);
			glVertex3fv( (pos + dw + dh ).v);//右上点

			glTexCoord2f(0.0,1.0);
			glVertex3fv( (pos - dw + dh ).v);//左上点
		}
		glEnd();
	}
	//----------------------------------------------------------------
	void Billboard::drawEdgeUsingRotateY() const
	{
		const Vector3 up = mRotatedAxis * mHeight * mScale;
		const Vector3& pos = mPosition;

		const Vector3 right = mCurrentViewRight * mWidth * 0.5f * mScale;

		glDisable( GL_TEXTURE_2D );

		glBegin(GL_LINE_LOOP);
		{
			glTexCoord2f(0.0f, 0.0f); 
			glVertex3fv( ( pos - right ).v );
			glTexCoord2f(1.0f, 0.0f); 
			glVertex3fv( ( pos + right ).v );
			glTexCoord2f(1.0f, 1.0f); 
			glVertex3fv( ( pos + right + up  ).v );
			glTexCoord2f(0.0f, 1.0f); 
			glVertex3fv( ( pos - right + up  ).v );
		}
		glEnd();
	}
	//----------------------------------------------------------------
	void Billboard::drawUsingRotatedY() const
	{
		const Vector3 up = mRotatedAxis * mHeight * mScale;
		const Vector3 &pos = this->mPosition ;

		const Vector3 right = mCurrentViewRight * mWidth * 0.5f * mScale;

		// texture binded in draw()
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 0.0f); 
			glVertex3fv( ( pos - right ).v );
			glTexCoord2f(1.0f, 0.0f); 
			glVertex3fv( ( pos + right ).v );
			glTexCoord2f(1.0f, 1.0f); 
			glVertex3fv( ( pos + right + up  ).v );
			glTexCoord2f(0.0f, 1.0f); 
			glVertex3fv( ( pos - right + up  ).v );
		}
		glEnd();
	}
	//----------------------------------------------------------------
	String Billboard::getDetails() const
	{
		std::ostringstream o;
		o << "\n-- Billboard details begin: "
			<< " UniqueName : " << *this->mUniqueNamePtr
			<< " \n  mTexturePtr : " << this->mTexturePtr->getDetails()
			<< " \n  mPosition : " << this->mPosition 
			<< " , msEdgeColor : " << msEdgeColor
			<< " , mWidth : " << this->mWidth
			<< " , mHeight : " << this->mHeight
			<< " , mIfVisible : " <<	this->mIfVisible
			<< " , mIfSelected : " << this->mIfSelected
			<< " , mRenderType : " << this->mRenderType 
			<< " , mRotatedAxis : " << this->mRotatedAxis
			<< "\n-- Billboard details end.\n";

		return o.str();
	}
	//----------------------------------------------------------------
	void Billboard::drawUsingHoldStill() const
	{
		const Integer& width = this->mWidth * mScale;
		const Integer& height = this->mHeight * mScale;

		const Vector3& pos = this->mPosition;

		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0,0.0);	
			glVertex3f( pos.x  , pos.y , pos.z );//左下点		

			glTexCoord2f(1.0,0.0);
			glVertex3f( pos.x + width , pos.y , pos.z );//右下点

			glTexCoord2f(1.0,1.0);
			glVertex3f( pos.x  + width, pos.y + height, pos.z );//右上点

			glTexCoord2f(0.0,1.0);
			glVertex3f( pos.x  , pos.y + height , pos.z );//左上点
		}
		glEnd();
	}
	//----------------------------------------------------------------
	void Billboard::drawEdgeUsingHoldStill() const
	{
		glDisable( GL_TEXTURE_2D );
		const Integer& width = this->mWidth;
		const Integer& height = this->mHeight;

		const Vector3& pos = this->mPosition;

		glBegin(GL_LINE_LOOP);
		{
			glTexCoord2f(0.0,0.0);	
			glVertex3f( pos.x  , pos.y , pos.z );//左下点		

			glTexCoord2f(1.0,0.0);
			glVertex3f( pos.x + width , pos.y , pos.z );//右下点

			glTexCoord2f(1.0,1.0);
			glVertex3f( pos.x  + width, pos.y + height, pos.z );//右上点

			glTexCoord2f(0.0,1.0);
			glVertex3f( pos.x  , pos.y + height , pos.z );//左上点
		}
		glEnd();
	}
	//----------------------------------------------------------------
	void Billboard::setWidth( const Real& val )
	{
		this->mWidth = val;
	}
	//----------------------------------------------------------------
	Real& Billboard::getWidth()
	{
		return this->mWidth;
	}
	//----------------------------------------------------------------
	const Real Billboard::getWidth() const
	{
		return this->mWidth;
	}
	//----------------------------------------------------------------
	void Billboard::setHeight( const Real& val )
	{
		this->mHeight = val;
	}
	//----------------------------------------------------------------
	Real& Billboard::getHeight()
	{
		return this->mHeight;
	}
	//----------------------------------------------------------------
	const Real Billboard::getHeight() const
	{
		return this->mHeight;
	}
	//----------------------------------------------------------------
	void Billboard::setRenderType( const RenderTypes& val )
	{
		this->mRenderType = val;
	}
	//----------------------------------------------------------------
	Billboard::RenderTypes& Billboard::getRenderType()
	{
		return this->mRenderType;
	}
	//----------------------------------------------------------------
	const Billboard::RenderTypes Billboard::getRenderType() const
	{
		return this->mRenderType;
	}
	//----------------------------------------------------------------
	void Billboard::setTexturePtr( const TexturePtr& val )
	{
		this->mTexturePtr = val;
	}
	//----------------------------------------------------------------
	TexturePtr& Billboard::getTexturePtr()
	{
		return this->mTexturePtr;
	}
	//----------------------------------------------------------------
	const TexturePtr Billboard::getTexturePtr() const
	{
		return this->mTexturePtr;
	}
	//----------------------------------------------------------------
	void Billboard::setIfSelected( const bool& val )
	{
		this->mIfSelected = val;
	}
	//----------------------------------------------------------------
	bool& Billboard::getIfSelected()
	{
		return this->mIfSelected;
	}
	//----------------------------------------------------------------
	const bool Billboard::getIfSelected() const
	{
		return this->mIfSelected;
	}
	//----------------------------------------------------------------
	void Billboard::setPosition( const Vector3& val )
	{
		this->mPosition = val;
	}
	//----------------------------------------------------------------
	Vector3& Billboard::getPosition()
	{
		return this->mPosition;
	}
	//----------------------------------------------------------------
	const Vector3 Billboard::getPosition() const
	{
		return this->mPosition;
	}
	//----------------------------------------------------------------
	void Billboard::setIfVisible( const bool& val )
	{
		this->mIfVisible = val;
	}
	//----------------------------------------------------------------
	bool& Billboard::getIfVisible()
	{
		return this->mIfVisible;
	}
	//----------------------------------------------------------------
	const bool Billboard::getIfVisible() const
	{
		return this->mIfVisible;
	}
	//----------------------------------------------------------------
	const StringPtr Billboard::getUniqueNamePtr() const
	{
		return this->mUniqueNamePtr;
	}
	//----------------------------------------------------------------
	void Billboard::setRotatedAxis( const Vector3& val )
	{
		this->mRotatedAxis = val;
	}
	//----------------------------------------------------------------
	Vector3& Billboard::getRotatedAxis()
	{
		return this->mRotatedAxis;
	}
	//----------------------------------------------------------------
	const Vector3 Billboard::getRotatedAxis() const
	{
		return this->mRotatedAxis;
	}
	//----------------------------------------------------------------
	void Billboard::setParametersDefault()
	{
		//this->mUniqueID = -1;
		this->mIfVisible = true;
		this->mIfSelected = false;
		this->mPosition = Vector3::ZERO;
		this->mRenderType = RENDERTYPE_ROTATE_Y;
		this->mUniqueNamePtr = StringPtr::EmptyBillboardStrPtr;
		this->mTexturePtr = TexturePtr::EmptyTexturePtr;
		this->mHeight = DEFAULT_RECT_HEIGHT;
		this->mWidth = DEFAULT_RECT_WIDTH;
		this->mRotatedAxis = Vector3::UNIT_Y;

		this->mScale = 1.0f;
	}
	//----------------------------------------------------------------
	void Billboard::autoUpdateRect()
	{
		if ( !this->mTexturePtr.isEmpty() )
		{
			this->mWidth = 
				mTexturePtr->getWidth() * PIXCEL_TO_FLOAT_FACTOR;
			this->mHeight = 
				mTexturePtr->getHeight() * PIXCEL_TO_FLOAT_FACTOR;
		}
	}
	//----------------------------------------------------------------
	void Billboard::setScale( const Real& scale )
	{
		assert( scale < 1000000000 );

		this->mScale = scale;

		//this->mWidth *= scale;
		//this->mHeight *= scale;
	}
	//----------------------------------------------------------------
	void Billboard::setParameters( const StringPtr& uniname ,  
		const TexturePtr& ptex , const Vector3& pos ,  
		const bool& selected ,const bool& visible , 
		const RenderTypes& rendertype , 
		const Real& width ,const Real& height ,  
		const Vector3& upVector )
	{
		this->mIfVisible	= visible;
		this->mIfSelected	= selected;
		this->mPosition		= pos;
		this->mRenderType	= rendertype;
		this->mUniqueNamePtr = uniname;
		this->mTexturePtr	= ptex;
		this->mHeight		= height;
		this->mWidth		= width;
		this->mRotatedAxis	= upVector;
	}
	//----------------------------------------------------------------
	void Billboard::reverseRenderType()
	{
		if ( this->mRenderType == RENDERTYPE_EYE_ORIENTED )
		{
			this->mRenderType = RENDERTYPE_ROTATE_Y;
			return;
		}
		this->mRenderType = RENDERTYPE_ROTATE_Y;
		return;
	}
	//----------------------------------------------------------------
	void Billboard::create( const StringPtr& uniname ,  
		const TexturePtr& ptex , const Vector3& pos /*= Vector3::ZERO */ )
	{
		this->mUniqueNamePtr = uniname;
		this->mTexturePtr	= ptex;
		this->mPosition		= pos;

		this->autoUpdateRect();
	}
	//----------------------------------------------------------------
	void Billboard::create( const String& uniname , const TexturePtr& ptex , 
		const Vector3& pos /*= Vector3::ZERO */ )
	{
		this->create( StringUtil::createStringPtr( uniname ) , ptex , pos );
	}
	//----------------------------------------------------------------
	void Billboard::create( const String& uniname ,  const String& texUniName , 
		const Vector3& pos /*= Vector3::ZERO */ )
	{
		this->create( uniname ,
			TextureManager::getSingleton().getTexturePtr( texUniName ) , pos );
	}
	//----------------------------------------------------------------









	//----------------------------------------------------------------
	std::istream& operator >> ( std::istream& in , Billboard& bbd )
	{
		Vector3 pos;
		Real   scale;
		int rendertype;
		char buf[255];

		// 读位置信息
		in >> pos;

		// 读到末尾
		in.getline( buf , 255 , '\n');

		// 读取Scale值
		in >> scale;

		// 读到末尾
		in.getline( buf , 255 , '\n');

		// 读billboard的uniname
		in.getline( buf , 255 , '\n' );
		String bbd_uniname( buf );

		//// 读纹理的uniname
		//in.getline( buf , 255 , '\n' );
		//String tex_uniname( buf );

		// 读纹理的filepath
		in.getline( buf , 255 , '\n' );
		String tex_filepath( buf );

		/// 读取rendertype
		in >> rendertype;
		in.getline( buf , 255 , '\n' );

		StringUtil::trim( tex_filepath , true , true );

		TextureManager *pmgr = TextureManager::getSingletonPtr();

		assert( pmgr != NULL );

		bbd.mUniqueNamePtr = StringUtil::createStringPtr( bbd_uniname );
		bbd.setPosition( pos );


		// 这里以后要改！！
		// 直接把纹理名称当作texuniname实际上并不好。
		bbd.setTexturePtr( pmgr->getTexturePtr( tex_filepath /*, false , false*/ ) );

		bbd.mScale = scale;

		bbd.mRenderType = static_cast<Billboard::RenderTypes>(rendertype) ;

		bbd.autoUpdateRect();

		return in;
	}
	//----------------------------------------------------------------
	std::ostream& operator << ( std::ostream& out , Billboard& bbd )
	{
		out << bbd.getPosition() << '\n';

		out << bbd.mScale << '\n';

		out << *(bbd.mUniqueNamePtr) << '\n';
		
		out << bbd.mTexturePtr->getFilePath() << '\n';

		out << bbd.mRenderType << '\n';

		return out;
	}
	//----------------------------------------------------------------



}// end of namespace vgCore
