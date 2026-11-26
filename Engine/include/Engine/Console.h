#pragma once

namespace Engine
{
	//Console class
	class Console
	{

	public:
		Console();
		~Console();

		void Log();
		void Warning();
		void WriteLine();
		void Write();
	};
}