


#ifndef __VGENTRYUTILITY_H__
#define __VGENTRYUTILITY_H__

#include <vgKernel/vgkForward.h>
#include "vgBaseEntryEx.h"
	

class EntryUtility
{
private:
	EntryUtility()
	{
		
	}
public:
	~EntryUtility()
	{
		
	}
public:

	static  void invalidatePropValues( PropertiesParamVector& params );

	template<typename T>
	static T* getPtrFromProperties( PropertiesParamVector& params ,
		const String& query_name )
	{
		PropertiesParamVector::iterator iter = params.begin();
		PropertiesParamVector::iterator iter_end = params.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			PropertiesParam& pa = *iter;
			if ( pa.label == query_name )
			{
				return (T*)pa.connectedPtr;
			}
		}

		return NULL;
	}

};




#define VG_PUSH_PROP_GROUP( paramsvec , description ) {\
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_GROUP;\
	param.dataType = PROP_DATA_NONE;\
	param.connectedPtr = NULL;\
	param.comment = description;\
	paramsvec.push_back( param ); }


#define VG_PUSH_PROP_STR( paramsvec , description , str_ptr) {\
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_STR;\
	param.connectedPtr = str_ptr;\
	param.comment = description;\
	paramsvec.push_back( param ); }

#define VG_PUSH_PROP_CONST_STR( paramsvec , description , const_str_ptr) {\
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_CONST_STR;\
	param.connectedPtr = const_str_ptr;\
	param.comment = description;\
	paramsvec.push_back( param ); }

#define VG_PUSH_PROP_CONST_STR2( paramsvec , description , const_str_ptr) {\
	static String staticStr;\
	std::ostringstream o;\
	o << *const_str_ptr; \
	staticStr = o.str(); \
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_CONST_STR;\
	param.connectedPtr = &staticStr;\
	param.comment = description;\
	paramsvec.push_back( param ); }

#define VG_PUSH_PROP_INT( paramsvec , description , int_ptr) {\
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_INT;\
	param.connectedPtr = int_ptr;\
	param.comment = description;\
	paramsvec.push_back( param ); }

#define VG_PUSH_PROP_CONST_INT( paramsvec , description , int_ptr) {\
	static String staticStr;\
	std::ostringstream o;\
	o << *int_ptr; \
	staticStr = o.str(); \
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_CONST_STR;\
	param.connectedPtr = &staticStr;\
	param.comment = description;\
	paramsvec.push_back( param ); }

#define VG_PUSH_PROP_FLOAT( paramsvec , description , float_ptr) {\
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_FLOAT;\
	param.connectedPtr = float_ptr;\
	param.comment = description;\
	paramsvec.push_back( param ); }


#define VG_PUSH_PROP_CONST_FLOAT( paramsvec , description , float_ptr) {\
	static String staticStr;\
	std::ostringstream o;\
	o << *float_ptr; \
	staticStr = o.str(); \
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_CONST_STR;\
	param.connectedPtr = &staticStr;\
	param.comment = description;\
	paramsvec.push_back( param ); }


#define VG_PUSH_PROP_DOUBLE( paramsvec , description , double_ptr) {\
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_DOUBLE;\
	param.connectedPtr = double_ptr;\
	param.comment = description;\
	paramsvec.push_back( param ); }


#define VG_PUSH_PROP_CONST_DOUBLE( paramsvec , description , double_ptr) {\
	static String staticStr;\
	std::ostringstream o;\
	o << *double_ptr; \
	staticStr = o.str(); \
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_CONST_STR;\
	param.connectedPtr = &staticStr;\
	param.comment = description;\
	paramsvec.push_back( param ); }

#define VG_PUSH_PROP_BOOL( paramsvec , description , bool_ptr) {\
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_BOOL;\
	param.connectedPtr = bool_ptr;\
	param.comment = description;\
	paramsvec.push_back( param ); }

#define VG_PUSH_PROP_CONST_BOOL( paramsvec , description , bool_ptr) {\
	static String staticStr;\
	std::ostringstream o;\
	o << *bool_ptr; \
	staticStr = o.str(); \
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_CONST_STR;\
	param.connectedPtr = &staticStr;\
	param.comment = description;\
	paramsvec.push_back( param ); }



#define VG_PUSH_PROP_COLOR( paramsvec , description , color_ptr) {\
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_COLOR;\
	param.connectedPtr = color_ptr;\
	param.comment = description;\
	paramsvec.push_back( param ); }



	/**
		@author  	lss
		@brief 
	*/
#define VG_PUSH_OPTION_START( paramsvec , description , option_ptr) {\
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_OPTION_START;\
	param.connectedPtr = &option_ptr;\
	param.comment = description;\
	paramsvec.push_back( param ); }

#define VG_PUSH_OPTION_ITEM( paramsvec , description ) {\
	PropertiesParam param;\
	param.label = description;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_OPTION_ITEM;\
	paramsvec.push_back( param ); }

#define VG_PUSH_OPTION_END( paramsvec ) {\
	PropertiesParam param;\
	param.typeId = PROP_ITEM_DATA;\
	param.dataType = PROP_DATA_OPTION_END;\
	paramsvec.push_back( param ); }




//------------------------------------------
// 修改某个prop的名称
//------------------------------------------
#define VG_CHANGE_PROP_LABEL( paramsvec , old_label , new_label )  \
	{\
		PropertiesParamVector::iterator iter = params.begin();\
		PropertiesParamVector::iterator iter_end = params.end();\
		for ( ; iter != iter_end ;++ iter )\
		{\
			if ( iter->label == old_label )\
			{\
				iter->label = iter->comment = new_label;\
			}\
		}\
	}



#endif // end of __VGENTRYUTILITY_H__