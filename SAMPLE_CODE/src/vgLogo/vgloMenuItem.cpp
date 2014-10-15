
#include <vgStableHeaders.h>

#include <vgLogo/vgloMenuItem.h>

#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgImage/vgiFreeImageWrapper.h>

#include <vgConf/vgcoExeConfig.h>

#define VGDATA_PATHCONF						"DataPathConfig"
#define VGDATA_PATHCONF_TEXTURE_PATH		"TexturePath"

#define VGDATA_FILECONF						"DataFileConfig"
#define VGDATA_FILECONF_TEXTURE_LOGO		"MenuLogoName"

//----------------------------------------------------------------
namespace	vgLogo
{

	//----------------------------------------------------------------
	MenuItem::MenuItem( String name/* = ""*/, 
		UINT id/* = 0*/, 
		MenuItemType type/* = USER_MENU_LEAF*/,
		MenuItem* pParent/* = NULL*/
		 )
		:_id(id)
		,_name(name)
		,_type(type)
		, _pParent(pParent)
	{
		// 首先分配一个纹理ID空间，保证无贴图渲染
		m_textureID = new GLuint[1];
	}

	MenuItem::MenuItem(const MenuItem& item )
	{
		*this = item;
	}

	//----------------------------------------------------------------
	MenuItem::~MenuItem()
	{
		this->unloadData();
	}

	//----------------------------------------------------------------
	void MenuItem::appendSubItem( MenuItem* item )
	{
		_subItems.push_back(item);
	}

	void MenuItem::appendSubItem( String name/* = ""*/, 
		UINT id/* = 0*/, 
		MenuItemType type/* = USER_MENU_LEAF*/,
		MenuItem* pParent/* = NULL*/
		)
	{
		//_subItems.push_back( MenuItem(name,  id, type) );
	}
	//----------------------------------------------------------------
	bool MenuItem::hasSubItem()
	{
		return USER_MENU_BRANCH == _type;
	}

	//----------------------------------------------------------------
	MenuItem& MenuItem::operator=( const MenuItem& item )
	{
		_type	= item._type;
		_id		= item._id;
		_name	= item._name;

		_subItems = item._subItems;
		return *this;
	}
	
	//----------------------------------------------------------------
	MenuItemVecL1* MenuItem::getSubItems()
	{
		return &_subItems;
	}

	//----------------------------------------------------------------
	MenuItem* MenuItem::getSubItemByName(String leaf_name)
	{
		return getSubItemByName(leaf_name, &_subItems);
	}
	
	//----------------------------------------------------------------
	MenuItem* MenuItem::getSubItemByName(String leaf_name,
		MenuItemVecL1* pMenuItems)
	{
		for (MenuItemVecL1::iterator itr = pMenuItems->begin();
			itr != pMenuItems->end(); itr ++ )
		{
			if ( (*itr)->_type == USER_MENU_LEAF
				&& (*itr)->_name == leaf_name )
			{
				return *itr;
			}

			else
			{
				return getSubItemByName( leaf_name, (*itr)->getSubItems() );
			}
		}

		return NULL;
	}
	
	//----------------------------------------------------------------
	MenuItem* MenuItem::getSubItemByID(UINT leaf_id)
	{
		return getSubItemByID(leaf_id, &_subItems);
	}

	//----------------------------------------------------------------
	vgLogo::MenuItem* MenuItem::getSubItemByID(UINT leaf_id,
		MenuItemVecL1* pMenuItems)
	{
		for (MenuItemVecL1::iterator itr = pMenuItems->begin();
			itr != pMenuItems->end(); itr ++ )
		{
			if ( (*itr)->_type == USER_MENU_LEAF 
				&& (*itr)->_id == leaf_id )
			{
				return *itr;
			}

			else
			{
				return getSubItemByID( leaf_id, (*itr)->getSubItems() );
			}
		}

		return NULL;
	}

	UINT& MenuItem::getID()
	{
		return _id;
	}

	String& MenuItem::getName()
	{
		return _name;
	}

	MenuItemType& MenuItem::getType()
	{
		return _type;
	}
	
	MenuItem* MenuItem::getParentPtr()
	{
		return _pParent;
	}

