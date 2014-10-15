
#include <vgStableHeaders.h>

#include <vgTex/tvgStringUtil.h>


namespace vgCore {
	
	
	//----------------------------------------------------------------
	void StringUtil::trim( String& str, bool left /*= true*/,
		bool right /*= true */, const String& delstr /*= " \t\r"*/ )
	{
		//assert(str.length() != 0 );
		//static const String delims = " \t\r";
		if(right)
			str.erase(str.find_last_not_of(delstr)+1); // trim right
		if(left)
			str.erase(0, str.find_first_not_of(delstr)); // trim left
	}
	//----------------------------------------------------------------
	void StringUtil::toLowerCase( String& str )
	{
		std::transform(
			str.begin(),
			str.end(),
			str.begin(),
			tolower);
	}
	//----------------------------------------------------------------
	void StringUtil::toUpperCase( String& str )
	{
		transform( str.begin() , str.end() , str.begin() , toupper);
	}
	//----------------------------------------------------------------
	void StringUtil::splitFilename( const String& qualifiedName, 
		String& outBasename, String& outPath )
	{
		String path = qualifiedName;
		// Replace \ with / first
		std::replace( path.begin(), path.end(), '\\', '/' );
		// split based on final /
		size_t i = path.find_last_of('/');

		if (i == String::npos)
		{
			outPath = "";
			outBasename = qualifiedName;
		}
		else
		{
			outBasename = path.substr(i+1, path.size() - i - 1);
			outPath = path.substr(0, i+1);
		}

	}
	//----------------------------------------------------------------
	bool StringUtil::match( const String& str, const String& pattern, 
		bool caseSensitive /*= true*/ )
	{
		String tmpStr = str;
		String tmpPattern = pattern;
		if (!caseSensitive)
		{
			StringUtil::toLowerCase(tmpStr);
			StringUtil::toLowerCase(tmpPattern);
		}

		String::const_iterator strIt = tmpStr.begin();
		String::const_iterator patIt = tmpPattern.begin();
		String::const_iterator lastWildCardIt = tmpPattern.end();
		while (strIt != tmpStr.end() && patIt != tmpPattern.end())
		{
			if (*patIt == '*')
			{
				lastWildCardIt = patIt;
				// Skip over looking for next character
				++patIt;
				if (patIt == tmpPattern.end())
				{
					// Skip right to the end since * matches the entire rest of the string
					strIt = tmpStr.end();
				}
				else
				{
					// scan until we find next pattern character
					while(strIt != tmpStr.end() && *strIt != *patIt)
						++strIt;
				}
			}
			else
			{
				if (*patIt != *strIt)
				{
					if (lastWildCardIt != tmpPattern.end())
					{
						// The last wildcard can match this incorrect sequence
						// rewind pattern to wildcard and keep searching
						patIt = lastWildCardIt;
						lastWildCardIt = tmpPattern.end();
					}
					else
					{
						// no wildwards left
						return false;
					}
				}
				else
				{
					++patIt;
					++strIt;
				}
			}

		}
		// If we reached the end of both the pattern and the string, we succeeded
		if (patIt == tmpPattern.end() && strIt == tmpStr.end())
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	//----------------------------------------------------------------


}// end of namespace
