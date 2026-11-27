#pragma once

#include <iostream>

#include <type_traits>
#include <typeinfo>
#include <string>
#include <vector>

namespace Engine
{
	//Engine console used for debugging.
	class Console
	{

	public:
		Console();
		~Console();

		Console(const Console&) = delete;
		Console& operator=(const Console&) = delete;

		static Console& Get();

		template<typename T>
		struct is_vector : std::false_type {};

		template<typename T, typename Alloc>
		struct is_vector<std::vector<T, Alloc>> : std::true_type {};

		// Writes supported values to the console.
		template<typename T>
		void Log(const T& content)
		{
			if constexpr (std::is_same_v<T, short> || std::is_same_v<T, int>)
			{
				std::cout << content << "\n";
			}
			else if constexpr (std::is_same_v<T, bool>)
			{
				std::cout << std::boolalpha << content << "\n";
			}
			else if constexpr (std::is_same_v<T, float> || std::is_same_v<T, double>)
			{
				std::cout << content << "\n";
			}
			// If content can be implicitly converted into std::string
			else if constexpr (std::is_convertible_v<const T&, std::string>)
			{
				std::cout << content << "\n";
			}
			else if constexpr (is_vector<T>::value)
			{
				std::cout << "[";

				for (size_t i = 0; i < content.size(); ++i)
				{
					if (i > 0)
						std::cout << ", ";

					std::cout << content[i];
				}

				std::cout << "]\n";
			}
			else
			{
				Warning("Trying to log unsupported type: " + std::string(typeid(T).name()));
			}
		}

		//Writes warnings to the console.
		void Warning(const std::string& input);
		//Writes errors to the console.
		void Error(const std::string& input);
		//Writes system messages to the console.
		void System(const std::string& input);

	private:
		std::string colorDefaultLB = "\033[0m\n";
		std::string colorEngine = "\033[36m";
		std::string colorWarning = "\033[33m";
		std::string colorError = "\033[31m";
	};
}