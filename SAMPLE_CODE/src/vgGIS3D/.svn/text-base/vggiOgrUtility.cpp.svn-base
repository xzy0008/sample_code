


#include <vgStableHeaders.h>
#include <vgGis3D/vggiOgrUtility.h>
#include <vgGis/vggisDefinition.h>
#include <vgGIS3D/vggiPrerequisite.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>
#include <vgKernel/vgkTrace.h>


namespace vgGIS3D {
	

	int OgrUtility::nGroupTransactions = 200;
	int OgrUtility::bPreserveFID = TRUE;
	int OgrUtility::nFIDToFetch = OGRNullFID;
	int OgrUtility::bSkipFailures = FALSE;
	
	//----------------------------------------------------------------
	int OgrUtility::TranslateLayer( OGRDataSource *poSrcDS, 
		OGRLayer * poSrcLayer, 
		OGRDataSource *poDstDS, 
		char **papszLCO, 
		const char *pszNewLayerName,
		int bTransform, 
		OGRSpatialReference *poOutputSRS, 
		OGRSpatialReference *poSourceSRS, 
		char **papszSelFields, 
		int bAppend, 
		int eGType,
		int bOverwrite ,
		bool append_vrgis_field/* = true*/,
		bool force_to_3d /*= true*/)
	{
		OGRLayer    *poDstLayer;
		OGRFeatureDefn *poFDefn;
		OGRErr      eErr;
		int         bForceToPolygon = FALSE;
		int         bForceToMultiPolygon = FALSE;

		if( pszNewLayerName == NULL )
			pszNewLayerName = poSrcLayer->GetLayerDefn()->GetName();

		if( wkbFlatten(eGType) == wkbPolygon )
			bForceToPolygon = TRUE;
		else if( wkbFlatten(eGType) == wkbMultiPolygon )
			bForceToMultiPolygon = TRUE;

		/* -------------------------------------------------------------------- */
		/*      Setup coordinate transformation if we need it.                  */
		/* -------------------------------------------------------------------- */
		OGRCoordinateTransformation *poCT = NULL;

		if( bTransform )
		{
			if( poSourceSRS == NULL )
				poSourceSRS = poSrcLayer->GetSpatialRef();

			if( poSourceSRS == NULL )
			{
				printMsg( "Can't transform coordinates, source layer has no\n"
					"coordinate system.  Use -s_srs to set one.\n" );
				return FALSE;
			}

			CPLAssert( NULL != poSourceSRS );
			CPLAssert( NULL != poOutputSRS );

			poCT = OGRCreateCoordinateTransformation( poSourceSRS, poOutputSRS );
			if( poCT == NULL )
			{
				char        *pszWKT = NULL;

				printMsg("Failed to create coordinate transformation between the\n"
					"following coordinate systems.  This may be because they\n"
					"are not transformable, or because projection services\n"
					"(PROJ.4 DLL/.so) could not be loaded.\n" );

				poSourceSRS->exportToPrettyWkt( &pszWKT, FALSE );
				printMsg( "Source:\n%s\n", pszWKT );

				poOutputSRS->exportToPrettyWkt( &pszWKT, FALSE );
				printMsg( "Target:\n%s\n", pszWKT );
				return FALSE;
			}
		}

		/* -------------------------------------------------------------------- */
		/*      Get other info.                                                 */
		/* -------------------------------------------------------------------- */
		poFDefn = poSrcLayer->GetLayerDefn();

		if( poOutputSRS == NULL )
			poOutputSRS = poSrcLayer->GetSpatialRef();

		/* -------------------------------------------------------------------- */
		/*      Find the layer.                                                 */
		/* -------------------------------------------------------------------- */
		int iLayer = -1;
		poDstLayer = NULL;

		for( iLayer = 0; iLayer < poDstDS->GetLayerCount(); iLayer++ )
		{
			OGRLayer        *poLayer = poDstDS->GetLayer(iLayer);

			if( poLayer != NULL 
				&& EQUAL(poLayer->GetLayerDefn()->GetName(),pszNewLayerName) )
			{
				poDstLayer = poLayer;
				break;
			}
		}

		/* -------------------------------------------------------------------- */
		/*      If the user requested overwrite, and we have the layer in       */
		/*      question we need to delete it now so it will get recreated      */
		/*      (overwritten).                                                  */
		/* -------------------------------------------------------------------- */
		if( poDstLayer != NULL && bOverwrite )
		{
			if( poDstDS->DeleteLayer( iLayer ) != OGRERR_NONE )
			{
				printMsg(
					"DeleteLayer() failed when overwrite requested.\n" );
				return FALSE;
			}
			poDstLayer = NULL;
		}

		/* -------------------------------------------------------------------- */
		/*      If the layer does not exist, then create it.                    */
		/* -------------------------------------------------------------------- */
		if( poDstLayer == NULL )
		{
			if( eGType == -2 )
				eGType = poFDefn->GetGeomType();

			if( !poDstDS->TestCapability( ODsCCreateLayer ) )
			{
				printMsg(
					"Layer %s not found, and CreateLayer not supported by driver.", 
					pszNewLayerName );
				return FALSE;
			}

			CPLErrorReset();

			//------------------------------------------
			// 将其设置为3D格式 
			//------------------------------------------
			if ( force_to_3d )
			{
				eGType = (eGType) | (wkb25DBit);
			}

			poDstLayer = poDstDS->CreateLayer( pszNewLayerName, poOutputSRS,
				(OGRwkbGeometryType) eGType, 
				papszLCO );

			if( poDstLayer == NULL )
				return FALSE;

			bAppend = FALSE;
		}

		/* -------------------------------------------------------------------- */
		/*      Otherwise we will append to it, if append was requested.        */
		/* -------------------------------------------------------------------- */
		else if( !bAppend )
		{
			printMsg( "FAILED: Layer %s already exists, and -append not specified.\n"
				"        Consider using -append, or -overwrite.\n",
				pszNewLayerName );
			return FALSE;
		}
		else
		{
			if( CSLCount(papszLCO) > 0 )
			{
				printMsg( "WARNING: Layer creation options ignored since an existing layer is\n"
					"         being appended to.\n" );
			}
		}

		/* -------------------------------------------------------------------- */
		/*      Add fields.  Default to copy all field.                         */
		/*      If only a subset of all fields requested, then output only      */
		/*      the selected fields, and in the order that they were            */
		/*      selected.                                                       */
		/* -------------------------------------------------------------------- */
		int         iField;

		if (papszSelFields && !bAppend )
		{
			assert(0);
			for( iField=0; papszSelFields[iField] != NULL; iField++)
			{
				int iSrcField = poFDefn->GetFieldIndex(papszSelFields[iField]);
				if (iSrcField >= 0)
				{
					poDstLayer->CreateField( poFDefn->GetFieldDefn(iSrcField) );
				}
				else
				{
					printMsg( "Field '%s' not found in source layer.\n", 
						papszSelFields[iField] );
					if( !bSkipFailures )
						return FALSE;
				}
			}
		}
		else if( !bAppend )
		{
			for( iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
			{
				poDstLayer->CreateField( poFDefn->GetFieldDefn(iField) );
			}

			if ( append_vrgis_field )
			{
				//------------------------------------------
				// 设定vrgis field
				//------------------------------------------
				int fieldid = poFDefn->GetFieldIndex(VG_GIS_STYLE_FIELD);
				if ( fieldid == -1 )
				{
					OGRFieldDefn vrgis_field( VG_GIS_STYLE_FIELD , 
						OFTString );

					vrgis_field.SetWidth( 50 );

					// 千万不要用下面这个!
					// 详见文档:
					/**
					OGRErr OGRLayer::CreateField  ( OGRFieldDefn *  poField,  
					int  bApproxOK = TRUE   
					)   [virtual] 

					Create a new field on a layer.
					You must use this to create new fields on a real layer. 
					Internally the OGRFeatureDefn for the layer will be updated to
					reflect the new field. Applications should never modify the 
					OGRFeatureDefn used by a layer directly.
					*/
					//def->AddFieldDefn( &vrgis_field );

					OGRErr err = poDstLayer->CreateField( &vrgis_field );
					assert( err == OGRERR_NONE );
				}
			}

		}

		/* -------------------------------------------------------------------- */
		/*      Transfer features.                                              */
		/* -------------------------------------------------------------------- */
		OGRFeature  *poFeature;
		int         nFeaturesInTransaction = 0;

		poSrcLayer->ResetReading();

		if( nGroupTransactions )
			poDstLayer->StartTransaction();

		while( TRUE )
		{
			OGRFeature      *poDstFeature = NULL;

			if( nFIDToFetch != OGRNullFID )
			{
				// Only fetch feature on first pass.
				if( nFeaturesInTransaction == 0 )
					poFeature = poSrcLayer->GetFeature(nFIDToFetch);
				else
					poFeature = NULL;
			}
			else
				poFeature = poSrcLayer->GetNextFeature();

			if( poFeature == NULL )
				break;

			if( ++nFeaturesInTransaction == nGroupTransactions )
			{
				poDstLayer->CommitTransaction();
				poDstLayer->StartTransaction();
				nFeaturesInTransaction = 0;
			}

			CPLErrorReset();
			poDstFeature = OGRFeature::CreateFeature( poDstLayer->GetLayerDefn() );

			if( poDstFeature->SetFrom( poFeature, TRUE ) != OGRERR_NONE )
			{
				if( nGroupTransactions )
					poDstLayer->CommitTransaction();

				CPLError( CE_Failure, CPLE_AppDefined,
					"Unable to translate feature %d from layer %s.\n",
					poFeature->GetFID(), poFDefn->GetName() );

				OGRFeature::DestroyFeature( poFeature );
				OGRFeature::DestroyFeature( poDstFeature );
				return FALSE;
			}

			if( bPreserveFID )
				poDstFeature->SetFID( poFeature->GetFID() );

			if( poCT && poDstFeature->GetGeometryRef() != NULL )
			{
				eErr = poDstFeature->GetGeometryRef()->transform( poCT );
				if( eErr != OGRERR_NONE )
				{
					if( nGroupTransactions )
						poDstLayer->CommitTransaction();

					printMsg( "Failed to transform feature %d.\n", 
						(int) poFeature->GetFID() );
					if( !bSkipFailures )
					{
						OGRFeature::DestroyFeature( poFeature );
						OGRFeature::DestroyFeature( poDstFeature );
						return FALSE;
					}
				}
			}

			if( poDstFeature->GetGeometryRef() != NULL && bForceToPolygon )
			{
				poDstFeature->SetGeometryDirectly( 
					OGRGeometryFactory::forceToPolygon(
					poDstFeature->StealGeometry() ) );
			}

			if( poDstFeature->GetGeometryRef() != NULL && bForceToMultiPolygon )
			{
				poDstFeature->SetGeometryDirectly( 
					OGRGeometryFactory::forceToMultiPolygon(
					poDstFeature->StealGeometry() ) );
			}

			OGRFeature::DestroyFeature( poFeature );

			CPLErrorReset();
			if( poDstLayer->CreateFeature( poDstFeature ) != OGRERR_NONE 
				&& !bSkipFailures )
			{
				if( nGroupTransactions )
					poDstLayer->RollbackTransaction();

				OGRFeature::DestroyFeature( poDstFeature );
				return FALSE;
			}

			OGRFeature::DestroyFeature( poDstFeature );
		}

		if( nGroupTransactions )
			poDstLayer->CommitTransaction();

		/* -------------------------------------------------------------------- */
		/*      Cleaning                                                        */
		/* -------------------------------------------------------------------- */
		delete poCT;

		return TRUE;
	}
	//----------------------------------------------------------------
	bool OgrUtility::copyDataSource( OGRDataSource *poSrcDS, 
		OGRDataSource *poDstDS )
	{
		assert( poSrcDS != NULL );
		assert( poDstDS != NULL );

		for( int iLayer = 0; iLayer < poSrcDS->GetLayerCount(); 
			iLayer++ )
		{
			OGRLayer        *poLayer = poSrcDS->GetLayer(iLayer);

			if( poLayer == NULL )
			{
				assert(0);
				return false;
			}


			if( !TranslateLayer( poSrcDS, poLayer, poDstDS, NULL, 
				NULL, FALSE, 
				poLayer->GetSpatialRef(),
				poLayer->GetSpatialRef(), 
				NULL, FALSE, -2,
				TRUE ) 
				&& !bSkipFailures )
			{

				assert(0);
				return false;
			}
		}

		return true;
	}

	void OgrUtility::printMsg( const char *format, ... )
	{
		char szBuf[1024] = {0};
		va_list argptr;
		va_start(argptr, format);
		vsprintf_s(szBuf, sizeof(szBuf), format, argptr);
		va_end(argptr);

		VGK_SHOW( szBuf );
	}
	//----------------------------------------------------------------


}// end of namespace  
