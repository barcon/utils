-- premake5.lua
workspace "utils"
   configurations { "Debug", "Release" }
   location "build"

project "utils"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   
   targetdir "build/%{cfg.buildcfg}"

   files { "src/**.cpp" }
   includedirs { "src" }

   filter "configurations:Debug"
      architecture "x86_64"     
	  defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      architecture "x86_64"     
	  defines { "NDEBUG" }
      optimize "Speed"