
/* Shape work stuff & defines */

#ifndef _SHAPE_H_DEFINED
#define _SHAPE_H_DEFINED

/* Shape info flag bit meanings */

#define SHPTICKS 1	/* Shape displayed with ticks on control pts */
#define SHPMODI 2	/* Shape uses MODICOUNT for steps */

/* Define edge flag bit meanings */

#define BRIDGE 4
#define SPLICE 2
#define VISEDGE 1

/* Template flag bit meanings */

#define TMPEND 0x0001		/* Last vertex of template polygon */
#define TMPCLOSED 0x0002	/* Template polygon closed */
#define TMPCTL 0x0004		/* Vertex is spline control pt */
#define TMPSMOOTH 0x0008	/* Vertex is smoothed */
#define TMPLINEAR 0x0010	/* Linear vertex on span */
#define TMPCSPAN 0x0020		/* Closing span */

#define TMPENDOFF 0xFFFE	/* Last vertex of template polygon */
#define TMPCLSOFF 0xFFFD	/* Template polygon closed */
#define TMPCTLOFF 0xFFFB	/* Vertex is spline control pt */
#define TMPSMOFF 0xFFF7		/* Vertex is smoothed */
#define TMPLINOFF 0xFFEF	/* Linear vertex on span */
#define TMPCSPOFF 0xFFDF	/* Closing span */

#undef POLYBOOL
#undef POLYINSIDE
#undef POLYOUTSIDE

/* Shape flags bit meanings */

#define POLYEND	0x0001		/* Set for last point in shape */
#define POLYCLOSED 0x0002	/* Set in last point to indicate closed poly */
#define POLYSPAN 0x0004		/* Span draw required */
#define POLYFLAG 0x0008		/* Misc-use flag */
#define POLYA	0x0010		/* Group A select bit */
#define POLYB	0x0020		/* Group B select bit */
#define POLYC	0x0040		/* Group C select bit */
#define POLYALL	0x0080		/* Entire poly selected bit */
#define POLYSHP	0x0100		/* Poly is part of shape bit */
#define POLYSTART 0x0200	/* Set for 1st control pt in poly */
#define POLYBOOL 0x0400		/* Boolean-created vertex */
#define POLYINSIDE 0x0800	/* Boolean: Inside other poly */
#define POLYOUTSIDE 0x1000	/* Boolean: Outside other poly */
#define POLYFROZEN 0x2000	/* Polygon is frozen */

#define POLYENDOFF 0xFFFE	/* Bitmask to turn off end flag */
#define POLYCLSOFF 0xFFFD	/* Bitmask to turn off closed flag */
#define POLYSPANOFF 0xFFFB	/* Bitmask to turn off span flag */
#define POLYFLAGOFF 0xFFF7	/* Bitmask to turn off selected flag */
#define POLYAOFF 0xFFEF		/* Group A select bit off */
#define POLYBOFF 0xFFDF		/* Group B select bit off */
#define POLYCOFF 0xFFBF		/* Group C select bit off */
#define POLYALLOFF 0xFF7F	/* Entire poly selected bit off */
#define POLYSHPOFF 0xFEFF	/* Poly is part of shape bit off */
#define POLYSTARTOFF 0xFDFF	/* 1st control pt in poly off */
#define POLYBOOLOFF 0xFBFF	/* Boolean-created vertex off */
#define POLYINSIDEOFF 0xF7FF	/* Boolean: Inside other poly off */
#define POLYOUTSIDEOFF 0x7FFF	/* Boolean: Outside other poly off */
#define POLYFROZENOFF 0xDFFF	/* Polygon is frozen off */

/* Spline open/closed flags */

#define NULLSPLINE -1	/* Partial segment */
#define OPEN 0		/* Open spline */
#define CLOSED 1	/* Closed spline */


#define SINGLE_SHAPE 0
#define MULTIPLE_SHAPES 1

// global setting : environment && background
#define ENV_DISTCUE 1
#define ENV_FOG 2
#define ENV_LAYFOG 3

#define BG_SOLID 1
#define BG_GRADIENT 2
#define BG_BITMAP 3

// 3DS face edge vis flags
#define ABLINE (1<<2)
#define BCLINE (1<<1)
#define CALINE 1

#define VWRAP (1<<11)		/* Texture coord V wraps on this face */
#define UWRAP (1<<3)		/* Texture coord U wraps on this face */

// Node list structure

#define OBJ_MESH 0
#define OBJ_OMNILIGHT 1
#define OBJ_SPOTLIGHT 2
#define OBJ_CAMERA 3
#define OBJ_DUMMY 4
#define OBJ_TARGET 5
#define OBJ_OTHER  6 // generated from app data


