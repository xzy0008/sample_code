// ContourValues.cpp: implementation of the ContourValues class.
//
//////////////////////////////////////////////////////////////////////


#include <vgStableHeaders.h>
#include <vgGIS3D\vggiContourValues.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace vgGIS3D
{
	ContourValues::ContourValues()
	{
		m_Values.RemoveAll();
	}

	ContourValues::~ContourValues()
	{
	}

	ContourValues& ContourValues::operator=(const ContourValues& rhs)
	{
		m_Values.RemoveAll();

		POSITION pos = rhs.m_Values.GetHeadPosition();

		while(pos!=NULL)
		{
			m_Values.AddTail(rhs.m_Values.GetNext(pos));
		}

		return *this;

	}

	void ContourValues::AddValue(float newValue)
	{//按从小到大插入，插入后保证有序

		if( m_Values.IsEmpty() )
		{
			m_Values.AddTail(newValue);
		}
		else
		{
			float val; 
			POSITION pos = m_Values.GetHeadPosition();
			val = m_Values.GetAt(pos);
			if( newValue < val )
			{
				m_Values.AddHead(newValue);
				//	TraceOutValueList();
				return;
			} 

			pos = m_Values.GetTailPosition();
			val = m_Values.GetAt(pos);
			if( newValue > val)
			{
				m_Values.AddTail(newValue);
				//TraceOutValueList();
				return;
			}

			POSITION nextPos = m_Values.GetHeadPosition();
			pos = nextPos;
			float valNext;
			while( nextPos!=NULL )
			{
				val = m_Values.GetNext(nextPos);
				if( val == newValue )
				{
					//TraceOutValueList();
					return;
				}

				ASSERT(nextPos!=NULL);
				valNext = m_Values.GetAt(nextPos);
				if( newValue == valNext )
				{
					//TraceOutValueList();
					return;
				}

				if( val< newValue && newValue < valNext )
				{
					m_Values.InsertAfter(pos,newValue);
					//TraceOutValueList();
					return;
				}

				pos = nextPos; //watch out here!


			}


		}


	}

	#ifdef _DEBUG
	void ContourValues::TraceOutValueList()
	{

		POSITION pos = m_Values.GetHeadPosition();
		float val;
		while(pos!=NULL)
		{
			val = m_Values.GetNext(pos);
			TRACE1("%f\n",val);

		}

	}
	#endif

	void ContourValues::DeleteValue(float oldValue)
	{
		POSITION pos = m_Values.GetHeadPosition();
		float val;
		while(pos!=NULL)
		{
			val = m_Values.GetAt(pos);
			if( abs(val - oldValue) < 1e-4 )
			{
				m_Values.RemoveAt(pos);
				return ;
			}
			m_Values.GetNext(pos);
		}

	}

	void ContourValues::ReplaceValue(float oldValue, float newValue)
	{
		POSITION pos = m_Values.GetHeadPosition();
		float val;
		while(pos!=NULL)
		{
			val = m_Values.GetAt(pos);
			if( val == oldValue )
			{
				m_Values.RemoveAt(pos);
				AddValue(newValue);
			}
			m_Values.GetNext(pos);

		}

	}

	void ContourValues::GenerateValues(int numContours, float rangeStart, float rangeEnd)
	{
		float incr;

		if (numContours == 1)
		{
			incr = 0;
		}
		else
		{
			incr = (rangeEnd - rangeStart) / (numContours-1);
		}

		float val = rangeStart;
		for (int i=0; i < numContours; i++)
		{
			AddValue(val);
			val+=incr;
		}

	}

	float ContourValues::GetValue(int i)
	{
		ASSERT( i>=0 && i<GetNumberOfValues() );
			
		return m_Values.GetAt(m_Values.FindIndex(i));
	}

	void ContourValues::SetValue(int i, float newValue)
	{
		int numCoutr = GetNumberOfValues();
		ASSERT( i>=0 && i<numCoutr-1 );

		float val = GetValue(i);
		ReplaceValue(val,newValue);

	}
}






















