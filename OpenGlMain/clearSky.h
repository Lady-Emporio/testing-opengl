#pragma once

#include <iostream>
#include <string>

namespace Twilight
{
	inline void log(const char * text, const char * type="") {
		if (type != "") {
			std::cout << text << "|" << type << std::endl;
		}
		else {
			std::cout << text << std::endl;
		}
		
	}
	inline  void Error(const char * text, const char * type="") {
		log(text,type);
		system("pause");
		//exit(1);
	}
}