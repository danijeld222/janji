project "AppTest"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"

   files { "Source/**.h", "Source/**.cpp" }

   links
   {
      "Core"
   }
   
   includedirs
   {
      "../Core/Source",
      "../Core/Vendor/spdlog/include"
   }
   
   libdirs
   {
      "../Core"
   }
   
   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS", "COREIMPORT" }

   filter "configurations:Debug"
       defines { "DEBUG", "COREIMPORT" }
       runtime "Debug"
       buildoptions "/MDd"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE", "COREIMPORT" }
       runtime "Release"
       optimize "On"
       buildoptions "/MD"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST", "COREIMPORT" }
       runtime "Release"
       optimize "On"
       buildoptions "/MD"
       symbols "Off"