


#ifndef __VGMOVINGMANAGER_H__
#define __VGMOVINGMANAGER_H__



#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSingleton.h>
#include <vgMod/vgobjframenode.h>
#include <vgMs3d/ms3d.h>
#include<vgKernel/vgkRendererHolder.h>
#include <vgMod/vgGisRoadMatch.h>

#include <vgMod/vgObjNodeBaked.h>
#include <vgEffect/vgClimate.h>

#include <vgGismatchDrawer.h>

#include <vgEffect/vgDustsun.h>

namespace  vgCore {
	
	using namespace vgMod;
	/**
		@action		creation
		@date 		2009/03/07  11:29	
		@author  	lss
	
		@brief 	
	
		@see    
		*/
	enum	EMovingModualMarkExt
	{
		EXT_NONE,

		EXT_COUNT
	};

	class MovingModualHeader
	{
	public:
		String			strModualDescription;	// Part 1: 模块标识字符串
		unsigned int	uiMark;					// Part 2: 模块版本标记

	public:
		MovingModualHeader();
		~MovingModualHeader();

		bool write(CFile* pfile);
		bool write(vgKernel::StreamWriterPtr	pfile);
		bool read(CFile* pfile);
		bool read(vgKernel::StreamReaderPtr	pfile);
	};

	/**
	@date 	2008/05/21  20:23	
	@author  hero

	@brief 	

	@see    
	*/
	class vgClimate;

	class  VGDEP_EXPORT MovingManager  : public ::Singleton<MovingManager>
		,public vgKernel::RendererHolder//chunyongma2008.9.8
	{
	public:
		MovingManager();
		virtual ~MovingManager();

		static MovingManager* getSingletonPtr(void)
		{
			return ms_pSingleton;
		}
		static MovingManager& getSingleton(void)
		{  
			assert( ms_pSingleton );  return ( *ms_pSingleton );  
		}

		bool initialise()
		{
			return true;
		}

		void reset();


	public://file series
		void writeToFile( CFile* pCfile , const String& attachDataPath);
		void writeToFile( const String& save_absolute_path , const String& attachDataPath);
		bool readFromFile( CFile* pCfile , const String& attachDataPath);
		bool readFromFile( const String& save_absolute_path, const String& attachDataPath);

		void writeMs3dToFile( CFile* pCfile , const String& attachDataPath);
		void writeMs3dToFile( const String& save_absolute_path , const String& attachDataPath);
		bool readMs3dFromFile( CFile* pCfile , const String& attachDataPath);
		bool readMs3dFromFile( const String& save_absolute_path , const String& attachDataPath);
		void writeGismatchToFile( CFile* pCfile , const String& attachDataPath);
		bool readGismatchFromFile( CFile* pCfile , const String& attachDataPath);
		
		bool copyMs3dFile( const String& attachDataPath);
		bool copyGisMatchFile( const String& attachDataPath);

		bool writeModualHeader( CFile* pCfile  );

		bool loadVgiForMs3d(String filePath);
		bool copyVgiForMs3d( String attachDataPath, String filePath);

#if 1
		void writeKeyframeToFile( const String& save_absolute_path );
		bool readKeyframeFromFile( const String& save_absolute_path );

		void writeKeyframeToFile( CFile* pCfile );
		bool readKeyframeFromFile( CFile* pCfile );
		ObjFrameNode*  MovingManager::generateKeyframeNodeFromFile( CFile* pCfile );

		bool addKeyFrameNode( ObjFrameNode *node );
		bool addKeyFrameNodePtr( ObjFrameNodePtr pnode );
		void	startAllKeyFramePlaying();
		ObjFrameNode*	getKeyFrameByName( const String& strRendererName);
#endif
		
		//void AddNewGisMatchName(vggismatchNodePtr nodeptr);
		void addGisMatchNode(vgMod::GisRoadMatch *node);



		bool addSkelecton(String szFilename);

		void addMs3dNode( vgMs3d::CMs3d *node);

		void renderMovingNode();
		
		virtual bool onDeleteRenderer( vgKernel::Renderer *render );//chunyongma2008.9.8


		vgMs3d::CMs3d*	getMs3dnodeByName( const String& strRendererName);

	
		vgMod::vgClimate*	getClimate()	{ return m_pClimate;}
	private:


		vector<ObjFrameNodePtr> ObjFrames;

		typedef vgCore::SharedPtr<vgMs3d::CMs3d> vgMs3dNodePtr;

		vector<vgMs3dNodePtr> Ms3dvet;

		typedef vgCore::SharedPtr<vgMod::GisRoadMatch> vggismatchNodePtr;

		vector<vggismatchNodePtr> GisMatchVet;
		//----------------------------------------------------------------------------[9/23/2008 YX]

		vgMod::vgClimate* m_pClimate;


		GisMatchDrawer* _GisMatchdrawer;

		Dustsun *p_dustsun;


	public:
		bool importImageFileOnly(String VgiPathName);
	
		void Initdustsun(string modfile = "", string origtex = "", string dusttex = "" , string lastsuntex = ""  );
	

		void Dustsuneffect();
	};




}// end of namespace 

#endif // end of __VGSOUNDMANAGER_H__

