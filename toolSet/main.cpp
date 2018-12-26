#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

#define _BOOST_STR1(s, aug1)             boost::str(boost::format(s) % (aug1))
#define _BOOST_STR2(s, aug1, aug2)       boost::str(boost::format(s) % (aug1) % (aug2))
#define _BOOST_STR3(s, aug1, aug2, aug3) boost::str(boost::format(s) % (aug1) % (aug2) % (aug3))

using namespace std;

static bool replaceFileString(ifstream &instream, ofstream &outstream, const std::string& srcStr, const std::string& dstStr)
{
	string str;
	size_t pos = 0;
	while (getline(instream, str))
	{
		pos = str.find(srcStr);
		if (pos != string::npos)
		{
			str = str.replace(pos, srcStr.length(), dstStr);
			outstream << str << endl;
			continue;
		}
		outstream << str << endl;
	}
	return true;
}

static void createProjectFromTemplate(const std::string& vProjectPath, const std::string& vProjectName)
{
	_ASSERTE(!vProjectPath.empty() && !vProjectName.empty());

	system(_BOOST_STR1("echo d | xcopy ..\\templateProject %1% /e", vProjectPath).c_str());
	system(_BOOST_STR2("ren %1%\\templateProject.vcxproj.filters	%2%.vcxproj.filters", vProjectPath, vProjectName).c_str());
	system(_BOOST_STR2("ren %1%\\templateProject.vcxproj.user		%2%.vcxproj.user", vProjectPath, vProjectName).c_str());

	ifstream inStream(_BOOST_STR1("%1%\\templateProject.vcxproj", vProjectPath));
	ofstream outStream(_BOOST_STR2("%1%\\%2%.vcxproj", vProjectPath, vProjectName));
	replaceFileString(inStream, outStream, "templateProject", vProjectName);
	inStream.close();
	outStream.close();

	system(_BOOST_STR1("del %1%\\templateProject.vcxproj", vProjectPath).c_str());
}

int main(int vArgc, char** vArgv)
{
	if (vArgc < 2) return -1;

	switch (atoi(vArgv[1]))
	{
	case 1:
		createProjectFromTemplate(vArgv[2], vArgv[3]);
		break;
	}

	system("pause");

	return 0;
}