#define W_TENS  1
#define W_CONT  (1<<1)
#define W_BIAS  (1<<2)
#define W_EASETO  (1<<3)
#define W_EASEFROM  (1<<4)


#define KFVERSION 5


// key types
#define KEY_FLOAT	0
#define KEY_POS		1
#define KEY_ROT		2
#define KEY_SCL		3
#define KEY_COLOR	4

#define NUMTRACKS 8

#define POS_TRACK_INDEX 0
#define ROT_TRACK_INDEX 1
#define SCL_TRACK_INDEX 2
#define FOV_TRACK_INDEX 3
#define ROLL_TRACK_INDEX 4
#define COL_TRACK_INDEX 5
#define HOT_TRACK_INDEX 6
#define FALL_TRACK_INDEX 7



/* Camera flag bit meanings */

#define NO_CAM_CONE	0x0001
#define NO_CAM_TEMP_APPDATA 0x0002 /* Free appdata after rendering complete  */	

#define NO_CAM_CONE_OFF	(~NO_CAM_CONE)

/* Light flag bit meanings */

#define NO_LT_ON	0x0001
#define NO_LT_SHAD	0x0002
#define NO_LT_LOCAL	0x0004
#define NO_LT_CONE	0x0008
#define NO_LT_RECT	0x0010
#define NO_LT_PROJ	0x0020
#define NO_LT_OVER	0x0040
#define NO_LT_ATTEN	0x0080
#define NO_LT_RAYTR	0x0100
#define NO_LT_TEMP_APPDATA 0x0200 /* Free appdata after rendering complete  */	

#define NO_LT_OFF	(~NO_LT_ON)
#define NO_LT_SHAD_OFF	(~NO_LT_SHAD)
#define NO_LT_LOCAL_OFF	(~NO_LT_LOCAL)
#define NO_LT_CONE_OFF	(~NO_LT_CONE)
#define NO_LT_RECT_OFF	(~NO_LT_RECT)
#define NO_LT_PROJ_OFF	(~NO_LT_PROJ)
#define NO_LT_OVER_OFF	(~NO_LT_OVER)
#define NO_LT_ATTEN_OFF	(~NO_LT_ATTEN)

/*--------- Track flags bits------------ */

/*-- This bit causes the spline to be cyclic */
#define ANIM_CYCLIC 1
/*-- This bit causes a track to continue "modulo" its duration */
#define ANIM_LOOP  (1<<1)
/*-- This bit is used by anim.c, but clients need not worry about it*/
#define ANIM_NEGWRAP (1<<2)

#define X_LOCKED (1<<3)
#define Y_LOCKED (1<<4)
#define Z_LOCKED (1<<5)
#define ALL_LOCKED (X_LOCKED|Y_LOCKED|Z_LOCKED)
#define TRACK_ATKEY (1<<6)

/* these flags specify which coords are NOT inherited from parent */ 
#define LNKSHFT 7
#define NO_LNK_X (1<<LNKSHFT)
#define NO_LNK_Y (1<<(LNKSHFT+1))
#define NO_LNK_Z (1<<(LNKSHFT+2))
#define LASTAXIS_SHFT 10
#define LASTAXIS_MASK (3<<LASTAXIS_SHFT)

// A worker object for dealing with creating the objects.
// Useful in the chunk-oriented 3DS file format

// Worker types

#define WORKER_IDLE		0
#define WORKER_MESH		1
#define WORKER_KF		2
#define WORKER_SHAPE	3
#define WORKER_LIGHT	4
#define WORKER_CAMERA	5


// key types
#define KEY_FLOAT	0
#define KEY_POS		1
#define KEY_ROT		2
#define KEY_SCL		3
#define KEY_COLOR	4


//#define SCHAR_MAX   128
#define NeedsKeys(nkeys)    ((nkeys) > 0 || (nkeys) == NOT_KEYFRAMEABLE)
#define KEYS_POS	        (1<<1)
#define KEYS_ROT	        (1<<2)
#define KEYS_SCL	        (1<<3)


#define DUMNUM 0x7fff

#define OBJ_NAME_LEN 10

#define VERTICES_FLIP_X


#define EXPORT_MTLS


#define LAYERS_BY_OBJECT 0
#define LAYERS_BY_MATERIAL 1
#define LAYERS_ONE_LAYER 2

#define NUM_SOURCES 3 		// # of sources in dialog


// 3DS face edge vis flags
#define ABLINE (1<<2)
#define BCLINE (1<<1)
#define CALINE 1

#define VWRAP (1<<11)		/* Texture coord V wraps on this face */
#define UWRAP (1<<3)		/* Texture coord U wraps on this face */


#endif// _SHAPE_H_DEFINED


