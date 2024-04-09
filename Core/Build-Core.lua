project "Core"
   kind "SharedLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "on"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "COREEXPORT" }
       postbuildcommands
       {
          "{COPY} ../Binaries/" .. OutputDir .. "/%{prj.name}/*.dll ../Binaries/" .. OutputDir .. "/App",
          "{COPY} ../Binaries/" .. OutputDir .. "/%{prj.name}/*.dll ../Binaries/" .. OutputDir .. "/AppTest"
       }

   filter "configurations:Debug"
       defines { "DEBUG", "COREEXPORT" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE", "COREEXPORT" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST", "COREEXPORT" }
       runtime "Release"
       optimize "On"
       symbols "Off"