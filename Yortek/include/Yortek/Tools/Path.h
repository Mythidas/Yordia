#pragma once

#include <filesystem>

namespace Yortek::Tools
{
  namespace FS = std::filesystem;

  class Path
  {
  public:
    Path() = default;
    Path(const char* path);
    Path(const std::string& path);
    Path(const FS::path& path);

    std::string read_to_string() const;
    void write(const std::string& str) const;

    bool exists() const;
    bool is_file() const;
    std::string extension() const { return m_path.extension().string(); }
    std::string name() const { return m_path.filename().string(); }

    std::string to_string() const { return m_path.string(); }
    std::wstring to_wstring() const { return m_path.wstring(); }

  public:
    Path operator+(const Path& rhs) const
    {
      return m_path.string() + rhs.to_string();
    }

  private:
    FS::path m_path;
  };
}