/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFASMMATH_H__
#define __VGFASMMATH_H__

#include <vgMath/vgfPrerequisites.h>


namespace vgMath {

		/**
			@date 	2007/02/19  23:05	
			@author  leven

			@brief 	汇编语言实现math库,注意,此时的库被Math类私有,其他所有类不可调用.
			另外,asm_*起头并不意味着完全是汇编实现,此时只是标志.在vgGlobalDefinition.h
			中定义VGES_USE_ASM_MATH可以选择是否使用汇编语言.

			函数列表:

			float asm_arccos( float r );
			float asm_arcsin( float r );
			float asm_arctan( float r );
			float asm_sin( float r );
			float asm_cos( float r );
			float asm_tan( float r );
			float asm_sqrt( float r );
			float asm_rsq( float r );
			float apx_rsq( float r );
			float asm_rand();
			float asm_rand_max();
			float asm_ln( float r );

			@see    
		*/

		/*=============================================================================
		ASM math routines posted by davepermen et al on flipcode forums
		=============================================================================*/
		const float pi = 4.0 * atan( 1.0 );
		const float half_pi = 0.5 * pi;

		/*=============================================================================
		NO EXPLICIT RETURN REQUIRED FROM THESE METHODS!! 
		=============================================================================*/


		inline float asm_arccos( float r ) {
			// return half_pi + arctan( r / -sqr( 1.f - r * r ) );

	#if VGES_USE_ASM_MATH == 1

			float asm_one = 1.f;
			float asm_half_pi = half_pi;
			__asm {
				fld r // r0 = r
					fld r // r1 = r0, r0 = r
					fmul r // r0 = r0 * r
					fsubr asm_one // r0 = r0 - 1.f
					fsqrt // r0 = sqrtf( r0 )
					fchs // r0 = - r0
					fdiv // r0 = r1 / r0
					fld1 // {{ r0 = atan( r0 )
					fpatan // }}
					fadd asm_half_pi // r0 = r0 + pi / 2
			} // returns r0

	#else

			return float( acos( r ) );

	#endif
		}

		//////////////////////////////////////////////////////////////////////////
		inline float asm_arcsin( float r ) {
			// return arctan( r / sqr( 1.f - r * r ) );

	#if VGES_USE_ASM_MATH == 1

			const float asm_one = 1.f;
			__asm {
				fld r // r0 = r
					fld r // r1 = r0, r0 = r
					fmul r // r0 = r0 * r
					fsubr asm_one // r0 = r0 - 1.f
					fsqrt // r0 = sqrtf( r0 )
					fdiv // r0 = r1 / r0
					fld1 // {{ r0 = atan( r0 )
					fpatan // }}
			} // returns r0

	#else

			return float( asin( r ) );

	#endif

		}

		//////////////////////////////////////////////////////////////////////////
		inline float asm_arctan( float r ) {

	#if VGES_USE_ASM_MATH == 1

			__asm {
				fld r // r0 = r
					fld1 // {{ r0 = atan( r0 )
					fpatan // }}
			} // returns r0

	#else

			return float( atan( r ) );

	#endif

		}

		//////////////////////////////////////////////////////////////////////////
		inline float asm_sin( float r ) {

	#if VGES_USE_ASM_MATH == 1

			__asm {
				fld r // r0 = r
					fsin // r0 = sinf( r0 )
			} // returns r0

	#else

			return sin( r );

	#endif

		}

		//////////////////////////////////////////////////////////////////////////
		inline float asm_cos( float r ) {

	#if VGES_USE_ASM_MATH == 1

			__asm {
				fld r // r0 = r
					fcos // r0 = cosf( r0 )
			} // returns r0

	#else

			return cos( r );

	#endif
		}

		//////////////////////////////////////////////////////////////////////////
		inline float asm_tan( float r ) {

	#if VGES_USE_ASM_MATH == 1

			// return sin( r ) / cos( r );
			//__asm {
			//	fld r // r0 = r
			//		fsin // r0 = sinf( r0 )
			//		fld r // r1 = r0, r0 = r
			//		fcos // r0 = cosf( r0 )
			//		fdiv // r0 = r1 / r0
			//} // returns r0

			/// 李文添加
			_asm
			{
				fld r		// load r
				fptan		// tan function
				fstp ST(0)	// pop stack
			} 
	#else

			return tan( r );

	#endif
		}

