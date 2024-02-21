#include "Yortek/Tools/Path.h"
#include "Yortek/Debug/Log.h"

#include <fstream>
#include <Windows.h>
#include <ShlObj.h>

namespace Yortek::Tools
{
  Path::Path(const char* path)
    : m_path(path)
  {
  }

  Path::Path(const std::string& path)
    : m_path(path)
  {
  }

  Path::Path(const FS::path& path)
    : m_path(path)
  {
  }

  std::string Path::read_to_string() const
  {
    if (!exists() || !is_file()) return std::string();

    std::ifstream stream(m_path.c_str());
    if (!stream.is_open()) return std::string();

    std::stringstream buf;
    buf << stream.rdbuf();
    stream.close();
    return buf.str();
  }

  void Path::write(const std::string& str) const
  {
    if (!is_file()) return;

    std::ofstream fout(m_path);
    if (fout.is_open())
    {
      fout << str;
      fout.close();
    }
    else
    {
      Debug::Log::error("Failed to create file! {0}", to_string());
    }
  }

  bool Path::exists() const
  {
    return FS::exists(m_path);
  }

  bool Path::is_file() const
  {
    return !FS::is_directory(m_path);
  }
}