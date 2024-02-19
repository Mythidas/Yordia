include "dependencies.lua"

project "Yortek"
  kind "StaticLib"
  language "C++"
  cppdialect "C++latest"
  staticruntime "off"

  targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
  objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

  files
  {
    "include/**.h",
    "src/**.cpp"
  }

  defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
    "YAML_CPP_STATIC_DEFINE",
	}

  includedirs
  {
    "include",
    "%{IncludeDir.SPD}",
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.GLAD}",
    "%{IncludeDir.STB}",
    "%{IncludeDir.GLM}",
    "%{IncludeDir.IMGUI}",
    "%{IncludeDir.YAML_CPP}"
  }

  links
  {
    "GLFW",
    "Glad",
    "ImGui",
    "yaml-cpp",
    "OpenGL32.lib"
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