
#include <vgStableHeaders.h>
#include <vgKernel/vgkExportManager.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>

//m OLE 所需相关头文件
#include <ole/CApplication.h>
#include <ole/CDocument0.h>
#include <ole/CDocuments.h>
#include <ole/CSelection.h>
#include <AtlBase.h>
#include <ole/CTables0.h>
#include <ole/CTable0.h>
#include <ole/CFont0.h>
#include <ole/CRange.h>
#include <ole/CCells.h>
#include <ole/CCell.h>
#include <ole/CShading.h>
#include <ole/CParagraphs.h>
#include <ole/CParagraph.h>



namespace vgKernel {

	bool ExportManager::ExportToWord()
	{
		CString m_wordPath;

		CString szFilter("(*.doc)|*.doc|All Files (*.*)|*.*||");

		CFileDialog dlg (FALSE, _T("doc"), _T("*.doc"),
			OFN_HIDEREADONLY, szFilter, NULL);

		if (dlg.DoModal() == IDOK)
		{
			m_wordPath = dlg.GetPathName();		
		}
		else
		{
			return false;
		}

		if ( m_wordPath.IsEmpty() )
		{
			return false;
		}

		CApplication wordApp;//m 定义若干变量；
		CDocuments   wordDocs;
		CDocument0   wordDoc;
		CSelection   wordSelection;
		CTables0     wordTables;
		CTable0      wordTable;      
		CFont0       wordFont;
		CRange       wordRange;
		CCell        wordCell;    
		CCells       wordCells;
		CShading     wordShading;

		int nRow=0;
		COleVariant vTrue((short)TRUE),
			vFalse((short)FALSE),
			vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		CComVariant defaultBehavior(1),AutoFitBehavior(0);//m 定义几个变量下面插入表格时会作为填充参数用到；

		if (!wordApp.CreateDispatch (_T("Word.Application")))//m 创建word application实例；
		{
			AfxMessageBox (_T("Error Connecting to Word"));
		}
		wordApp.put_Visible(FALSE);	//设置WORD不可见。//app.put_Visible(TRUE);	//设置WORD可见。

		wordDocs=wordApp.get_Documents();//m 得到documents对象；

		CComVariant tpl(_T("")),Visble,DocType(0),NewTemplate(false);
		wordDoc=wordDocs.Add(&tpl,&NewTemplate,&DocType,&Visble);//m 添加一个wordDoc对象到wordDocs中；
		wordSelection=wordApp.get_Selection();//m 得到当前应用程序的选择；
		wordTables=wordDoc.get_Tables();//m 得到word文档中的表格集；

		CParagraphs   paragraphs1;//代表文档中所有段 //m 欲将首行字体靠左显示，其它字体居中；  
		CParagraph    paragraph1;                 //代表文档中某一段   
		paragraphs1=wordDoc.get_Paragraphs();   
		paragraph1=paragraphs1.GetFirst(); 
		wordRange=paragraph1.GetRange();   //选中第一段
		wordFont=wordRange.GetFont();   
		wordFont.put_Bold(9999998);
		wordFont.put_Name(_T("宋体"));   
		wordFont.put_Size((short)18);   
		paragraph1.SetAlignment(1);   //使一段(Paragraph)靠左显示“3”   
		wordRange.SetText(_T("用地平衡表\n"));   

		paragraph1=paragraphs1.GetLast();//	m 得到最后一段；
		wordRange=paragraph1.GetRange();   //选中第一段
		wordFont=wordRange.GetFont();
		paragraph1.SetAlignment(1);   //使最后一段(Paragraph)居中显示；“1”

		wordSelection.EndOf(COleVariant((short)6),COleVariant((short)0));//m //move to end of story;
		wordFont = wordSelection.GetFont();//m 得到字体集；
		wordFont.put_Bold(9999998);//m 设置字体为粗体，函数用的是vs2005自带的；注意：普通字体是写入字体然后再设置其格式；
		wordFont.put_Name(_T("宋体"));   
		wordFont.put_Size((short)12); 

		wordRange=wordSelection.GetRange();//m 得到选择范围；
		wordTable=wordTables.Add(wordRange,8/*row*/,6/*column*/,&defaultBehavior,&AutoFitBehavior);//m 插入8*6图表；
		wordRange=wordTable.GetRange();
		wordCell=wordTable.Cell(1,1);//m 选择表格中第一个单元格；
		wordCell.Select();//m 选中该单元格；
		wordSelection.EndKey(&CComVariant(10),&CComVariant(1));//m 选中当前单元格所在的整个行（row）；

		wordCells=wordSelection.GetCells();
		wordShading = wordCells.get_Shading();//m 得到字体背景,函数用的是vs2005自带的；
		wordShading.SetTexture(0);
		wordShading.SetBackgroundPatternColor(14737632);//15987699 14737632 adColorBlue 设置背景色；
		wordShading.SetForegroundPatternColor(-16777216);//m 设置前景色；

		//m 填充表格中第一行中的字体 ；注意：表格中是先设置的字体格式然后再写入文字；
		wordCell=wordTable.Cell(1,1);//m 选择表格中第一个单元格；
		wordCell.Select();//m 选中该单元格；
		wordSelection.TypeText(_T("序号"));
		wordSelection.MoveRight(&CComVariant(12),&CComVariant(1),&CComVariant(0));//m 将光标移到右边紧挨着的单元格中；
		wordSelection.TypeText(_T("类别代号"));
		wordSelection.MoveRight(&CComVariant(12),&CComVariant(1),&CComVariant(0));
		wordSelection.TypeText(_T("用地性质"));
		wordSelection.MoveRight(&CComVariant(12),&CComVariant(1),&CComVariant(0));
		wordSelection.TypeText(_T("用地面积(公顷)"));
		wordSelection.MoveRight(&CComVariant(12),&CComVariant(1),&CComVariant(0));
		wordSelection.TypeText(_T("百分比%"));
		wordSelection.MoveRight(&CComVariant(12),&CComVariant(1),&CComVariant(0));
		wordSelection.TypeText(_T("人均用地面积（平方米）"));

		for (int row=0;row<7;row++)//m 序号插入0、1、2、3等序号；
		{
			wordCell=wordTable.Cell(row+2,1);//m 选择表格中的某个单元格；
			wordCell.Select();//m 选中该单元格；

			int content=row+1;
			CString temp;
			temp.Format(_T("%d"),content);
			wordSelection.TypeText(temp);//m 将文字写入单元格；

		}
		
		wordCell=wordTable.Cell(2,2);//m 选择表格中的某个单元格；
		wordCell.Select();//m 选中该单元格；
		wordSelection.TypeText(_T("C"));//m 将文字写入单元格；

		CCell nextcell=wordCell.GetNext();
		
		nextcell.Select();//m 选中该单元格；
		wordSelection.TypeText(_T("公共设施用地"));//m 将文字写入单元格；
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		/*CCell */nextcell=nextcell.GetNext();//m 这儿是重点，用单元格移动的方式依次往后操作，再插入表格太麻烦且效果不对；
		nextcell.Select();//m 不加这句，则未选中新的即下一次单元格；
		wordSelection.TypeText(_T("80.73"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("41.38937"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("14.95"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("其中"));
		nextcell.Split(COleVariant((short)1),COleVariant((short)2));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("C1行政办公用地"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("1.22"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.62548"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.23"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 同一行；
		nextcell.Select();
		wordSelection.TypeText(_T("C2商业金融业用地"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("54.73"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("28.05947"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("10.14"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 同一行；
		nextcell.Select();
		wordSelection.TypeText(_T("C3文化娱乐用地"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("15.78"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("8.09023"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("2.92"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 同一行；
		nextcell.Select();
		wordSelection.TypeText(_T("C4体育用地"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("4.61"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("2.36350"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.85"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 同一行；
		nextcell.Select();
		wordSelection.TypeText(_T("C5医疗卫生用地"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("2.43"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("1.24583"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.45"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 同一行；
		nextcell.Select();
		wordSelection.TypeText(_T("C6教育科研用地"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.39"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.19995"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.07"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 同一行；
		nextcell.Select();
		wordSelection.TypeText(_T("C7文物古迹用地"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("1.57"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.80492"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.29"));
		//*******************************第二大行
		//wordCell=wordTable.Cell(3,2)/*nextcell.GetNext()*/;//m ！！！无法重新选中单元格，郁闷！！；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("2"));

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("D"));

		nextcell=nextcell.GetNext();
		nextcell.Select();//m 选中该单元格；
		wordSelection.TypeText(_T("特殊用地"));//m 将文字写入单元格；
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 这儿是重点，用单元格移动的方式依次往后操作，再插入表格太麻烦且效果不对；
		nextcell.Select();//m 不加这句，则未选中新的即下一次单元格；
		wordSelection.TypeText(_T("1.67"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.85619"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.31"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("其中"));
		nextcell.Split(COleVariant((short)1),COleVariant((short)2));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("D1军事用地"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.55"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.28198"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.10"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 同一行；
		nextcell.Select();
		wordSelection.TypeText(_T("D2外事用地"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("1.12"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.57421"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.21"));
		//*******************************第三大行开始
		//wordCell=wordTable.Cell(3,2)/*nextcell.GetNext()*/;//m ！！！无法重新选中单元格，郁闷！！；
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("3"));

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("G"));

		nextcell=nextcell.GetNext();
		nextcell.Select();//m 选中该单元格；
		wordSelection.TypeText(_T("绿地"));//m 将文字写入单元格；
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 这儿是重点，用单元格移动的方式依次往后操作，再插入表格太麻烦且效果不对；
		nextcell.Select();//m 不加这句，则未选中新的即下一次单元格；
		wordSelection.TypeText(_T("8.62"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("4.41938"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("1.60"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("其中"));
		nextcell.Split(COleVariant((short)1),COleVariant((short)2));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("G1公共绿地"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("3.42"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("1.75340"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.63"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 同一行；
		nextcell.Select();
		wordSelection.TypeText(_T("G2生产防护绿地"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("5.20"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("2.66598"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.96"));
		//*******************************第四大行开始
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("4"));

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("R"));

		nextcell=nextcell.GetNext();
		nextcell.Select();//m 选中该单元格；
		wordSelection.TypeText(_T("居住用地"));//m 将文字写入单元格；
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 这儿是重点，用单元格移动的方式依次往后操作，再插入表格太麻烦且效果不对；
		nextcell.Select();//m 不加这句，则未选中新的即下一次单元格；
		wordSelection.TypeText(_T("85.80"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("43.98870"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("15.89"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("其中"));
		nextcell.Split(COleVariant((short)1),COleVariant((short)2));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("R1一类居住用地"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("38.24"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("19.60522"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("7.08"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 同一行；
		nextcell.Select();
		wordSelection.TypeText(_T("R2二类居住用地"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("47.56"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("24.38349"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("8.81"));
		//*******************************第五大行开始
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("5"));

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("S"));

		nextcell=nextcell.GetNext();
		nextcell.Select();//m 选中该单元格；
		wordSelection.TypeText(_T("道路广场用地"));//m 将文字写入单元格；
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 这儿是重点，用单元格移动的方式依次往后操作，再插入表格太麻烦且效果不对；
		nextcell.Select();//m 不加这句，则未选中新的即下一次单元格；
		wordSelection.TypeText(_T("5.66"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("2.90182"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("1.05"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("其中"));
		nextcell.Split(COleVariant((short)1),COleVariant((short)2));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("S2广场用地"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("4.20"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("2.15329"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.78"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 同一行；
		nextcell.Select();
		wordSelection.TypeText(_T("S3社会停车厂库用地"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("1.46"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.74853"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.27"));
		//*******************************第六大行开始
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("6"));

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("U"));

		nextcell=nextcell.GetNext();
		nextcell.Select();//m 选中该单元格；
		wordSelection.TypeText(_T("市政公用设施用地"));//m 将文字写入单元格；
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 这儿是重点，用单元格移动的方式依次往后操作，再插入表格太麻烦且效果不对；
		nextcell.Select();//m 不加这句，则未选中新的即下一次单元格；
		wordSelection.TypeText(_T("2.97"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("1.52269"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.55"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("其中"));
		nextcell.Split(COleVariant((short)1),COleVariant((short)2));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("U1供应设施用"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("1.00"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.51269"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.19"));
		nextcell.Split(COleVariant((short)2),COleVariant((short)1));//m 将当前选中的单元格分裂成个2*1的新单元格；

		nextcell=nextcell.GetNext();//m 同一行；
		nextcell.Select();
		wordSelection.TypeText(_T("U2交通设施用地"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("1.97"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("1.01000"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("0.36"));
		//*******************************第七大行开始
		nextcell=nextcell.GetNext();
		nextcell.Select();
		CCell c81=nextcell;
		wordSelection.TypeText(_T("城市建设用地"));//m 1

		nextcell=nextcell.GetNext();
		nextcell.Select();
		CCell c82=nextcell;
		wordSelection.TypeText(_T(""));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		CCell c83=nextcell;
		wordSelection.TypeText(_T(""));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("195.05"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("100"));
		nextcell=nextcell.GetNext();
		nextcell.Select();
		wordSelection.TypeText(_T("36.12"));
		//m 合并（8,1）（8,2）（8,3）这3个单元格；
		c81.Merge(c82);
		c81.Merge(c83);

		//m 保存生成的word文档至该路径下；
		wordDoc.SaveAs(COleVariant(m_wordPath),COleVariant((short)0),vOpt,vOpt,vOpt,vOpt,vOpt,vOpt
			,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt,vOpt);
		
		//m 释放所有的对象；
		//Release com
		wordFont.ReleaseDispatch();
		wordCells.ReleaseDispatch();
		wordShading.ReleaseDispatch();
		wordTable.ReleaseDispatch();
		wordTables.ReleaseDispatch();
		wordRange.ReleaseDispatch();
		wordSelection.ReleaseDispatch();
		wordDoc.ReleaseDispatch();
		wordDocs.ReleaseDispatch();

		CComVariant SaveChanges(false),OriginalFormat,RouteDocument;
		wordApp.Quit(&SaveChanges,&OriginalFormat,&RouteDocument);
		wordApp.ReleaseDispatch();

		CString keystr;
		keystr.Format(_T("数据已成功导出至:%s"),m_wordPath);
		AfxMessageBox(keystr,MB_ICONINFORMATION);

		return true;
	}
	////----------------------------------------------------------------
	bool ExportManager::ExportToExcel()
	{
		CoInitialize(NULL);	// 初始化COM库
		
		CLSID clsid;// 获得EXCEL的CLSID
		HRESULT hr = CLSIDFromProgID(L"Excel.Application", &clsid);
		if(FAILED(hr)) 
		{
			AfxMessageBox(_T("CLSIDFromProgID() 函数调用失败！"));
			return false;
		}
    
		IDispatch *pXlApp;// 创建实例 //m 创建excel实例,作用相当于“_Application   oApp;//oApp.CreateDispatch("Excel.Application",NULL); ”这两句；
		hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **)&pXlApp);
		if(FAILED(hr))
		{
			AfxMessageBox(_T("请检查是否已经安装EXCEL！"));
			return false;
		}

		VARIANT x;// 显示，将Application.Visible属性置1
		x.vt = VT_I4;
		x.lVal = 0;//m 0为隐式显示；//m 实践证明这个参数是控制excel的创建时显示或隐式；1为显示显示，0为隐式；
		AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlApp, L"Visible", 1, x);

		
		IDispatch *pXlBooks;// 获取Workbooks集合
		{
			VARIANT result;
			VariantInit(&result);
			AutoWrap(DISPATCH_PROPERTYGET, &result, pXlApp, L"Workbooks", 0);
			pXlBooks = result.pdispVal;
		}

		IDispatch *pXlBook;// 调用Workbooks.Add()方法，创建一个新的Workbook
		{
			VARIANT result;
			VariantInit(&result);
			AutoWrap(DISPATCH_PROPERTYGET, &result, pXlBooks, L"Add", 0);
			pXlBook = result.pdispVal;
		}
		
		VARIANT arr;// 创建一个15x15的数组，用于填充表格
		WCHAR szTmp[32];
		arr.vt = VT_ARRAY | VT_VARIANT;
		SAFEARRAYBOUND sab[2];
		sab[0].lLbound = 1; sab[0].cElements = 15;
		sab[1].lLbound = 1; sab[1].cElements = 15;
		arr.parray = SafeArrayCreate(VT_VARIANT, 2, sab);

		
		for(int i=1; i<=15; i++) // 初始化数组内容
		{
			for(int j=1; j<=15; j++) 
			{
				VARIANT tmp;
				tmp.vt = VT_BSTR;
				wsprintfW(szTmp,L"%i,%i",i,j);
				tmp.bstrVal = SysAllocString(szTmp);
				long indices[] = {i,j};// 添加数据到数组中
				SafeArrayPutElement(arr.parray, indices, (void *)&tmp);
			}
		}

		IDispatch *pXlSheet;// 从Application.ActiveSheet属性获得Worksheet对象
		{
			VARIANT result;
			VariantInit(&result);
			AutoWrap(DISPATCH_PROPERTYGET, &result, pXlApp, L"ActiveSheet", 0);
			pXlSheet = result.pdispVal;
		}

		IDispatch *pXlRange;// 选择一个15x15大小的Range
		{
			VARIANT parm;
			parm.vt = VT_BSTR;
			parm.bstrVal = ::SysAllocString(L"A1:O15");

			VARIANT result;
			VariantInit(&result);
			AutoWrap(DISPATCH_PROPERTYGET, &result, pXlSheet, L"Range", 1, parm);
			VariantClear(&parm);

			pXlRange = result.pdispVal;
		}

		AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlRange, L"Value", 1, arr);// 用我们的数组填充这个Range
		pXlRange->Release();

		{// 另外再选择一个Range
			VARIANT parm;
			parm.vt = VT_BSTR;
			parm.bstrVal = ::SysAllocString(L"A11:O25");

			VARIANT result;
			VariantInit(&result);
			AutoWrap(DISPATCH_PROPERTYGET, &result, pXlSheet, L"Range", 1, parm);
			VariantClear(&parm);

			pXlRange = result.pdispVal;
		}
		AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlRange, L"Value", 1, arr);// 用我们的数组再次填充这个Range
		
		CString strDocTemplate;//m 导出的数据文件保存路径为当前工程Debug文件夹下； 
		CString strPath;
		TCHAR szFullPath[_MAX_PATH];
		::GetModuleFileName(NULL,szFullPath,_MAX_PATH);
		strDocTemplate=szFullPath;
		int nPos=strDocTemplate.ReverseFind('\\');
		nPos+=1;
		strDocTemplate=strDocTemplate.Left(nPos);
		strPath=strDocTemplate;
		SYSTEMTIME sysTime;//m 将word保存成一个报告，以系统时间命名加以区分；
		GetLocalTime(&sysTime);
		CString excelsavepath;//m 设置文件保存路径；
		CString filetype;
		excelsavepath.Format(_T("%d年-%d月-%d日 %d点%d分%d秒 用地平衡表1"),sysTime.wYear,sysTime.wMonth,
			sysTime.wDay,sysTime.wHour,sysTime.wMinute,sysTime.wSecond);
		filetype=_T(".xlsx");
		excelsavepath=strPath+_T("")+excelsavepath+filetype;

		int nLen = excelsavepath.GetLength() + 1;
		WCHAR* pwsz = new WCHAR [ nLen];
		pwsz=excelsavepath.AllocSysString();//m CString转wchar_t；

		// 接下来我们该保存文件了，利用Worksheet.SaveAs()方法(我这里忽略了其他所有参数，除了文件名)
		{
			VARIANT filename;
			filename.vt = VT_BSTR;
			//filename.bstrVal = SysAllocString(L"d:\\Mytest2.xlsx");
			filename.bstrVal = SysAllocString(pwsz);//m "L" 和"_T"二者效果是一样的；
			AutoWrap(DISPATCH_METHOD, NULL, pXlSheet, L"SaveAs", 1, filename);
		}

		CString keystr;
		keystr.Format(_T("数据已成功导出至:%s"),excelsavepath);
		AfxMessageBox(keystr,MB_ICONINFORMATION);

		AutoWrap(DISPATCH_METHOD, NULL, pXlApp, L"Quit", 0);		// 退出，调用Application.Quit()方法

		pXlRange->Release();//m // 释放所有的接口以及变量;从此处可以看出实际上还是根据OLE方式对excel进行操作，只是没有依次定义这些变量，而是有效封装了起来；
		pXlSheet->Release();
		pXlBook->Release();
		pXlBooks->Release();
		pXlApp->Release();
		VariantClear(&arr);

		CoUninitialize();// 注销COM库

		return true;
	}
	////----------------------------------------------------------------	
	HRESULT  ExportManager::AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...)
	{
		// Begin variable-argument list...
		va_list marker;
		va_start(marker, cArgs);

		if(!pDisp) 
		{
			AfxMessageBox(_T("NULL IDispatch passed to AutoWrap()"));
			_exit(0);
		}

		// Variables used...
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		DISPID dispID;
		HRESULT hr;
		char buf[200];
		char szName[200];

		// Convert down to ANSI
		WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);

		// Get DISPID for name passed...
		hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
		if(FAILED(hr)) 
		{
			sprintf(buf, "IDispatch::GetIDsOfNames(\"%s\") failed w/err 0x%08lx", szName, hr);
			AfxMessageBox(_T( "AutoWrap()"));
			_exit(0);
			return hr;
		}

		// Allocate memory for arguments...
		VARIANT *pArgs = new VARIANT[cArgs+1];
		// Extract arguments...
		for(int i=0; i<cArgs; i++) {
			pArgs[i] = va_arg(marker, VARIANT);
		}

		// Build DISPPARAMS
		dp.cArgs = cArgs;
		dp.rgvarg = pArgs;

		// Handle special-case for property-puts!
		if(autoType & DISPATCH_PROPERTYPUT) {
			dp.cNamedArgs = 1;
			dp.rgdispidNamedArgs = &dispidNamed;
		}

		// Make the call!
		hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
		if(FAILED(hr)) 
		{
			sprintf(buf, "IDispatch::Invoke(\"%s\"=%08lx) failed w/err 0x%08lx", szName, dispID, hr);
			AfxMessageBox(_T("AutoWrap()"));
			_exit(0);
			return hr;
		}
		// End variable-argument section...
		va_end(marker);

		delete [] pArgs;

		return hr;
	}


}// end of namespace vgKernel

