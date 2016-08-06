#include <ZR/GUI/GUINode.h>

namespace zr
{
	GUINode::GUINode()
	{	

	}

	GUINode::~GUINode()
	{

	}

	sf::Vector2f GUINode::getCoords(std::string str)
	{
		std::string s(str);
		s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
		for (int i = 0; i < s.length(); i++)
		{
			if (isupper(s[i]))
				s[i] = tolower(s[i]);
		}
		s.erase(std::remove(s.begin(), s.end(), '('), s.end());
		s.erase(std::remove(s.begin(), s.end(), ')'), s.end());
		return sf::Vector2f({std::stof(s.substr(0,s.find(','))),std::stof(s.substr(s.find(',')+1))});
	}
}
