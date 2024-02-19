include "dependencies.lua"

workspace "Yor"
  architecture "x64"
  startproject "Yordia"

  configurations
  {
    "Debug",
    "Release",
    "Dist"
  }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
  include "vendor/GLFW"
  include "vendor/glad"
  include "vendor/imgui"
  include "vendor/yaml-cpp"
group ""

group "Core"
  include "Yortek"
group ""

group "Tools"
group ""

group "Game"
  include "Yordia"
group ""