	void MenuItem::setParentPtr( MenuItem* parent )
	{
		_pParent = parent;
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	void MenuItem::unloadData()
	{
		if ( m_textureID == NULL )
		{
			return;
		}

		for ( int i = 0; i < sizeof( m_textureID ) / sizeof( m_textureID[0] ); i++ )
		{
			if ( m_textureID[i] != 0 )
			{
				glDeleteTextures( 1, &m_textureID[i] );
				m_textureID[i] = 0;
			}
		}

		delete[] m_textureID;
		m_textureID = NULL;
	}

	//--------------------------------------------------------------------
	// Load Bitmaps And Convert To Textures
	void  MenuItem::loadTexture( vgKernel::StringVector fileNames )	
	{
		int fileNums = fileNames.size();

		//当纹理数多于一张时,首先释放初始时分配的内存，再重新分配空间
		if ( fileNums > 1 && m_textureID != NULL )
		{
			delete[] m_textureID;
			m_textureID = new GLuint[fileNums];
		}

		String exepath = vgKernel::SystemUtility::getCurrentProcessPath();

		String texturePath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_TEXTURE_PATH);

		for ( int i = 0; i < fileNums; i++ )
		{
			String logopath = exepath + texturePath + fileNames[i];
			
			vgImage::FreeImageWrapper img;

			img.loadFromFile( logopath.c_str() );

			if ( img.getImageSize() == 0 )
			{
				return;
			}

			img.swapRedAndBlueChannel();

			if ( img.getInfoHeader()->biBitCount == 24)
			{
				glGenTextures(1, &m_textureID[i]);					// Create 1 Textures
				glBindTexture(GL_TEXTURE_2D, m_textureID[i]);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,  img.getWidth(), img.getHeight(),
					GL_RGB, GL_UNSIGNED_BYTE, img.accessAlignedPixels());
			}
			else if (  img.getInfoHeader()->biBitCount == 32 )
			{
				glGenTextures(1, &m_textureID[i]);					// Create 1 Textures
				glBindTexture(GL_TEXTURE_2D, m_textureID[i]);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA,  img.getWidth(), img.getHeight(),
					GL_RGBA, GL_UNSIGNED_BYTE, img.accessAlignedPixels());
			}
		}

		
	}

	void MenuItem::render()
	{
		if ( !getRenderState() )
		{
			return;
		}
		else
		{
			glPushAttrib(GL_CURRENT_BIT);

			//////////////////////////////////////////////////////////////////////////
			glMatrixMode( GL_PROJECTION );
			glPushMatrix();
			glLoadIdentity();

			glMatrixMode( GL_MODELVIEW );
			glPushMatrix();
			glLoadIdentity();
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

			glAlphaFunc(GL_GREATER, 0.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_ALPHA_TEST);
			glEnable(GL_BLEND);

			glDisable(GL_DEPTH_TEST);

			//////////////////////////////////////////////////////////////////////////

			glEnable(GL_TEXTURE_2D);
			glColor3f(1,1,1);
			assert( m_textureID != NULL );
			glBindTexture( GL_TEXTURE_2D, m_textureID[m_currentTexID] );

			float halfWidth = getLogoWidth()/2.0;
			float halfHeight = getLogoHeight()/2.0;

			glTranslatef( getCenterPos()->x, getCenterPos()->y, 0 );

			glBegin(GL_POLYGON);   
				glTexCoord2i(0,0);
				glVertex3f( (-1)*halfWidth,(-1) * halfHeight,0.0 );
				glTexCoord2i(0,1);
				glVertex3f( (-1)*halfWidth,halfHeight,0.0 );
				glTexCoord2i(1,1);
				glVertex3f( halfWidth,halfHeight,0.0 );
				glTexCoord2i(1,0);
				glVertex3f( halfWidth,(-1) * halfHeight,0.0 );
			glEnd();

			glDisable(GL_TEXTURE_2D);

			//////////////////////////////////////////////////////////////////////////
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);
			glDisable( GL_ALPHA_TEST );

			glMatrixMode( GL_PROJECTION );
			glPopMatrix();

			glMatrixMode( GL_MODELVIEW );
			glPopMatrix();

			glPopAttrib();
		}
		return;

	}



	bool MenuItem::textPointInRect( CPoint point )
	{
		//坐标系转换
		int viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );
		float x = ( point.x * 2 ) / (float)viewport[2];
		float y = ( -point.y + viewport[3] ) * 2 / (float)viewport[3];

		x = x - 1;
		y = y - 1;

		//计算图标的x,y最值
		float xmin = getCenterPos()->x - getLogoWidth()/2.0;
		float xmax = getCenterPos()->x + getLogoWidth()/2.0;
		float ymin = getCenterPos()->y - getLogoHeight()/2.0;
		float ymax = getCenterPos()->y + getLogoHeight()/2.0;

		//比较point 与 是否在rect内
		if ( x >= xmin && x <= xmax && y >= ymin && y<= ymax )
		{
			return true;
		}

		return false;
	}

}// namespace	vgKernelSDK

