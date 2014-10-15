


#include <vgStableHeaders.h>


namespace vgScript {
	
	
#if 0

	class World
	{
	public:
		World()
		{

		}

		~World()
		{

		}

		World( std::string str )
		{
			msg = str;
		}
		void set( const std::string& msg) 
		{ 
			this->msg = msg; 
		}

		std::string greet()
		{ 
			return msg; 
		}
		int getNum() const { return _num ;}

		void setNum( const int& num ) { _num = num ; }

	public:

		std::string name;

		std::string readonlyname;

	private:

		int _num;

		std::string msg;
	};



	char const* greet()
	{
		return "hello, world";
	}

	void show( const String& msg)
	{
		VGK_SHOW( msg );
	}


	BOOST_PYTHON_MODULE(hello)
	{
		using namespace boost::python;
		def("greet", greet );
		def( "show" , show );
		class_<World>("World")
			.def( init<std::string>() )
			.def("greet", &World::greet)
			.def("set", &World::set)
			.def_readwrite( "name" , &World::name )
			.def_readonly( "readonlyname", &World::readonlyname)
			.add_property("num", &World::getNum, &World::setNum);
		;
	}

	void registerScriptModule_hello()
	{
		inithello();
	}

#endif
	
}// end of namespace vgScript
