



#include <vgStableHeaders.h>
#include <vgEntry/vgEntryUtility.h>



//----------------------------------------------------------------
void EntryUtility::invalidatePropValues( PropertiesParamVector& params )
{

	PropertiesParamVector::iterator iter = params.begin();
	PropertiesParamVector::iterator iter_end = params.end();

	for ( ; iter != iter_end  ;++ iter )
	{
		PropertiesParam* param = &*iter;
		assert( param != NULL );
		assert( param->pProp != NULL );

		if ( param->dataType == PROP_DATA_STR ||
			param->dataType == PROP_DATA_CONST_STR)
		{
			param->pProp->SetValue( ((String*)param->connectedPtr)->c_str() );
		}
		else if ( param->dataType == PROP_DATA_FLOAT )
		{
			param->pProp->SetValue( *(float*)param->connectedPtr );
		}
		else if ( param->dataType == PROP_DATA_INT )
		{
			param->pProp->SetValue( *(int*)param->connectedPtr );
		}
		else if ( param->dataType == PROP_DATA_DOUBLE )
		{
			param->pProp->SetValue( *( double* )param->connectedPtr );
		}
		else if ( param->dataType == PROP_DATA_BOOL )
		{
			param->pProp->SetValue( *( bool* )param->connectedPtr );
		}
		else if ( param->dataType == PROP_DATA_COLOR )
		{
			param->pProp->SetValue( *( COLORREF* )param->connectedPtr );
		}
	}

	return;
}
//----------------------------------------------------------------