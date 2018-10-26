#include "classGen.h"
#include <algorithm>
#include <iostream>
#include <fstream>

ClassGen::ClassGen(int argc, char** argv) {
	TCLAP::CmdLine cmd("Class generator");
	TCLAP::ValueArg<std::string> arg_file("f", "file", "Specify file name so that it is different from class name", false, "", "string");
    cmd.add(arg_file);
    TCLAP::SwitchArg arg_display("d", "display", "Display the content instead of writing into a file");
	cmd.add(arg_display);;
    TCLAP::UnlabeledMultiArg<std::string> arg_multi("Name", "Class name and "
    "optionaly destination path for writing", true, "string");
	cmd.add( arg_multi );
	cmd.parse(argc, argv);
	
	std::vector<std::string> multi(arg_multi.getValue());
	std::string path;
	size_t sz(multi.size());
	// CHECKING 
	if(sz < 1)
		throw std::string("You must specify the name of the class");
	if(!checkName(multi[0]))
		throw std::string("The class name is invalid");
	mClassName = multi[0];
	if(sz > 1) {
		path = multi[1];
		if(path.find('/') == std::string::npos)
			throw std::string("The second argument should be a folder");
	}
	std::string f(arg_file.getValue());
	if(f == "")		mFileName = mClassName;
	else 			mFileName = f;
	
	std::string cpp(getCpp()), hpp(getH());
	if(arg_display.getValue()) {
		std::cout << "******************** "<<mFileName<<".cpp **********\n"<<cpp;
		std::cout << "\n******************** "<<mFileName<<".h   **********\n"<<hpp<<"\n";
	} else {
		std::string fNameH(path+mFileName+".h"), fNameCpp(path+mFileName+".cpp");
		// TESTING is files already exist (no oveririting)
		if(std::ifstream(fNameH).good())
			throw std::string("'"+fNameH+"' already exists");
		if(std::ifstream(fNameCpp).good())
			throw std::string("'"+fNameCpp+"' already exists");
		// OUTPUT file stream
		std::ofstream output;
		output.open(fNameH);
		if(!output.is_open())
			throw std::string("Cannot create '"+fNameH+"'. Nothing has been written.");
		output << hpp;
		output.close();
		output.open(fNameCpp);
		if(!output.is_open())
			throw std::string("Cannot create '"+fNameCpp+"'. '"+fNameH+"' has been written.");
		output << cpp;
		output.close();
	}
}

ClassGen::~ClassGen() {
	
}

std::string ClassGen::getCpp() const {
	std::string s;
	s += "#include \""+mFileName+".h\"";
	s += "\n\n" + mClassName + "::" + mClassName + "() {\n\t\n}";
	s += "\n\n" + mClassName + "::~" + mClassName + "() {\n\t\n}";
	s += "\n\n";
	
	return s;
}

std::string ClassGen::getH() const {
	std::string s, h(getHeader(mClassName));
	s += "#ifndef " + h + "\n#define " + h;
	s += "\n\nclass " + mClassName + " {\n\n";
	s += "public:\n\t" + mClassName + "();\n\t~"+mClassName+"();";
	s += "\n\nprivate:\n\t";
	
	s += "\n};\n\n#endif // " + h + "\n\n";
	
	return s;
}

// STATIC
bool ClassGen::checkName(const  std::string &n) {
	
	return true;
}
	
std::string ClassGen::getHeader(const  std::string &n) {
	std::string s;
	for(char c : n)
		s += toupper(c);
	s += "_H";
	return s;
}





