
#include <vgStableHeaders.h>
#include <vgLogo/vgloMenuLogo.h>
#include <vgLogo/vgloLogoManager.h>

#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgImage/vgiFreeImageWrapper.h>

#include <vgConf/vgcoExeConfig.h>

#define VGDATA_PATHCONF						"DataPathConfig"
#define VGDATA_PATHCONF_TEXTURE_PATH		"TexturePath"

#define VGDATA_FILECONF						"DataFileConfig"
#define VGDATA_FILECONF_TEXTURE_LOGO		"LogoName"


namespace vgLogo {  


	//----------------------------------------------------------------
	MenuLogo::MenuLogo()
	{
		m_varyType = NONE;
		m_dWidth = 512.0;
		m_dHeight = 477.0;

		int viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );
		m_lastViewWidth = viewport[2];
		m_lastViewHeight = viewport[3];

		SetHandleStatus( VG_MENU_LOGO );
		vgKernel::InputSystem::getSingleton().registerHandle(this);
		vgKernel::InputSystem::getSingleton().setCurrentStatus( VG_MENU_LOGO | 
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_SELECT | VG_INPUTMODE_UI );
	}

	//----------------------------------------------------------------
	MenuLogo::~MenuLogo()
	{
		this->uninitMenuLogo( &m_rootMenu );  //卸载数据
	}

	//-----------------------------------------------------------
	void MenuLogo::initMenuLogoLD()
	{
		MenuItem &menuItemLayer1 = m_rootMenu;

		vgKernel::StringVector fileNames;
		//****************************************************************
		MenuItem* menuItemLayer2;
		menuItemLayer2 = new MenuItem( "M2L11", 1, USER_MENU_LEAF );
		menuItemLayer2->setLogoWidth( (float)0.1 );
		menuItemLayer2->setCenterPos( vgKernel::Vec2( (float)-0.9, (float)-1.0 ), false );
		menuItemLayer2->setWCounter( -1 );
		fileNames.push_back( "MenuLogoLeft6.tga" );
		menuItemLayer2->loadTexture( fileNames );
		menuItemLayer1.appendSubItem( menuItemLayer2 ); 
		//****************************************************************
		menuItemLayer2 = new MenuItem( "M2L12", 2, USER_MENU_LEAF );
		menuItemLayer2->setLogoWidth( (float)0.1 );
		menuItemLayer2->setCenterPos( vgKernel::Vec2( (float)-0.8, (float)-1.0 ), false );
		menuItemLayer2->setWCounter( -3 );
		fileNames.clear();
		fileNames.push_back( "MenuLogoLeft5.tga" );
		menuItemLayer2->loadTexture( fileNames );
		menuItemLayer1.appendSubItem( menuItemLayer2 ); 
		//****************************************************************
		menuItemLayer2 = new MenuItem( "M2L13", 3, USER_MENU_LEAF );
		menuItemLayer2->setLogoWidth( (float)0.1 );
		menuItemLayer2->setCenterPos( vgKernel::Vec2( (float)-0.7, (float)-1.0 ), false );
		menuItemLayer2->setWCounter( -5 );
		fileNames.clear();
		fileNames.push_back( "MenuLogoLeft4.tga" );
		menuItemLayer2->loadTexture( fileNames );
		menuItemLayer1.appendSubItem( menuItemLayer2 ); 
		//****************************************************************
		menuItemLayer2 = new MenuItem( "M2L14", 4, USER_MENU_LEAF );
		menuItemLayer2->setLogoWidth( (float)0.1 );
		menuItemLayer2->setCenterPos( vgKernel::Vec2( (float)-0.6, (float)-1.0 ), false );
		menuItemLayer2->setWCounter( -7 );
		fileNames.clear();
		fileNames.push_back( "MenuLogoLeft3.tga" );
		menuItemLayer2->loadTexture( fileNames );
		menuItemLayer1.appendSubItem( menuItemLayer2 ); 
		//****************************************************************
		menuItemLayer2 = new MenuItem( "M2L15", 5, USER_MENU_LEAF );
		menuItemLayer2->setLogoWidth( (float)0.1 );
		menuItemLayer2->setCenterPos( vgKernel::Vec2( (float)-0.5, (float)-1.0 ), false );
		menuItemLayer2->setWCounter( -9 );
		fileNames.clear();
		fileNames.push_back( "MenuLogoLeft2.tga" );
		menuItemLayer2->loadTexture( fileNames );
		menuItemLayer1.appendSubItem( menuItemLayer2 ); 
		//****************************************************************
		menuItemLayer2 = new MenuItem( "M2L16", 6, USER_MENU_LEAF );
		menuItemLayer2->setLogoWidth( (float)0.1 );
		menuItemLayer2->setCenterPos( vgKernel::Vec2( (float)-0.4, (float)-1.0 ), false );
		menuItemLayer2->setWCounter( -11 );
		fileNames.clear();
		fileNames.push_back( "MenuLogoLeft1.tga" );
		menuItemLayer2->loadTexture( fileNames );
		menuItemLayer1.appendSubItem( menuItemLayer2 ); 

	}

	//-----------------------------------------------------------
	void MenuLogo::initMenuLogoRD()
	{
		MenuItem &menuItemLayer1 = m_rootMenu;
		menuItemLayer1.setRenderState( false );  //根本身不渲染
		menuItemLayer1.setSubRenderState( true );//根的子项渲染

		MenuItem* menuItemLayer2;
		MenuItem* menuItemLayer3;
		MenuItem* menuItemLayer4;

		vgKernel::StringVector fileNames;
		//*******************返回上一级按纽*******************************
		menuItemLayer2 = new MenuItem( "return", 1000, USER_MENU_LEAF );   // new 出对象
		menuItemLayer2->setLogoWidth( (float)0.1 );  // 设置宽度,同时根据屏幕宽高比计算高度
		menuItemLayer2->setCenterPos( vgKernel::Vec2( (float)1.0, (float)-1.0 ), false );// 设置中心位置
		menuItemLayer2->setWCounter( 1 ); 
		fileNames.clear();
		fileNames.push_back( "半透明.tga" );
		fileNames.push_back( "返回2.tga" );
		menuItemLayer2->loadTexture( fileNames );          // 加载贴图
		menuItemLayer2->setRenderState( false );           // 设置渲染状态
		menuItemLayer2->setParentPtr( &menuItemLayer1 );   // 设置父节点 

		menuItemLayer1.appendSubItem( menuItemLayer2 );

		//****************************************************************
		menuItemLayer2 = new MenuItem( "M1L11", 1, USER_MENU_BRANCH );
		menuItemLayer2->setLogoWidth( (float)0.1 );                  
		menuItemLayer2->setCenterPos( vgKernel::Vec2( 1.0, -1.0 ), false );     
		menuItemLayer2->setWCounter( 1 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo6.tga" );
		fileNames.push_back( "MenuLogo6In.tga" );
		menuItemLayer2->loadTexture( fileNames );          
		menuItemLayer2->setParentPtr( &menuItemLayer1 );

		menuItemLayer3 = new MenuItem( "M1L211", 11, USER_MENU_BRANCH );
		menuItemLayer3->setLogoWidth( (float)0.1 );
		menuItemLayer3->setCenterPos( vgKernel::Vec2( (float)0.9, (float)-1.0 ), false );
		menuItemLayer3->setWCounter( 3 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo5.tga" );
		fileNames.push_back( "MenuLogo5In.tga" );
		menuItemLayer3->loadTexture( fileNames );
		menuItemLayer3->setParentPtr( menuItemLayer2 );

		menuItemLayer4 = new MenuItem( "M1L3111", 111, USER_MENU_LEAF );
		menuItemLayer4->setLogoWidth( (float)0.1 );
		menuItemLayer4->setCenterPos( vgKernel::Vec2( (float)0.9, (float)-1.0 ), false );
		menuItemLayer4->setWCounter( 3 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo2.tga" );
		fileNames.push_back( "MenuLogo2In.tga" );
		menuItemLayer4->loadTexture( fileNames );
		menuItemLayer4->setParentPtr( menuItemLayer3 );
		menuItemLayer3->appendSubItem( menuItemLayer4 );

		menuItemLayer2->appendSubItem( menuItemLayer3 );


		menuItemLayer3 = new MenuItem( "M1L212", 12, USER_MENU_LEAF );
		menuItemLayer3->setLogoWidth( (float)0.1 );
		menuItemLayer3->setCenterPos( vgKernel::Vec2( (float)0.8, (float)-1.0 ), false );
		menuItemLayer3->setWCounter( 5 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo4.tga" );
		fileNames.push_back( "MenuLogo4In.tga" );
		menuItemLayer3->loadTexture( fileNames );
		menuItemLayer3->setParentPtr( menuItemLayer2 );
		menuItemLayer2->appendSubItem( menuItemLayer3 );

		menuItemLayer3 = new MenuItem( "M1L213", 13, USER_MENU_LEAF );
		menuItemLayer3->setLogoWidth( (float)0.1 );
		menuItemLayer3->setCenterPos( vgKernel::Vec2( (float)0.7, (float)-1.0 ), false );
		menuItemLayer3->setWCounter( 7 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo2.tga" );
		fileNames.push_back( "MenuLogo2In.tga" );
		menuItemLayer3->loadTexture( fileNames );
		menuItemLayer3->setParentPtr( menuItemLayer2 );
		menuItemLayer2->appendSubItem( menuItemLayer3 );

		menuItemLayer3 = new MenuItem( "M1L214", 14, USER_MENU_LEAF );
		menuItemLayer3->setLogoWidth( (float)0.1 );
		menuItemLayer3->setCenterPos( vgKernel::Vec2( (float)0.6, (float)-1.0 ), false );
		menuItemLayer3->setWCounter( 9 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo1.tga" );
		fileNames.push_back( "MenuLogo1In.tga" );
		menuItemLayer3->loadTexture( fileNames );
		menuItemLayer3->setParentPtr( menuItemLayer2 );
		menuItemLayer2->appendSubItem( menuItemLayer3 );

		menuItemLayer1.appendSubItem( menuItemLayer2 );

		//****************************************************************
		menuItemLayer2 = new MenuItem( "M1L12", 2, USER_MENU_BRANCH );
		menuItemLayer2->setLogoWidth( (float)0.1 );
		menuItemLayer2->setCenterPos( vgKernel::Vec2( (float)0.9, (float)-1.0 ), false );
		menuItemLayer2->setWCounter( 3 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo5.tga" );
		fileNames.push_back( "MenuLogo5In.tga" );
		menuItemLayer2->loadTexture( fileNames );
		menuItemLayer2->setParentPtr( &menuItemLayer1 );

		menuItemLayer3 = new MenuItem( "M1L221", 21, USER_MENU_LEAF );
		menuItemLayer3->setLogoWidth( (float)0.1 );
		menuItemLayer3->setCenterPos( vgKernel::Vec2( (float)0.9, (float)-1.0 ), false );
		menuItemLayer3->setWCounter( 3 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo6.tga" );
		fileNames.push_back( "MenuLogo6In.tga" );
		menuItemLayer3->loadTexture( fileNames );
		menuItemLayer3->setParentPtr( menuItemLayer2 );
		menuItemLayer2->appendSubItem( menuItemLayer3 );

		menuItemLayer3 = new MenuItem( "M1L222", 22, USER_MENU_LEAF );
		menuItemLayer3->setLogoWidth( (float)0.1 );
		menuItemLayer3->setCenterPos( vgKernel::Vec2( (float)0.8, (float)-1.0 ), false );
		menuItemLayer3->setWCounter( 5 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo4.tga" );
		fileNames.push_back( "MenuLogo4In.tga" );
		menuItemLayer3->loadTexture( fileNames );
		menuItemLayer3->setParentPtr( menuItemLayer2 );
		menuItemLayer2->appendSubItem( menuItemLayer3 );

		menuItemLayer1.appendSubItem( menuItemLayer2 );
		//****************************************************************
		menuItemLayer2 = new MenuItem( "M1L13", 3, USER_MENU_LEAF );
		menuItemLayer2->setLogoWidth( (float)0.1 );
		menuItemLayer2->setCenterPos( vgKernel::Vec2( (float)0.8, (float)-1.0 ), false );
		menuItemLayer2->setWCounter( 5 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo4.tga" );
		fileNames.push_back( "MenuLogo4In.tga" );
		menuItemLayer2->loadTexture( fileNames );
		menuItemLayer2->setParentPtr( &menuItemLayer1 );
		menuItemLayer1.appendSubItem( menuItemLayer2 );
		//****************************************************************
		menuItemLayer2 = new MenuItem( "M1L14", 4, USER_MENU_LEAF );
		menuItemLayer2->setLogoWidth( (float)0.1 );
		menuItemLayer2->setCenterPos( vgKernel::Vec2( (float)0.7, (float)-1.0 ), false );
		menuItemLayer2->setWCounter( 7 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo3.tga" );
		fileNames.push_back( "MenuLogo3In.tga" );
		menuItemLayer2->loadTexture( fileNames );
		menuItemLayer2->setParentPtr( &menuItemLayer1 );
		menuItemLayer1.appendSubItem( menuItemLayer2 ); 
		//****************************************************************
		menuItemLayer2 = new MenuItem( "M1L15", 5, USER_MENU_LEAF );
		menuItemLayer2->setLogoWidth( (float)0.1 );
		menuItemLayer2->setCenterPos( vgKernel::Vec2( (float)0.6, (float)-1.0 ), false );
		menuItemLayer2->setWCounter( 9 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo2.tga" );
		fileNames.push_back( "MenuLogo2In.tga" );
		menuItemLayer2->loadTexture( fileNames );
		menuItemLayer2->setParentPtr( &menuItemLayer1 );
		menuItemLayer1.appendSubItem( menuItemLayer2 ); 
		//****************************************************************
		menuItemLayer2 = new MenuItem( "M1L16", 6, USER_MENU_LEAF );
		menuItemLayer2->setLogoWidth( (float)0.1 );
		menuItemLayer2->setCenterPos( vgKernel::Vec2( (float)0.5, (float)-1.0 ), false );
		menuItemLayer2->setWCounter( 11 );
		fileNames.clear();
		fileNames.push_back( "MenuLogo1.tga" );
		fileNames.push_back( "MenuLogo1In.tga" );
		menuItemLayer2->loadTexture( fileNames );
		menuItemLayer2->setParentPtr( &menuItemLayer1 );
		menuItemLayer1.appendSubItem( menuItemLayer2 ); 

		//////////////////////////////////////////////////////////////////////////
		clearCurrentItemVec();
		findCurrentItems( &m_rootMenu );
	}

	//-----------------------------------------------------------
	void MenuLogo::uninitMenuLogo( MenuItem* pRootMenuItem )
	{
		if ( !pRootMenuItem->hasSubItem() )
		{
			return;
		}

		MenuItemVecL1* pMenuItemVec = pRootMenuItem->getSubItems();
		MenuItemVecL1Itr itr = pMenuItemVec->begin();
		MenuItemVecL1Itr itr_end = pMenuItemVec->end();

		for ( ; itr != itr_end; itr++ )
		{
			if ( (*itr)->hasSubItem() )
			{
				this->uninitMenuLogo( (*itr) );  //如果有子节点则递归卸载

				(*itr)->unloadData();

				//释放vector 中new出来的内存
				delete (*itr);
				*itr = NULL;
			}
			else
			{
				(*itr)->unloadData();   //如果是叶节点则直接卸载

				//释放vector 中new出来的内存
				delete (*itr);
				*itr = NULL;
			}
		}
	}

	//-----------------------------------------------------------
	void MenuLogo::reset()
	{/*
		m_bRender = true;
		m_centerPos = vgKernel::Vec2();
		m_logoHeight = 0.1f;                             
		m_logoWidth = 0.1f;*/
	
	}

	//-----------------------------------------------------------
	void MenuLogo::render()
	{
		//当渲染窗口大小变化时重新计算Logo的参数
		int viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );

		//只宽度变化
		if ( viewport[2] != m_lastViewWidth && viewport[3] == m_lastViewHeight )
		{
			m_lastViewWidth = viewport[2];
			this->setVaryType( WIDTH );
		}
		//只高度变化 
		if ( viewport[3] != m_lastViewHeight && viewport[2] == m_lastViewWidth )
		{
			m_lastViewHeight = viewport[3];
			this->setVaryType( HEIGHT );
		}
		//高度宽度都变化
		if ( viewport[2] != m_lastViewWidth && viewport[3] != m_lastViewHeight )
		{
			m_lastViewWidth = viewport[2];
			m_lastViewHeight = viewport[3];
			this->setVaryType( BOTH );
		}

		//根据窗口变化类型，重新计算MenuLogo各参数
		if ( m_varyType != NONE )
		{
			this->recalculate( &m_rootMenu );
			this->setVaryType( NONE );
		}

		//渲染Logo
		this->render( &m_rootMenu );
	}

	//-----------------------------------------------------------
	void MenuLogo::render( MenuItem* pRootMenuItem )
	{	
		if ( !pRootMenuItem->getRenderState() && !pRootMenuItem->getSubRenderState() )
		{
			//本身及子节点都不可渲染时返回
			return;
		}
		
		MenuItemVecL1* pMenuItemVec = pRootMenuItem->getSubItems();

		MenuItemVecL1Itr itr = pMenuItemVec->begin();
		MenuItemVecL1Itr itr_end = pMenuItemVec->end();

		for ( ; itr != itr_end; itr++ )
		{
			if ( (*itr)->hasSubItem() )
			{
				//如果有子节点且子节点可渲染
				if ( (*itr)->getSubRenderState() )
				{
					//如果子节点可渲染
					render( (*itr) );

					(*itr)->render();
				}
				if ( (*itr)->getRenderState() )
				{
					//如果自身可渲染
					(*itr)->render();
				}
			}
			else
			{
				(*itr)->render();
			}
		}
	}
	//-----------------------------------------------------------
	void MenuLogo::recalculate( MenuItem* pRootMenuItem )
	{
		MenuItemVecL1* pMenuItemVec = pRootMenuItem->getSubItems();

		MenuItemVecL1Itr itr = pMenuItemVec->begin();
		MenuItemVecL1Itr itr_end = pMenuItemVec->end();

		for ( ; itr != itr_end; itr++ )
		{
			if ( (*itr)->hasSubItem() )    //如果有子节点则循环处理
			{
				this->recalculate( (*itr) );

				this->recalculateData( (*itr) );
			}
			else  //如果是叶节点则直接处理
			{
				this->recalculateData( (*itr) );
			}
		}
	}

	//-----------------------------------------------------------
	void MenuLogo::recalculateData( MenuItem* pMenuItem )
	{
		int viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );

		// 1.恢复原始参数
		pMenuItem->setLogoWidth( pMenuItem->getOriginalWidth() );
		pMenuItem->setLogoHeight( pMenuItem->getOriginalHeight() );
		pMenuItem->setCenterPos( pMenuItem->getOriginalCenterPos(), true );
		// 2.计算比例
		float radio = viewport[2] / (float)viewport[3];

		float originalHeight = pMenuItem->getOriginalHeight();
		float originalWidth = pMenuItem->getOriginalWidth();

		if ( m_varyType == WIDTH )  //保持宽度比例，让高度变化
		{
#if 0  
			// 1.恢复原始参数
			pMenuItem->setLogoWidth( pMenuItem->getOriginalWidth() );
			pMenuItem->setLogoHeight( pMenuItem->getOriginalHeight() );
			pMenuItem->setCenterPos( (*pMenuItem->getOriginalCenterPos()), true );

			// 2.计算比例
			float ratio = viewport[2] / (float)viewport[3];
			float originalHeight = pMenuItem->getOriginalHeight();
#endif
			// 3.设置新的参数
			pMenuItem->setLogoHeight( originalHeight * radio );
			pMenuItem->getCenterPos()->y += 
				pMenuItem->getHCounter() * ( pMenuItem->getLogoHeight() - originalHeight ) / 2.0;
		}
		else if ( m_varyType == HEIGHT  )  //保持宽度比例，让宽度变化
		{
			//此比例须重新计算，与其它两种情况不同
			radio = ( viewport[3] / m_dHeight ) * ( m_dWidth / (float)viewport[2] );

			// 3.设置新的参数
			pMenuItem->setLogoWidth( originalWidth * radio );
			pMenuItem->getCenterPos()->x -= 
				pMenuItem->getWCounter() * ( pMenuItem->getLogoWidth() - originalWidth ) / 2.0;
		}
		else if ( m_varyType == BOTH )   //保持宽度比例，让高度变化
		{
			// 3.设置新的参数
			pMenuItem->setLogoHeight( originalHeight * radio );
			pMenuItem->getCenterPos()->y += 
				pMenuItem->getHCounter() * ( pMenuItem->getLogoHeight() - originalHeight ) / 2.0;
		}
	}

	//-----------------------------------------------------------
	void MenuLogo::OnLButtonDown(UINT nFlags, CPoint position)
	{
		//////////////////////////////////////////////////////////////////////////
		//为了排除左下角Logo对象对消息的响应，因其不触发事件
		MenuItemVecL1* pVec = m_rootMenu.getSubItems();
		if ( pVec->size() > 0 )
		{
			MenuItemVecL1Itr itr = pVec->begin();
			if ( (*itr)->getID() != 1000 )
			{
				return;
			}
		}
		else
		{
			return;
		}
		//////////////////////////////////////////////////////////////////////////

		int viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );

		float x = ( position.x - viewport[2] / 2.0 ) / ( viewport[2] / 2.0 );
		float y = ( viewport[3] / 2.0 - position.y ) / ( viewport[3] / 2.0 );

		MenuItemVecL1Itr itr = getCurrentItems()->begin();
		MenuItemVecL1Itr itr_end = getCurrentItems()->end();

		for ( ; itr != itr_end; itr++ )
		{
			float width = (*itr)->getLogoWidth();
			float height = (*itr)->getLogoHeight();

			vgKernel::Vec2* centerPos = (*itr)->getCenterPos();

			float xMin = centerPos->x - width / 2.0;
			float xMax = centerPos->x + width / 2.0;
			float yMin = centerPos->y - height / 2.0;
			float yMax = centerPos->y + height / 2.0;

			if ( x >= xMin && x <= xMax && y >= yMin && y <= yMax )
			{
				int id = (*itr)->getID();

				if( id == 1000 )  //返回上一级按纽
				{
					setItemState( m_currentItemVec[m_currentItemVec.size()-1], true );
					clearCurrentItemVec();
					findCurrentItems( &m_rootMenu );
				} 
				else
				{
					if ( (*itr)->hasSubItem() )  //渲染子节点Item
					{
						setItemState( (*itr) );
						clearCurrentItemVec();
						findCurrentItems( &m_rootMenu );
					}
					else  //直接进行消息响应
					{
						//发送处理事件的消息
						static int i = 1;
						if ( i >= 6 )
						{
							i = 1;
						}
						CorpLogo* pTrriger = vgLogo::LogoManager::getSingleton().getCorpLogoPtr();
						CString texFileName;
						texFileName.Format( "%s%d%s", "MenuLogo", i, ".tga" );
						pTrriger->setCurrentTexID( (string)texFileName );
						i++;
					}
					
				}
				break;
			}//end if
		} //end for
	}

	//-----------------------------------------------------------
	void MenuLogo::OnMouseMove(UINT nFlags, CPoint position)
	{
		int viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );

		float x = ( position.x - viewport[2] / 2.0 ) / ( viewport[2] / 2.0 );
		float y = ( viewport[3] / 2.0 - position.y ) / ( viewport[3] / 2.0 );

		MenuItemVecL1Itr itr = getCurrentItems()->begin();
		MenuItemVecL1Itr itr_end = getCurrentItems()->end();

		for ( ; itr != itr_end; itr++ )
		{
			float width = (*itr)->getLogoWidth();
			float height = (*itr)->getLogoHeight();

			vgKernel::Vec2* centerPos = (*itr)->getCenterPos();

			float xMin = centerPos->x - width / 2.0;
			float xMax = centerPos->x + width / 2.0;
			float yMin = centerPos->y - height / 2.0;
			float yMax = centerPos->y + height / 2.0;

			if ( x >= xMin && x <= xMax && y >= yMin && y <= yMax )
			{

				(*itr)->setCurrentTexID( true );
			}
			else
			{
				(*itr)->setCurrentTexID( false );
			}
		}
	}

	//-----------------------------------------------------------
	void MenuLogo::findCurrentItems( MenuItem* pMenuItem ) 
	{
		MenuItemVecL1* pRootMenuVec = pMenuItem->getSubItems();

		MenuItemVecL1Itr itr = pRootMenuVec->begin();
		MenuItemVecL1Itr itr_end = pRootMenuVec->end();

		for ( ; itr != itr_end; itr++ )
		{
			if ( (*itr)->getName() == "return" )  //返回上一级
			{
				if ( (*itr)->getRenderState() ) //如果返回上一级可用则加入数组
				{
					m_currentItemVec.push_back( (*itr) );
				}
				continue;
			}

			if ( (*itr)->getRenderState() ) //此节点可渲染
			{
				m_currentItemVec.push_back( (*itr) );
			}
			else  //此节点不可渲染
			{
				if ( (*itr)->hasSubItem() && (*itr)->getSubRenderState() ) 
				{
					// 有子节点且子节点可渲染
					findCurrentItems( (*itr) );
				}
			}//end esle
		}//end for
	}

	//-----------------------------------------------------------
	void MenuLogo::setItemState( MenuItem* pMenuItem, bool bUpLevel /* = false */ ) 
	{
		if ( bUpLevel )   //点击返回上一级时重置Items状态
		{
			MenuItem* pParent = pMenuItem->getParentPtr(); //获取当前节点的父节点
			MenuItem* pParentParent = pParent->getParentPtr();//获取父节点的父节点

			MenuItemVecL1* pParentParentVec = pParentParent->getSubItems();

			MenuItemVecL1Itr itr2 = pParentParentVec->begin();
			MenuItemVecL1Itr itr_end2 = pParentParentVec->end();

			for ( ; itr2 != itr_end2; itr2++ )
			{
				if ( pParentParent->getID() == 0 && (*itr2)->getName() == "return" )
				{
					(*itr2)->setRenderState( false );
				}
				else
				{
					(*itr2)->setRenderState( true );
					(*itr2)->setSubRenderState( false );
				}
			}
		}//end if
		else  //点击父节点将打开其子节点渲染状态，同时关闭父节点同一级的其它节点渲染状态
		{

			MenuItem* pParent = pMenuItem->getParentPtr();
			if ( pParent->getID() != 0 )
			{
				setItemState( pParent );
				
				setSubItemsState( pParent, pMenuItem ); //设置子节点渲染状态
			}
			else
			{
				setSubItemsState( pParent, pMenuItem );//设置子节点渲染状态
			}
		}//end else
	}

	//-----------------------------------------------------------
	void MenuLogo::setSubItemsState( MenuItem* pParentItem, MenuItem* pSubItem )
	{
		MenuItemVecL1* pMenuItemVec = pParentItem->getSubItems(); //获取子Items

		MenuItemVecL1Itr itr = pMenuItemVec->begin();
		MenuItemVecL1Itr itr_end = pMenuItemVec->end();

		for ( ; itr != itr_end; itr++ )  //循环处理
		{
			if ( (*itr)->getName() == "return" )
			{
				(*itr)->setRenderState( true );
				continue;
			}

			if ( (*itr)->getID() == pSubItem->getID() )  
			{
				(*itr)->setRenderState( false );  //关闭自身渲染
				(*itr)->setSubRenderState( true );//打开子节点渲染
			}
			else
			{
				(*itr)->setRenderState( false ); //关闭同级下其它节点自身渲染
				(*itr)->setSubRenderState( false );//关闭同级下其它节点子节点渲染
			}
		} //end for
	}

	//-----------------------------------------------------------
	vector<MenuItem*>* MenuLogo::getCurrentItems()
	{
		return &m_currentItemVec;
	}

	//-----------------------------------------------------------
	void MenuLogo::clearCurrentItemVec()
	{
		m_currentItemVec.clear();
	}

	//-----------------------------------------------------------
#if 0
	void MenuLogo::largenLogo( MenuItem* pMenuItem, vector<MenuItem*>* pMenuItemVec )
	{
		vector<MenuItem*>::iterator itr = pMenuItemVec->begin();
		vector<MenuItem*>::iterator itr_end = pMenuItemVec->end();

		for ( ; itr != itr_end; itr++ )
		{
			float width = (*itr)->getLogoWidth();
			float height = (*itr)->getLogoHeight();
			vgKernel::Vec2* centerPos = (*itr)->getCenterPos();
			vgKernel::Vec2 cornerPos = (*itr)->getCornerPos();

			if ( pMenuItem->getID() == (*itr)->getID() )
			{
				//ID唯一
				(*itr)->setLogoWidth( width * 1.5 );
				(*itr)->setLogoHeight( height * 1.5 );
				(*itr)->setCenterPos( cornerPos, false );
				continue;
			}

			if ( pMenuItem->getCenterPos()->x < (*itr)->getCenterPos()->x )
			{
				//在变大图标的右面
				continue;
			}
			else
			{
				float xVary = (*itr)->getCenterPos()->x - pMenuItem->getLogoWidth() + pMenuItem->getOriginalWidth();
				(*itr)->getCenterPos()->x = xVary;
				//在变大图标的左面
				//(*itr)->setCenterPos( *(*itr)->getCenterPos(),true );
			}
		}
	}

	//-----------------------------------------------------------
	void MenuLogo::reInitAllItem( MenuItem* pMenuItem )
	{
		MenuItemVecL1* pVec = pMenuItem->getSubItems();

		MenuItemVecL1Itr itr = pVec->begin();
		MenuItemVecL1Itr itr_end = pVec->end();
		
		for ( ; itr != itr_end; itr++ )
		{
			if ( (*itr)->hasSubItem() )
			{
				reInitAllItem( (*itr) );

				(*itr)->setLogoWidth( (*itr)->getOriginalWidth() );
				(*itr)->setLogoHeight( (*itr)->getOriginalHeight() );
				(*itr)->setCenterPos( *(*itr)->getOriginalCenterPos(), true );
			}
			else
			{
				(*itr)->setLogoWidth( (*itr)->getOriginalWidth() );
				(*itr)->setLogoHeight( (*itr)->getOriginalHeight() );
				(*itr)->setCenterPos( *(*itr)->getOriginalCenterPos(), true );
			}
		}

	}
#endif

	//-----------------------------------------------------------

}//namespace vgLogo