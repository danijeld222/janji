project "App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"

   files { "Source/**.h", "Source/**.cpp" }

   links
   {
      "Core",
      "SDL3",
      "SDL3_Image",
      "SDL3_Mixer",
      "SDL3_TTF"
   }
   
   includedirs
   {
      "../Core/Source",
      "../Core/Vendor/spdlog/include"
   }
   
    externalincludedirs
   {
      "../Core/Vendor/SDL3/include",
      "../Core/Vendor/SDL3_Image/include",
      "../Core/Vendor/SDL3_Mixer/include",
      "../Core/Vendor/SDL3_TTF/include"
   }
   
   libdirs
   {
      "../Core",
      "../Core/Vendor/SDL3/lib/%{cfg.architecture}",
      "../Core/Vendor/SDL3_Image/lib/%{cfg.architecture}",
      "../Core/Vendor/SDL3_Mixer/lib/%{cfg.architecture}",
      "../Core/Vendor/SDL3_TTF/lib/%{cfg.architecture}"
   }
   
   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       buildoptions "/MDd"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       buildoptions "/MD"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       buildoptions "/MD"
       symbols "Off"