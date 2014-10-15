
#include <vgStableHeaders.h>
#include <vgChannel/vgcChannelManager.h>
#include <vgKernel/vgkSystemUtility.h>

#include <vgCam/vgcaCamManager.h>
#include <vgKernel/vgkInputCodeDef.h>
#include <vgKernel/vgkSingletonLifeTimeDefine.h>
#include <vgKernel/vgkRenderCommandManager.h>

#include <vgChannel/vgchChannelRenderCommand.h>

#include <vgKernel/vgkPropertyManager.h>
#include <vgKernel/vgkVec2.h>
//#pragma comment(lib,"vgCam.lib")

namespace vgChannel//vgChannelManager命名空间
{
	static const long OVER_TIME_THREAHOLD = 300 ;

	static DWORD WINAPI clientReceiveThread(LPVOID lpParameter);
	static DWORD WINAPI serverReceiveThread(LPVOID lpParameter);

	static void reriveFromServerSocket(long dataLength);
	static void reriveFromClientSocket(long dataLength);

	static CSemaphore* gs_pClientRsp = new CSemaphore(1, 1);
	static CSemaphore* gs_pServerMsg = new CSemaphore(1, 1);

	static int		gs_serverRecvPort = 8692;
	static SOCKET	gs_serverSendSocket;
	static SOCKET	gs_serverReceiveSocket;

	static DWORD	gs_serverThreadID;
	static HANDLE	gs_serverReceiveHandle;

	static int		gs_clientRecvPort = 8610;
	static SOCKET	gs_clientSendSocket;
	static SOCKET	gs_clientReceiveSocket;

	static DWORD	gs_clientThreadID;
	static HANDLE	gs_clientReceiveHandle;

	static ViewPackage gs_viewerPackage;

	static fstream  gs_logFile;

	static bool		gs_b3ChannelOpened = false;
	static int		gs_channelNum =-2;	
	static int		MAX_CLIENT_NUM = 0;

	static bool left = false;
	static bool right = false;

	static bool gs_logEnable = TRUE;

	static DWORD dwIPServ;//存储服务器端的IP地址
	static 	CString strClientInfoPath;//存储服务器端多通道配置文件的路径

	LARGE_INTEGER litmp;  
	LONGLONG QPart1,QPart2, QParttemp; 
	double dfMinus, dfFreq, dfTim;  

	double getmillsecond()
	{
		QueryPerformanceCounter(&litmp); 
		QPart2 = litmp.QuadPart;//获得中止值 
		dfMinus = (double)(QPart2-QPart1); 
		dfTim = dfMinus / dfFreq;// 获得对应的时间值，单位为秒 

		return dfTim * 1000;
	}

	ChannelManager::ChannelManager() 
		: Singleton<ChannelManager>( VGK_SINGLETON_LEFE_CHANNEL )
		, m_nurbsAdjustImpl()
	{
		WSADATA wsd;

		int ret = WSAStartup(0x0202,&wsd);
		if(ret!=0)
		{
			WSACleanup();
		}

		QueryPerformanceFrequency(&litmp); 
		dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率 
		QueryPerformanceCounter(&litmp); 
		QPart1 = litmp.QuadPart;// 获得初始值

		for (int i=0; i<MAX_OF_CLIENT; i++)
		{
			m_clientInfo[i].clientIsInCome = false;
			m_clientInfo[i].controlParam.channelNum = -2;
			m_clientInfo[i].controlParam.hOffset = 0;
			m_clientInfo[i].controlParam.vOffset = 0;
			m_clientInfo[i].controlParam.leftEdge = 0;
			m_clientInfo[i].controlParam.rightEdge = 0;
			m_clientInfo[i].controlParam.cameraOffset = 256;
			m_clientInfo[i].controlParam.eyePosOffset = 0;
		}

		m_cameraOffset = 256;
		m_hOffset = 0;
		m_vOffset = 0;
		Lflag = false;

		char hostName[255];   
		PHOSTENT hostinfo;

		if(gethostname(hostName, sizeof(hostName))   ==   0)   
		{   
			if((hostinfo = gethostbyname(hostName)) != NULL)   
			{   
				m_broadCastAddress = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);   
			}
			m_broadCastAddress[m_broadCastAddress.length()-1] = '5';
			m_broadCastAddress[m_broadCastAddress.length()-2] = '5';
			m_broadCastAddress[m_broadCastAddress.length()-3] = '2';


		} 
		// 响应nurbs微调模式下的输入事件
		statusFlag = VG_INPUTMODE_NURBSCORRECT;
		// 向InputSystem注册，InputSystem会转发相应消息给CamManager
		vgKernel::InputSystem::getSingleton().registerHandle(this);

		m_blendAndAdjust = false;
		m_eyeOffset = 0;

