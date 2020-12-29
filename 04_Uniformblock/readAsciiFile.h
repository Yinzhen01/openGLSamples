#include <string>
#include <fstream>
#include <sstream>

std::string ReadAsciiFile(std::string filename)
{
  std::stringstream strStream;
  std::ifstream ifile(filename);
  
  strStream << ifile.rdbuf();
  return strStream.str();
}
