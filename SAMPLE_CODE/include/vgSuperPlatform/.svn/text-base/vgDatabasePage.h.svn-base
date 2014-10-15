#ifndef VG_DATABASEPAGE_H
#define VG_DATABASEPAGE_H

#include "vgPropertyPage.h"
#include "vgBaseEntry.h"

typedef struct DatabaseProperties_t
{
	// unsigned int	dataType;			// 属性项的类型
	string			label;				// 属性项显示名称
	string			recordLable;			// 属性项在表中的字段名
	_variant_t		data;
	CBCGPProp*		pProp;				// 生成的属性对象指针
} DatabaseProperties;


class vgDatabasePage : public vgPropertyPage
{
public:

	void ConnectNode(vgBaseEntry* node, vector<DatabaseProperties>& propParamList);
	
	virtual LRESULT OnPropertyChanged(WPARAM w, LPARAM l);

};

#endif