		//////////////////////////////////////////////////////////////////////////
		// returns a for a * a = r
		inline float asm_sqrt( float r )
		{
	#if VGES_USE_ASM_MATH == 1

			__asm {
				fld r // r0 = r
					fsqrt // r0 = sqrtf( r0 )
			} // returns r0

	#else

			return sqrt( r );

	#endif
		}

		//////////////////////////////////////////////////////////////////////////
		// returns 1 / a for a * a = r
		// -- Use this for Vector normalisation!!!
		inline float asm_rsq( float r )
		{
	#if VGES_USE_ASM_MATH == 1

			__asm {
				fld1 // r0 = 1.f
					fld r // r1 = r0, r0 = r
					fsqrt // r0 = sqrtf( r0 )
					fdiv // r0 = r1 / r0
			} // returns r0

	#else

			return 1. / sqrt( r );

	#endif
		}

		//////////////////////////////////////////////////////////////////////////
		// returns 1 / a for a * a = r
		// Another version
		inline float apx_rsq( float r ) {

	#if VGES_USE_ASM_MATH == 1

			const float asm_dot5 = 0.5f;
			const float asm_1dot5 = 1.5f;

			__asm {
				fld r // r0 = r
					fmul asm_dot5 // r0 = r0 * .5f
					mov eax, r // eax = r
					shr eax, 0x1 // eax = eax >> 1
					neg eax // eax = -eax
					add eax, 0x5F400000 // eax = eax & MAGICAL NUMBER
					mov r, eax // r = eax
					fmul r // r0 = r0 * r
					fmul r // r0 = r0 * r
					fsubr asm_1dot5 // r0 = 1.5f - r0
					fmul r // r0 = r0 * r
			} // returns r0

	#else

			return 1. / sqrt( r );

	#endif
		}

		//////////////////////////////////////////////////////////////////////////
		// returns a random number
		inline float asm_rand()
		{

	#if VGES_USE_ASM_MATH == 1
	#if 0
	#if OGRE_COMP_VER >= 1300

			static unsigned __int64 q = time( NULL );

			_asm {
				movq mm0, q

					// do the magic MMX thing
					pshufw mm1, mm0, 0x1E
					paddd mm0, mm1

					// move to integer memory location and free MMX
					movq q, mm0
					emms
			}

			return float( q );
	#endif
	#else
			// VC6 does not support pshufw
			return float( rand() );
	#endif
	#else
			// GCC etc

			return float( rand() );

	#endif
		}

		//////////////////////////////////////////////////////////////////////////
		// returns the maximum random number
		inline float asm_rand_max()
		{

	#if VGES_USE_ASM_MATH == 1
	#if 0
	#if OGRE_COMP_VER >= 1300

			return std::numeric_limits< unsigned __int64 >::max();
			return 9223372036854775807.0f;
	#endif
	#else
			// VC6 does not support unsigned __int64
			return float( RAND_MAX );
	#endif

	#else
			// GCC etc
			return float( RAND_MAX );

	#endif
		}

		// returns log2( r ) / log2( e )
		inline float asm_ln( float r ) {    

	#if VGES_USE_ASM_MATH == 1

			/*
			const float asm_e = 2.71828182846f;
			const float asm_1_div_log2_e = .693147180559f;
			const float asm_neg1_div_3 = -.33333333333333333333333333333f;
			const float asm_neg2_div_3 = -.66666666666666666666666666667f;
			const float asm_2 = 2.f;

			int log_2 = 0;

			__asm {
				// log_2 = ( ( r >> 0x17 ) & 0xFF ) - 0x80;
				mov eax, r
					sar eax, 0x17
					and eax, 0xFF
					sub eax, 0x80
					mov log_2, eax

					// r = ( r & 0x807fffff ) + 0x3f800000;
					mov ebx, r
					and ebx, 0x807FFFFF
					add ebx, 0x3F800000
					mov r, ebx

					// r = ( asm_neg1_div_3 * r + asm_2 ) * r + asm_neg2_div_3;   // (1)
					fld r
					fmul asm_neg1_div_3
					fadd asm_2
					fmul r
					fadd asm_neg2_div_3
					fild log_2
					fadd
					fmul asm_1_div_log2_e
			}

			*/

			// 李文添加
			_asm 
			{
				fld1		// load +1.0
					fldl2e		// load log2( e )
					fdiv		// r0 = 1.0 / r0 

					fld r		// load r
					fyl2x		// r0 = log2( r ) / log2( e )
			}

	#else

			return log( r );

	#endif
		}

}

#endif // end of __VGFASMMATH_H__