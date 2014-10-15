


#ifndef __VGSHWELLKNOWNBINARYDEFINITION_H__
#define __VGSHWELLKNOWNBINARYDEFINITION_H__


/**
	对WKB数据格式进行定义.
	注意, 这里只是通俗定义, 不是C++数据定义.
	参考:
	Well-known binary (WKB) representation 
	http://publib.boulder.ibm.com/infocenter/db2luw/v8/index.jsp?topic=/com.ibm.db2.udb.doc/opt/rsbp4121.htm
*/

#if 0


		/**
			This section describes the well-known binary representation for geometries. 

			The OpenGIS Consortium "Simple Features for SQL" specification defines the well-known binary representation. This representation is also defined by the International Organization for Standardization (ISO) "SQL/MM Part: 3 Spatial" standard. See the related reference section at the end of this topic for information on functions that accept and produce the WKB. 

			The basic building block for well-known binary representations is the byte stream for a point, which consists of two double values. The byte streams for other geometries are built using the byte streams for geometries that are already defined. 

			The following example illustrates the basic building block for well-known binary representations. 
		*/
		
		// Basic Type definitions
		// byte : 1 byte
		// uint32 : 32 bit unsigned integer  (4 bytes)
		// double : double precision number (8 bytes)

		// Building Blocks : Point, LinearRing

		Point {
			double x;
			double y;
		};
		LinearRing   {
			uint32  numPoints;
			Point   points[numPoints];
		};
		enum wkbGeometryType {
			wkbPoint = 1,
			wkbLineString = 2,
			wkbPolygon = 3,
			wkbMultiPoint = 4,
			wkbMultiLineString = 5,
			wkbMultiPolygon = 6
		};
		enum wkbByteOrder {
			wkbXDR = 0,     // Big Endian
			wkbNDR = 1     // Little Endian
		};
		WKBPoint {
			byte     byteOrder;
			uint32   wkbType;     // 1=wkbPoint
			Point    point;
		};
		WKBLineString {
			byte     byteOrder;
			uint32   wkbType;     // 2=wkbLineString
			uint32   numPoints;
			Point    points[numPoints];
		};

		WKBPolygon    {
			byte                byteOrder;
			uint32            wkbType;     // 3=wkbPolygon
			uint32            numRings;
			LinearRing        rings[numRings];
		};
		WKBMultiPoint    {
			byte                byteOrder;
			uint32            wkbType;     // 4=wkbMultipoint
			uint32            num_wkbPoints;
			WKBPoint            WKBPoints[num_wkbPoints];
		};
		WKBMultiLineString    {
			byte              byteOrder;
			uint32            wkbType;     // 5=wkbMultiLineString
			uint32            num_wkbLineStrings;
			WKBLineString     WKBLineStrings[num_wkbLineStrings];
		};

		WKBMultiPolygon {
			byte              byteOrder;
			uint32            wkbType;     // 6=wkbMultiPolygon
			uint32            num_wkbPolygons;
			WKBPolygon        wkbPolygons[num_wkbPolygons];
		};

		WKBGeometry  {
			union {
				WKBPoint                 point;
				WKBLineString            linestring;
				WKBPolygon               polygon;
				WKBMultiPoint            mpoint;
				WKBMultiLineString       mlinestring;
				WKBMultiPolygon          mpolygon;
			}
		};

	
#endif
	



#endif // end of __VGSHWELLKNOWNBINARYDEFINITION_H__