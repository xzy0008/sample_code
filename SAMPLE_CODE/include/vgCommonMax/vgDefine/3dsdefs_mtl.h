/*******************************************************************
 *
 *    DESCRIPTION:  3DStudio R4 Material definitions
 *
 *    AUTHOR:
 *
 *    HISTORY:    
 *
 *******************************************************************/

#ifndef __MTLDEF__H
#define __MTLDEF__H

#define REND_WIRE 0
#define REND_FLAT 1
#define REND_GOURAUD 2
#define REND_PHONG 3
#define REND_METAL 4

/* Material flags field bit definitions	*/
#define MF_TWOSIDE  	(1<<0)	/* Material seen from both sides	*/
#define MF_SELF 	  	(1<<1)	/* Material self-illuminated		*/
#define MF_DECAL 		(1<<2)	/* Material maps act as decals (transparent color)	*/
#define MF_ADDITIVE 	(1<<3)	/* Material uses additive transparency	*/
#define MF_WIRE	 	(1<<4)	/* Material renders as wire frame */
#define MF_NEEDUV 	(1<<5)	/* Material has some UV type maps */
#define MF_NEED3D    (1<<6)	/* Material needs 3D coords for SXP */
#define MF_XPFALLIN  (1<<7)   /* Transparency fall-off to inside	*/
#define MF_MATTE  	(1<<8)	/* Material used as a matte		*/
#define MF_CUBICMAP 	(1<<9)	/* Reflection map is cubic		*/
#define MF_XPFALL   	(1<<10)  /* Do Transparency fall-off		*/
#define MF_SUPERSMP	(1<<11)	/* Super sample material */
#define MF_FACEMAP	(1<<12)	/* Face-texture-coords */
#define MF_PHONGSOFT	(1<<13)	/* Soften phong hilites */
#define MF_WIREABS	(1<<14)	/* Absolute wire size */
#define MF_REFBLUR   (1<<15)	/* blurred reflection map */
/* for clearing temporary flags */
#define MF_CLEAR_TEMPFLAGS ~(MF_NEEDUV|MF_NEED3D|MF_REFBLUR|MF_CUBICMAP)


#define CM_UP 0
#define CM_DOWN 1
#define CM_LEFT 2
#define CM_RIGHT 3
#define CM_FRONT 4
#define CM_BACK 5
#define CUBMAP_READY 1

/* Auto-cubic flags */
#define AC_ON  1	  /* if ON this is an auto-cubic mapped material */
#define AC_SHADOW  (1<<1)
#define AC_2SIDE  (1<<2)
#define AC_FIRSTONLY (1<<3)
#define AC_MIRROR (1<<4)

/* rmtl.use flags */
#define MATUSE_XPFALL (1<<0)
#define MATUSE_REFBLUR (1<<1)

/* TextureParam.texflags */
#define TEX_DECAL (1)
#define TEX_MIRROR (1<<1)
#define TEX_UNUSED1 (1<<2)
#define TEX_INVERT (1<<3)
#define TEX_NOWRAP (1<<4)
#define TEX_SAT (1<<5)	 /* summed area table */
#define TEX_ALPHA_SOURCE (1<<6) /* use ALPHA instead of RGB of map */
#define TEX_TINT (1<<7)         /* tint for color */
#define TEX_DONT_USE_ALPHA (1<<8)    /* don't use map alpha */
#define TEX_RGB_TINT (1<<9)    /* Do RGB color transform */

#define NMAPTYPES 8
#define Ntex 0
#define Ntex2 1
#define Nopac 2
#define Nbump 3
#define Nspec 4
#define Nshin 5
#define Nselfi 6
#define Nrefl 7

#define USE_tex  (1<<Ntex)
#define USE_tex2  (1<<Ntex2)
#define USE_opac  (1<<Nopac)
#define USE_bump  (1<<Nbump)
#define USE_spec  (1<<Nspec)
#define USE_shin  (1<<Nshin)
#define USE_selfi  (1<<Nselfi)
#define USE_refl  (1<<Nrefl)


#define MAP_TYPE_UV 1
#define MAP_TYPE_SXP 2

#define	LENGTH_MTL_NAME	20
#endif

