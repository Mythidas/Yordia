include "dependencies.lua"

project "Yordia"
  kind "ConsoleApp"
  location "src"
  language "C++"
  cppdialect "C++latest"
  staticruntime "off"

  targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
  objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

  files
  {
    "src/*.h",
    "src/*.cpp"
  }

  defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

  includedirs
  {
    "src",
    "%{wks.location}/Yortek/include",
    "%{IncludeDir.SPD}",
    "%{IncludeDir.GLM}",
  }

  links
  {
    "Yortek"
  }

  filter "system:windows"
    systemversion "latest"

    defines
    {
      "YOR_PLAT_WINDOWS",
    }

  filter "configurations:Debug"
    defines
    {
      "YOR_DEBUG",
    }
    symbols "On"
    runtime "Debug"

  filter "configurations:Release"
    defines "YOR_RELEASE"
    optimize "On"
    runtime "Release"

  filter "configurations:Dist"
    defines "YOR_DIST"
    optimize "On"
    runtime "Release"