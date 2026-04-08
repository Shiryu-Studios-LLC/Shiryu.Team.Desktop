-- premake5.lua
workspace "Shiryu.Launcher"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Shiryu.Launcher"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Build-ShiryuTeam-External.lua"
include "ShiryuTeam.Launcher/Build-ShiryuTeam.Launcher.lua"