#pragma once

#include "stdincludes.h"

class ConfigFile
{
public:
	ConfigFile(const char *filename)
	{
		std::ifstream in(filename);
		
		while(!in.eof())
		{
			char buffer[128];

			std::string key0, value0;
			std::string key, value;

			in.getline(buffer, 128, '\n');
			std::string str(buffer);
			int eqpos = str.find_first_of('=');
			key0 = std::string(&str[0], eqpos);
			eqpos++;
			value0 = std::string(&str[eqpos], str.length() - eqpos);

			//std::ostringstream kwseater(key0);
			//std::ostringstream vwseater(value0);
			//kwseater<<key;
			//vwseater<<value;
			
			map[key0] = value0;
		}
	}
	~ConfigFile(void)
	{
	}

	std::string GetString(char *key)
	{
		MIter i = map.find(key);
		if(i != map.end())
			return i->second;
		else
		{
			assert(false);
			return std::string();
		}
	}

	int GetInt(char *key)
	{
		std::string s = GetString(key);
		return atoi(s.c_str());
	}

	float GetFloat(char *key)
	{
		std::string s = GetString(key);
		return float(atof(s.c_str()));
	}

	typedef std::map<std::string, std::string> Map;
	typedef Map::iterator MIter;
	typedef Map::const_iterator CMIter;

	Map map;
};

