


#ifndef __VGTHUGEPROCESSPROCESSOR_H__
#define __VGTHUGEPROCESSPROCESSOR_H__

#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtHugeProcessGlobal.h>
#include <vgTerritory/vgtHugeProcessSmallBlock.h>
#include <vgTerritory/vgtHugeProcessFileBlock.h>
#include <vgTerritory/vgTerrainHugeImageUtil.h>
#include <vgThreads/ThreadPool.h>
#include <vgThreads/ThreadRequest.h>
#include <vgThreads/CriticalSection.h>
#include <vgThreads/AutoEvent.h>
#include <vgThreads/ScopedLock.h>
#include <vgThreads/ManualEvent.h>
#include <vgTerritory/vgtHugeProcessCounter.h>
#include <vgKernel/vgkProcessObserver.h>
#include <vgTerritory/vgtDefinition.h>
	
namespace vgTerritory {


#define VGT_MAX_THREADS  0
#define VGT_MAX_QUEUE		51200

	namespace HugeProcess
	{

		using namespace vgThreads;

		class FileBlockRequest;


		class Processor : public vgKernel::ProcessNotifier
		{
		public:
			Processor();
			~Processor();
 
		public:

			void clear();
			

			// 注意,第一步
			bool initFileBlocks( const fileBlockVectorPtr inputfileblocks );

			// 注意,第二步!
			bool initParams( uchar* filledColor , 
				const String& temppath , const String& prefix , 
				const String& ext ,const String&temp_ext , 
				const long& smallblockwidth , 
				const long& widthandheightaddon , const bool& removetempfiles ,
				std::vector<ProcessObserver*> observers , 
				const bool& remove_input_files );
		
			// 注意,第三步!
			void process();

			Global* getGlobalPtr()
			{
				assert( _globalData != NULL );
				return _globalData;
			}

			HugeImageBlockInfoVectorPtr getHugeImageBlockInfoVectorPtr();


		private:


			

			ThreadPool* _threadPool;

			ManualEvent _event;
			Counter* _counter;

			ManualEvent _smallBlockEvent;
			
			CriticalSection _criticalSect;

			std::vector<SmallBlock*> _smallBlocks;
			std::vector<FileBlock*> _fileBlocks;

			std::vector<CutBlock*> _cutBlocks;
		
			Global* _globalData;

			StringVectorPtr _outputNames;

		};


		class FileBlockRequest : public ThreadRequest
		{
		public:
			FileBlockRequest( FileBlock* fileblock , std::vector<CutBlock*>& cutblocks,
				CriticalSection* cutblockcritical , Counter* counter , 
				ManualEvent* cut_event , vgKernel::ProcessNotifier* notifier );
			virtual ~FileBlockRequest();

			virtual void operator()(int threadId);
		
		private:
		
			vgKernel::ProcessNotifier* _notifier;
			Counter* _counter;
			ManualEvent* _event;

			std::vector<CutBlock*>& _cutBlocks;
			FileBlock* _fileBlock;
			CriticalSection* _cutBlockCriticalSect;

		};

		class SmallBlockRequest : public ThreadRequest
		{
		public:
			SmallBlockRequest( SmallBlock* sblock , 
				CriticalSection* cutblockcritical , Counter* counter , 
				ManualEvent* cut_event , StringVector* list ,
				vgKernel::ProcessNotifier* notifier );
			virtual ~SmallBlockRequest();

			virtual void operator()(int threadId);

		private:

			vgKernel::ProcessNotifier* _notifier;
			Counter* _counter;
			ManualEvent* _event;

			SmallBlock* _block;
			CriticalSection* _criticalSect;
			
			StringVector* _list;

		};



	}
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTHUGEPROCESSPROCESSOR_H__