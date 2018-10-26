#ifndef CLASSGEN_H
#define CLASSGEN_H

#include <tclap/CmdLine.h>

class ClassGen 
{
public:
	ClassGen(int argc, char** argv);
	~ClassGen();

private:
	std::string mClassName, mFileName;
	
	std::string getCpp() const;
	std::string getH() const;
	
	static std::string getHeader(const std::string &n);
	static bool checkName(const std::string &n);
	
};

#endif // CLASSGEN_H