		m_pChannelRenderBegin = new ChannelRenderBegin;
		m_pClientRenderBegin = new ClientRenderBegin;
		m_pServerRenderBegin = new ServerRenderBegin;
		m_pChannelRenderEnd = new ChannelRenderEnd;
		m_pBlendAndAdjust = new BlendAndAdjust;

		vgKernel::RenderCommandFacade::AddCommand(m_pChannelRenderBegin);
		vgKernel::RenderCommandFacade::AddCommand(m_pClientRenderBegin);
		vgKernel::RenderCommandFacade::AddCommand(m_pServerRenderBegin);
		vgKernel::RenderCommandFacade::AddCommand(m_pChannelRenderEnd);
		vgKernel::RenderCommandFacade::AddCommand(m_pBlendAndAdjust);
		// 向属性管理器注册，获取对屏幕尺寸的监控
		if (! vgKernel::PropertyManager::getSingleton().registerPropertyObserver("PROP_SCREEN_SIZE", this))
		{
			vgKernel::Property<vgKernel::Vec2> *screenSizeProp
				= new vgKernel::Property<vgKernel::Vec2>("PROP_SCREEN_SIZE");

			screenSizeProp->setValue(vgKernel::Vec2(1,1));
			vgKernel::PropertyManager::getSingleton().addProperty(screenSizeProp);
			vgKernel::PropertyManager::getSingleton().registerPropertyObserver("PROP_SCREEN_SIZE", this);	
		}
	}

	ChannelManager::~ChannelManager()
	{
		vgKernel::RenderCommandFacade::RemoveCommand(m_pChannelRenderBegin);
		vgKernel::RenderCommandFacade::RemoveCommand(m_pClientRenderBegin);
		vgKernel::RenderCommandFacade::RemoveCommand(m_pServerRenderBegin);
		vgKernel::RenderCommandFacade::RemoveCommand(m_pChannelRenderEnd);
		vgKernel::RenderCommandFacade::RemoveCommand(m_pBlendAndAdjust);

		m_pChannelRenderEnd = NULL;
		m_pChannelRenderBegin = NULL;
		m_pClientRenderBegin = NULL;
		m_pServerRenderBegin = NULL;
		m_pBlendAndAdjust = NULL;

		TRACE("Destory Channel Render Command. \n");

		gs_logFile.close();
		cancelChannel();
		WSACleanup();
	}

	bool ChannelManager::initialise()//
	{
		return true;
	}
	
	void ChannelManager::onEvent(unsigned int eventId, void *param)
	{
		if (eventId == vgKernel::UnTypedProperty::PROPERTY_ON_CHANGE)
		{
			vgKernel::Vec2 *pSize = (vgKernel::Vec2*)param;
			assert(pSize != NULL);

			setScreenSize(pSize->x, pSize->y);
		}
	}

	bool ChannelManager::shutdown()
	{
		return true;
	}

	bool ChannelManager::startChannel(int channelNum)
	{
		if (gs_b3ChannelOpened)
		{
			return false;
		}

		//gs_b3ChannelOpened = true;
		gs_channelNum = channelNum;
		gs_b3ChannelOpened = true;
		vgCam::CamManager::getSingleton().channel3Enable(true);

		if (gs_channelNum == 0)
		{
			gs_logFile.open( "logServer.txt", std::ios_base::out | std::ios_base::trunc );

			// if(gs_serverReceiveSocket == INVALID_SOCKET || gs_serverSendSocket == INVALID_SOCKET)
			{
				if(! createServerSocket(gs_serverRecvPort))
				{
					AfxMessageBox("端口创建错误.");
					return false;
				}
			}

			gs_serverReceiveHandle = 
				CreateThread(NULL, 0, serverReceiveThread, this, 0, &gs_serverThreadID);

			SetThreadPriority( gs_serverReceiveHandle, THREAD_PRIORITY_ABOVE_NORMAL);

			if(gs_serverReceiveHandle == NULL)
			{
				return false;
			}
		}
		else
		{
			gs_channelNum = -2;

			gs_logFile.open( "logClient.txt", std::ios_base::out | std::ios_base::trunc );

			// if (gs_clientReceiveSocket == INVALID_SOCKET || gs_clientSendSocket == INVALID_SOCKET)
			{
				if (! createClientSocket(gs_clientRecvPort))
				{
					AfxMessageBox("端口创建错误.");
					return false;
				}
			}

			gs_clientReceiveHandle = CreateThread(NULL, 0, clientReceiveThread, this, 0, &gs_clientThreadID);

			SetThreadPriority( gs_clientReceiveHandle, THREAD_PRIORITY_ABOVE_NORMAL);
		}
		return true;
	}

	bool ChannelManager::cancelChannel()
	{
		if (! gs_b3ChannelOpened)
		{
			return false;
		}

		if (gs_channelNum == 0)
		{
			closesocket(gs_serverSendSocket);
			closesocket(gs_serverReceiveSocket);
		}
		else
		{
			closesocket(gs_clientReceiveSocket);
			closesocket(gs_clientSendSocket);
		}
		
		gs_b3ChannelOpened = false;
		gs_channelNum = 0;
		
		vgCam::CamManager::getSingleton().channel3Enable(false);

		gs_b3ChannelOpened = false;
		gs_logFile.close();

		if(gs_serverReceiveHandle != NULL)
		{
			WaitForSingleObject(gs_serverReceiveHandle,INFINITE);
			gs_serverReceiveHandle = NULL;
			gs_serverThreadID = 0;
		}

		if (gs_clientReceiveHandle != NULL)
		{
			WaitForSingleObject(gs_clientReceiveHandle, INFINITE);
			gs_clientReceiveHandle = NULL;
			gs_clientReceiveHandle = 0;
		}

		gs_pServerMsg->Unlock();
		gs_pClientRsp->Unlock();

		return true;
	}

	bool ChannelManager::serverRenderBegin()
	{
		ViewPackage packet;

		if (! gs_b3ChannelOpened)
		{
			return true;
		}

		if (gs_channelNum == 0)
		{
			packet.x = vgCam::CamManager::getSingleton().getCurrentPosition().x;
			packet.y = vgCam::CamManager::getSingleton().getCurrentPosition().y;
			packet.z = vgCam::CamManager::getSingleton().getCurrentPosition().z;
			TRACE("send %f %f %f \n", packet.x, packet.y, packet.z);

			packet.headDegree = vgCam::CamManager::getSingleton().getHeadingDegrees();
			packet.pitchDegree = vgCam::CamManager::getSingleton().getPitchDegrees();
			
			// VGK_SHOW( "Lock Server \n");
			if (! gs_pClientRsp->Lock(OVER_TIME_THREAHOLD))
			{
				// gs_logFile << "server time out."
				// VGK_SHOW("Server Time out. \n");

				return false;
			}
			if ( sendToClient(packet) == 0)
				return true;
			else
				return false;
		}

		return true;
	}

	bool ChannelManager::renderBegin()
	{
		if (m_blendAndAdjust)
		{
			m_blendAdjustImpl.renderBegin();
		}

		return true;
	}

	bool ChannelManager::clientRenderBegin()
	{
		if (! gs_b3ChannelOpened)
		{
			return true;
		}

		if (gs_channelNum == -1 || gs_channelNum == 1)
		{
			// VGK_SHOW("Lock Client \n");

			if (! gs_pServerMsg->Lock(OVER_TIME_THREAHOLD))
			{
				// VGK_SHOW("Time out. \n");
				return false;
			}
			else
				return true;
		}
		else if (gs_channelNum == -11 || gs_channelNum == 11 || gs_channelNum == 10)
		{
			if (! gs_pServerMsg->Lock(OVER_TIME_THREAHOLD))
			{
				// VGK_SHOW("Time out. \n");
				return false;
			}
			else
				return true;
		}

		return true;
	}

	bool ChannelManager::renderEnd()
	{
		if (! gs_b3ChannelOpened)
		{
			return true;
		}

		if (gs_channelNum == 0)
		{
			return true;
		}
		else
		{
			if (sendToServer() == 0)
				return true;
			else 
				false;
		}

		return true;
	}

	bool ChannelManager::getChannelEnable()
	{
		return gs_b3ChannelOpened;
	}

	int ChannelManager::getChannelNum()
	{
		return gs_channelNum;
	}

	bool ChannelManager::createServerSocket(int serverRecvPort)
	{
		int ret;

		gs_serverRecvPort = serverRecvPort;

		// 创建Server接收Socket
		gs_serverReceiveSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP); 

		if(gs_serverReceiveSocket == INVALID_SOCKET)
		{
			return false;
		}

		SOCKADDR_IN addr;
		ZeroMemory(&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		// 绑定本机所有IP地址
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons(gs_serverRecvPort);
		// 绑定Server发送使用的端口和地址
		ret = bind(gs_serverReceiveSocket, (struct sockaddr *)&addr, sizeof(addr));

		if(ret != 0)
		{
			return false;
		}

		// 创建Server发送Socket
		gs_serverSendSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_IP); 
		if(gs_serverSendSocket == INVALID_SOCKET)
		{
			return 0;
		}

		SOCKADDR_IN addrSnd;
		//绑定发送
		ZeroMemory(&addrSnd,sizeof(addrSnd));
		addrSnd.sin_family = AF_INET;
		addrSnd.sin_addr.s_addr = INADDR_ANY;

		ret = bind(gs_serverSendSocket, (struct sockaddr *)&addrSnd, sizeof(addrSnd));

		if(ret != 0)
		{
			return 0;
		}

		return true;
	}

	void ChannelManager::setServerIP(DWORD dwIP)
	{
		dwIPServ = dwIP;
	}

	bool ChannelManager::createClientSocket(int clientRecvPort)
	{
		int ret;

		gs_clientRecvPort = clientRecvPort;

		// 创建Client接收Socket
		gs_clientReceiveSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP); 

		if(gs_clientReceiveSocket == INVALID_SOCKET)
		{
			return false;
		}

		SOCKADDR_IN addr;
		ZeroMemory(&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		// 绑定本机所有IP地址
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons(gs_clientRecvPort);
		// 绑定Server发送使用的端口和地址
		ret = bind(gs_clientReceiveSocket, (struct sockaddr *)&addr, sizeof(addr));

		if(ret != 0)
		{
			return false;
		}

		// 创建Client发送Socket
		gs_clientSendSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_IP); 
		if(gs_clientSendSocket == INVALID_SOCKET)
		{
			return 0;
		}

		SOCKADDR_IN addrSnd;
		//绑定发送
		ZeroMemory(&addrSnd,sizeof(addrSnd));
		addrSnd.sin_family = AF_INET;
		addrSnd.sin_addr.s_addr = INADDR_ANY;

		ret = bind(gs_clientSendSocket, (struct sockaddr *)&addrSnd, sizeof(addrSnd));

		if(ret != 0)
		{
			return 0;
		}

		return true;
	}

	int ChannelManager::sendToServer()
	{
		int ret;
		SOCKADDR_IN serverAddr;
		if(gs_clientSendSocket == INVALID_SOCKET)
		{
			return -1;
		}

		ZeroMemory(&serverAddr, sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		//serverAddr.sin_addr.s_addr = inet_addr(m_broadCastAddress.c_str());
		serverAddr.sin_addr.S_un.S_addr = htonl(dwIPServ);

		// serverAddr.sin_addr.s_addr = inet_addr("222.195.148.255");
		// serverAddr.sin_addr.S_un.S_addr=htonl(m_broadCastAddress);
		serverAddr.sin_port = htons(gs_serverRecvPort);
		// serverAddr.sin_port = htons(gs_clientRecvPort);

		char rsp;
		if (gs_channelNum == -1)
		{
			rsp = 'l';
		}
		else if (gs_channelNum == 1)
		{
			rsp = 'r';
		}
		else if (gs_channelNum == -11)//六通道的左客户端
		{
			rsp = 'z';
		}
		else if (gs_channelNum == 11)//六通道的右客户端
		{
			rsp = 'y';
		}
		else if (gs_channelNum == 10)//六通道的中间客户端
		{
			rsp = 'm';
		}
		else
		{
			rsp = 'U';
			// assert(0);
		}

		ret = sendto(gs_clientSendSocket, (char *)&rsp,sizeof(rsp), 0, (sockaddr *)&serverAddr,sizeof(serverAddr));	
		// VGK_SHOW("Send to server \n") ;
		if(ret == SOCKET_ERROR)
		{
			return -2;
		}

		// VGK_SHOW("Send to server \n");
		return 0;
	}

	int ChannelManager::sendToClient(ViewPackage& vp)
	{
		NetPackage sendPackage;
		int numOfClient = getInComeClientNum();

		sendPackage.type = 'W';

		int ret = 0;
		SOCKADDR_IN clientAddr;
		if(gs_serverSendSocket == INVALID_SOCKET)
		{
			return -1;
		}

		ZeroMemory(&clientAddr, sizeof(clientAddr));
		clientAddr.sin_family = AF_INET;
		clientAddr.sin_addr.s_addr = inet_addr(m_broadCastAddress.c_str());

		// clientAddr.sin_addr.s_addr = inet_addr("222.195.148.255");
		// clientAddr.sin_addr.S_un.S_addr=htonl(m_broadCastAddress);
		clientAddr.sin_port = htons(gs_clientRecvPort);
		// clientAddr.sin_port = htons(gs_serverRecvPort);

		double time1 = getmillsecond();

		if (gs_logEnable)
		{
			gs_logFile << time1 << " send: "<< vp.x << " " << vp.y << " " << vp.z << "\n";
			TRACE("%f %f %f \n", vp.x, vp.y, vp.z);
		}
		sendPackage.Data.view = vp;

		// memcpy_s(sendBuffer+1, sizeof(sendBuffer)-1, &vp, sizeof(vp));
		for (int i=0; i<numOfClient; i++)
		{
			clientAddr = m_clientInfo[i].clientSocketAddr;
			ret = sendto(gs_serverSendSocket, (char*)(&sendPackage), sizeof(sendPackage), 0,(sockaddr *)&clientAddr,sizeof(clientAddr));	
		}
		// ret = sendto(gs_serverSendSocket, (char *)&vp, sizeof(vp), 0,(sockaddr *)&clientAddr,sizeof(clientAddr));	
		// ret = sendto(gs_serverSendSocket, (char *)&rsp,sizeof(rsp), 0,(sockaddr *)&clientAddr,sizeof(clientAddr));	
		// VGK_SHOW("Send to Client \n") ;

		if(ret == SOCKET_ERROR)
		{
			VGK_SHOW("Server send error \n");
			return -2;
		}

		// VGK_SHOW("Send to client. \n");

		return 0;
	}

	ViewPackage ChannelManager::getCurrentViewPackage()
	{
		return gs_viewerPackage;
	}

	DWORD WINAPI clientReceiveThread(LPVOID lpParameter)
	{
		int ret;
		unsigned long lLength;

		while( gs_b3ChannelOpened )
		{
			ret = ioctlsocket(gs_clientReceiveSocket, FIONREAD, &lLength);
			if(ret != 0)
			{
				break;
			}
			else
			{
				if(lLength>0)
				{
					reriveFromClientSocket(lLength);
				}
			}

			Sleep(10);
		}


		return 0;
	}

	void reriveFromClientSocket(long dataLength)
	{
		//length 是socket列队中的第一个报文长度

		char *pbuf;
		int addr_len, iRecLen;;
		struct sockaddr_in addr;

		pbuf = new char[dataLength + 1];
		memset(pbuf, 0, dataLength + 1);

		addr_len = sizeof(addr);

		iRecLen = recvfrom(gs_clientReceiveSocket, pbuf, dataLength, 0,(struct sockaddr *)&addr, &addr_len);

		if( iRecLen<=0 )
		{
			gs_logFile << "Receive error. \n";
		}
		else
		{
			NetPackage *pPackage = (NetPackage*)(pbuf);

			// 传递的是同步信息
			if (pPackage->type == 'W')
			{
				ViewPackage buf = pPackage->Data.view;
				if (gs_logEnable)
				{
					gs_logFile << "Receive: "<< buf.x << " " << buf.y << " " << buf.z << "\n";
				}

				// 				if (buf == NULL)
				// 				{
				// 					gs_logFile << "Receive error. \n";
				// 
				// 					return ;
				// 				}

				gs_viewerPackage = buf;
				float offset = vgChannel::ChannelManager::getSingleton().getEyePosOffset();
				vgKernel::Vec3 m_CurrentDirecVec = vgCam::CamManager::getSingleton().getCurrentDirection();

				gs_viewerPackage.x -= m_CurrentDirecVec.z  * offset;
				gs_viewerPackage.z += m_CurrentDirecVec.x  * offset;
				
				vgCam::CamManager::getSingleton().setCurrentPosition(vgKernel::Vec3(gs_viewerPackage.x, gs_viewerPackage.y, gs_viewerPackage.z));
				vgCam::CamManager::getSingleton().setHeadingDegrees(gs_viewerPackage.headDegree);
				vgCam::CamManager::getSingleton().setPitchDegrees(gs_viewerPackage.pitchDegree);
				gs_pServerMsg->Unlock();
			}
			// 传递的是控制信息
			else if (pPackage->type == 'C')
			{
				ControlPackage buf = pPackage->Data.control;
				if (gs_logEnable)
				{
					gs_logFile << "Receive Control: "<< buf.channelNum << " " << buf.cameraOffset << " " << buf.leftEdge << " " << buf.rightEdge << " " << buf.hOffset << " " << buf.vOffset <<"\n";
				}
				VGK_SHOW("Receive control mesg. \n");
				ChannelManager::getSingleton().updateControlInfo(buf);
			}


			// VGK_SHOW("Receive from server. \n");
		}
		delete [] pbuf;
		pbuf = NULL;
	}

	DWORD WINAPI serverReceiveThread(LPVOID lpParameter)
	{
		int ret;
		unsigned long lLength;

		while( gs_b3ChannelOpened )
		{
			ret = ioctlsocket(gs_serverReceiveSocket, FIONREAD, &lLength);
			if(ret != 0)
			{
				break;
			}
			else
			{
				if(lLength>0)
				{
					reriveFromServerSocket(lLength);
				}
			}

			Sleep(10);
		}

		return 0;
	}

	void reriveFromServerSocket(long dataLength)
	{
		static int receiveCnt = 0;

		char *pbuf;
		int addr_len, iRecLen;;
		struct sockaddr_in addr;

		pbuf = new char[dataLength + 1];
		memset(pbuf, 0, dataLength + 1);

		addr_len = sizeof(addr);

		int receiveDataCnt = 0;
		while (receiveDataCnt < dataLength)
		{
			iRecLen = recvfrom(gs_serverReceiveSocket, pbuf, dataLength, 0,(struct sockaddr *)&addr, &addr_len);
			receiveDataCnt += iRecLen;

			if( iRecLen <= 0 )
			{
				gs_logFile << "Receive Failed! "<< iRecLen << " " << dataLength << " " << pbuf[0] << " " << pbuf[1] << "\n";
				break;
			}
			else
			{
				if (pbuf[0] == 'U')
				{
					// VGK_SHOW("Process client. \n");
					ChannelManager::getSingleton().processUnkownClient(addr);
				}
				else 
				{

					if (pbuf[0] == 'l')
					{
						if (gs_logEnable)
						{
							double time1 = getmillsecond();

							gs_logFile << "receive l " << time1 << "\n";
						}

						receiveCnt ++ ;
					}
					else if (pbuf[0] == 'r')
					{
						if (gs_logEnable)
						{
							double time1 = getmillsecond();

							gs_logFile << "receive r " << time1 << "\n";
						}

						receiveCnt ++ ;
					}
					else if (pbuf[0] == 'z')//六通道的左客户端
					{
						if (gs_logEnable)
						{
							double time1 = getmillsecond();

							gs_logFile << "receive r " << time1 << "\n";
						}

						receiveCnt ++ ;
					}
					else if (pbuf[0] == 'y')//六通道的右客户端
					{
						if (gs_logEnable)
						{
							double time1 = getmillsecond();

							gs_logFile << "receive r " << time1 << "\n";
						}

						receiveCnt ++ ;
					}
					else if (pbuf[0] == 'm')//六通道的中间客户端
					{
						if (gs_logEnable)
						{
							double time1 = getmillsecond();

							gs_logFile << "receive r " << time1 << "\n";
						}

						receiveCnt ++ ;
					}


					if (receiveCnt >= MAX_CLIENT_NUM)
					{
						receiveCnt = 0;

						double time1 = getmillsecond();

						if (gs_logEnable)
						{
							gs_logFile << "Unlock "<< time1 << "\n";
						}

						gs_pClientRsp->Unlock();
					}
				}// end of else

			}
		}


		delete [] pbuf;
		pbuf = NULL;
	}

	int ChannelManager::getInComeClientNum()
	{
		int cnt = 0;
		for (int i=0; i<MAX_OF_CLIENT; i++)
		{
			if (m_clientInfo[i].clientIsInCome != false)
			{
				cnt ++;
			}
		}
		MAX_CLIENT_NUM = cnt;
		return cnt;
	}

	SOCKADDR_IN ChannelManager::getClientSockAddr(int index)
	{
		if (m_clientInfo[index].clientIsInCome)
		{
			return m_clientInfo[index].clientSocketAddr;
		}
		else
		{
			assert(0);
		}

		return SOCKADDR_IN();
	}

	bool ChannelManager::processUnkownClient(SOCKADDR_IN inAddr)
	{
		int numOfClient = getInComeClientNum();
		inAddr.sin_port = htons(gs_clientRecvPort);
		for (int i=0; i<numOfClient; i++)
		{
			if (inAddr.sin_addr.S_un.S_addr == m_clientInfo[i].clientSocketAddr.sin_addr.S_un.S_addr)
			{
				return false;
			}
		}

		m_clientInfo[numOfClient].clientSocketAddr = inAddr;
		m_clientInfo[numOfClient].clientIsInCome = true;
		numOfClient = getInComeClientNum();
		return true;
	}

	int ChannelManager::sendControlMsgToClient(SOCKADDR_IN addr, ControlPackage controlPackage)
	{
		char sendBuffer[256];

		sendBuffer[0] = 'C';

		memcpy_s(sendBuffer+1, sizeof(sendBuffer)-1, &controlPackage, sizeof(controlPackage));

		int ret = sendto(gs_serverSendSocket, sendBuffer, sizeof(controlPackage)+1, 0,(sockaddr *)&addr, sizeof(addr));

		return ret;
	}

	ControlPackage* ChannelManager::getControlInfoByIp(string ipAddress)
	{
		int cnt = getInComeClientNum();
		for (int i=0; i<cnt; i++)
		{
			string ipStr = inet_ntoa(m_clientInfo[i].clientSocketAddr.sin_addr);
			if (ipStr == ipAddress)
			{
				return &(m_clientInfo[i].controlParam);
			}
		}

		return NULL;
	}

	int ChannelManager::setControlInfoByIp(string ipAddress, ControlPackage controlInfo)
	{
		NetPackage sendPackage;
		sendPackage.type = 'C';

		int cnt = getInComeClientNum();
		for (int i=0; i<cnt; i++)
		{
			string ipStr = inet_ntoa(m_clientInfo[i].clientSocketAddr.sin_addr);
			if (ipStr == ipAddress)
			{
				m_clientInfo[i].controlParam = controlInfo;

				// memcpy_s(pbuffer+1, sizeof(pbuffer)-1, &controlInfo, sizeof(controlInfo));
				sendPackage.Data.control = controlInfo;
				VGK_SHOW("Send control info to client. \n");
				gs_logFile <<"Control : " << controlInfo.cameraOffset <<" "<< controlInfo.channelNum << "\n ";
				int ret = sendto(gs_serverSendSocket, (char*)(&sendPackage), sizeof(sendPackage), 0,(sockaddr *)&(m_clientInfo[i].clientSocketAddr),sizeof(m_clientInfo[i].clientSocketAddr));	

				return ret;
			}
		}

		return -1;
	}

	void ChannelManager::updateControlInfo(ControlPackage controlInfo)
	{
		gs_channelNum = controlInfo.channelNum;
		m_cameraOffset = controlInfo.cameraOffset;

		m_hOffset = controlInfo.hOffset;
		m_vOffset = controlInfo.vOffset;

		m_eyeOffset = controlInfo.eyePosOffset;

		float ch_ratio = vgChannel::ChannelManager::getSingleton().getOffsetRatio();
		vgCam::CamManager::getSingleton().setViewFrustumParam(gs_channelNum, ch_ratio, m_hOffset, m_vOffset);
		//vgCam::CamManager::getSingleton().setupViewFrustum();
		
		stringstream outString;
		outString << "Camera offset set as : " << m_cameraOffset << "\n";
		VGK_SHOW(outString.str().c_str());
	}

	ClientInfo ChannelManager::getClientInfo(int index)
	{
		return m_clientInfo[index];
	}

	float ChannelManager::getOffsetRatio()
	{
		int hSize = GetSystemMetrics(SM_CXSCREEN); 

		float ret = hSize - m_cameraOffset;
		return ret / hSize; 
	}

	void ChannelManager::blendAndAdjust()                
	{
		if (m_blendAndAdjust)
		{

			m_blendAdjustImpl.blendPixelBegin();

			m_nurbsAdjustImpl.blendPixel();			

			m_blendAdjustImpl.blendPixelEnd();
		}
	}

	void ChannelManager::setBlendAndAdjustEnable(bool b)
	{
		m_blendAndAdjust = b;
		
		if (m_blendAndAdjust)
		{
			m_nurbsAdjustImpl.recomplieCallList();	
		}
	}

	void ChannelManager::SetChannelFromFile()
	{
		CString strFilePathName = getConfigFilePth();
		DWORD serverIP;
		CString Xmlsectionname;

		Xmlsectionname = _T("Server IP");

		if (vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument(strFilePathName)&&
			vgConfig::XMLConfigManager::getSingleton().FindSection(Xmlsectionname))
		{	
			vgConfig::SectionData tempIp = vgConfig::XMLConfigManager::getSingleton().GetCurrentValue(Xmlsectionname);
			CString tempServIP = tempIp._Currentkeyvalue[0];

			serverIP = inet_addr(tempServIP);
			setServerIP(serverIP);

		}

	}

	DWORD ChannelManager::GetServerIP()
	{
		return dwIPServ;
	}

	CString ChannelManager::getConfigFilePth()//仅使用在客户端
	{
		CString strExtension = _T(".xml");

		char exebuf[512];
		DWORD getret = GetModuleFileName( NULL , exebuf , 512 );

		assert( getret < 512 );
		assert( getret > 0 );

		String exestr( exebuf );
		String exepath = exestr.substr( 0 , 
			exestr.find_last_of("\\/")  + 1);

		CString path;
		path.Format("%s", exepath.c_str());

		CString Xmlfilename =  _T("ServerIP");		//@FengYK	2009/10/31 10:21
		CString configFilePath = path + Xmlfilename + strExtension ;
		return configFilePath;
	}

	void ChannelManager::SaveChannelSetToFile()
	{
		CString strFilePathName = getConfigFilePth();
		DWORD serverIP;

		vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument(strFilePathName);

		struct   sockaddr_in   local;   
		serverIP = GetServerIP();
		local.sin_family = AF_INET;   
		local.sin_addr.s_addr = serverIP;  
		CString tempServIP = inet_ntoa(local.sin_addr);

		vgConfig::XMLConfigManager::getSingleton().AddKeys(_T("Server IP"), 
			_T("ServerIP"), tempServIP);

		vgConfig::XMLConfigManager::getSingleton().SaveXML(strFilePathName);

	}

	void ChannelManager::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{

	}

	void ChannelManager::OnLButtonDown(UINT nFlags, CPoint position)
	{
		Lflag = true;
		vgKernel::Vec3 click_pos = vgKernel::Math::trans2DPointTo3DVec(position.x, position.y);
		m_nurbsAdjustImpl.Ifchose(click_pos);
		//m_nurbsAdjustImpl.IfFrustumPoint(click_pos);

	}

	void ChannelManager::OnLButtonUp(UINT nFlags, CPoint position)
	{
		Lflag = false;

	}

	void ChannelManager::OnMouseMove(UINT nFlags, CPoint position)
	{
		if (Lflag == true)
		{
			vgKernel::Vec3 click_pos = vgKernel::Math::trans2DPointTo3DVec(position.x, position.y);
			m_nurbsAdjustImpl.MoveContrlPoint(click_pos);

			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}
	}

	void ChannelManager::OnChar(int keyCode)
	{
		if(keyCode == vgKernel::InputCode::UP)
		{
			m_nurbsAdjustImpl.moveUp();
		}

		if(keyCode == vgKernel::InputCode::DOWN)
		{
			m_nurbsAdjustImpl.moveDown();
		}
		if(keyCode == vgKernel::InputCode::LEFT)
		{
			m_nurbsAdjustImpl.moveLeft();
		}

		if(keyCode == vgKernel::InputCode::RIGHT)
		{
			m_nurbsAdjustImpl.moveRight();
		}

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}
	
	CString ChannelManager::floatToCstr(float floatValue)
	{
		CString keyvalue;
		keyvalue.Format("%f", floatValue);
		return keyvalue;
	}

	void ChannelManager::saveClientInfotoXML(CString clientIp, CString chanNum, 
		int chCameraOffset, float hOffset, float vOffset, float eyePosOffset)
	{
		CString strFilePath = getClientInfoPath();
		CString xmlSectName = clientIp;//Section Name为IP地址
		CString cs_ChanNum = chanNum;
		CString cs_CameraOffset;

		cs_CameraOffset.Format("%d", chCameraOffset); 

		CString cs_hOffset = floatToCstr(hOffset);
		CString cs_vOffset = floatToCstr(vOffset);
		CString cs_eyeOffset = floatToCstr(eyePosOffset);

		vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument(strFilePath);

		vgConfig::XMLConfigManager::getSingleton().AddKeys(xmlSectName, 
			_T("ChannelNumber"), cs_ChanNum);
		vgConfig::XMLConfigManager::getSingleton().AddKeys(xmlSectName, 
			_T("CameraOffset"), cs_CameraOffset);
		vgConfig::XMLConfigManager::getSingleton().AddKeys(xmlSectName, 
			_T("hOffset"), cs_hOffset);
		vgConfig::XMLConfigManager::getSingleton().AddKeys(xmlSectName, 
			_T("vOffset"), cs_vOffset);
		vgConfig::XMLConfigManager::getSingleton().AddKeys(xmlSectName, 
			_T("eyePosOffset"), cs_eyeOffset);

		vgConfig::XMLConfigManager::getSingleton().SaveXML(strFilePath);
	}

	void ChannelManager::readClientInfofromXML()
	{
		CString strFilePath = getClientInfoPath();
		int numOfinClient = getInComeClientNum();//已连接的客户端数目

		vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument(strFilePath);

		for (int i=0; i<numOfinClient; i++)
		{			
			CString m_tempIP = inet_ntoa(m_clientInfo[i].clientSocketAddr.sin_addr);

			if (vgConfig::XMLConfigManager::getSingleton().FindSection(m_tempIP))
			{
				//从XML文件中读出数据
				vgConfig::SectionData tempSecData = vgConfig::XMLConfigManager::getSingleton().GetCurrentValue(m_tempIP);

				CString chanNum = tempSecData._Currentkeyvalue[0];

				int camOffset = vgConfig::XMLConfigManager::
					getSingleton().GetFloatValue(m_tempIP, _T("CameraOffset"));
				float f_hOffset = vgConfig::XMLConfigManager::
					getSingleton().GetFloatValue(m_tempIP, _T("hOffset"));
				float f_vOffset = vgConfig::XMLConfigManager::
					getSingleton().GetFloatValue(m_tempIP, _T("vOffset"));
				float f_eyeOffset = vgConfig::XMLConfigManager::
					getSingleton().GetFloatValue(m_tempIP, _T("eyePosOffset"));
				//将读出的数值赋给客户端
				if (chanNum == "+1")
				{
					m_clientInfo[i].controlParam.channelNum = 1;
				}
				else if (chanNum == "-1")
				{
					m_clientInfo[i].controlParam.channelNum = -1;
				}
				else if (chanNum == "+11")
				{
					m_clientInfo[i].controlParam.channelNum = 11;
				}
				else if (chanNum == "-11")
				{
					m_clientInfo[i].controlParam.channelNum = -11;
				}
				else if (chanNum == "10")
				{
					m_clientInfo[i].controlParam.channelNum = 10;
				}
				m_clientInfo[i].controlParam.cameraOffset = camOffset;
				m_clientInfo[i].controlParam.hOffset = f_hOffset;
				m_clientInfo[i].controlParam.vOffset = f_vOffset;
				m_clientInfo[i].controlParam.eyePosOffset = f_eyeOffset;
				//发送配置参数到客户端
				vgChannel::ControlPackage cp;
				cp.channelNum = m_clientInfo[i].controlParam.channelNum;
				cp.cameraOffset = camOffset;
				cp.hOffset = f_hOffset;
				cp.vOffset = f_vOffset;
				cp.eyePosOffset = f_eyeOffset;

				vgChannel::ChannelManager::getSingleton().setControlInfoByIp(m_tempIP.GetString(), cp);
			}
		}
	}

	void ChannelManager::setClientInfoPath(CString fullPathName)
	{
		strClientInfoPath = fullPathName;
	}

	CString ChannelManager::getClientInfoPath()
	{
		return strClientInfoPath;
	}

}//vgChannelManager命名空间结束

