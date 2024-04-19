project "Core"
   kind "SharedLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "on"
   
   files
   {
      "Source/**.h",
      "Source/**.cpp",
      "Vendor/imgui/imconfig.h",
      "Vendor/imgui/imgui.cpp",
      "Vendor/imgui/imgui.h",
      "Vendor/imgui/imgui_demo.cpp",
      "Vendor/imgui/imgui_draw.cpp",
      "Vendor/imgui/imgui_internal.h",
      "Vendor/imgui/imgui_tables.cpp",
      "Vendor/imgui/imgui_widgets.cpp",
      "Vendor/imgui/imstb_rectpack.h",
      "Vendor/imgui/imstb_textedit.h",
      "Vendor/imgui/imstb_truetype.h",
      "Vendor/imgui/backends/imgui_impl_sdl3.cpp",
      "Vendor/imgui/backends/imgui_impl_sdl3.h",
      "Vendor/imgui/backends/imgui_impl_sdlrenderer3.cpp",
      "Vendor/imgui/backends/imgui_impl_sdlrenderer3.h",
   }
   
   includedirs
   {
      "Source",
      "Vendor/imgui/",
      "Vendor/imgui/backends"
   }
   
   externalincludedirs
   {
      "Vendor/SDL3/include",
      "Vendor/SDL3_Image/include",
      "Vendor/SDL3_Mixer/include",
      "Vendor/SDL3_TTF/include"
   }
   
   links
   {
      "SDL3",
      "SDL3_Image",
      "SDL3_Mixer",
      "SDL3_TTF"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "COREEXPORT" }
       libdirs
       {
          "Vendor/SDL3/lib/%{cfg.architecture}",
          "Vendor/SDL3_Image/lib/%{cfg.architecture}",
          "Vendor/SDL3_Mixer/lib/%{cfg.architecture}",
          "Vendor/SDL3_TTF/lib/%{cfg.architecture}"
       }
       postbuildcommands
       {
          "{COPY} ../Binaries/" .. OutputDir .. "/%{prj.name}/*.dll ../Binaries/" .. OutputDir .. "/App",
          "{COPY} ../Binaries/" .. OutputDir .. "/%{prj.name}/*.dll ../Binaries/" .. OutputDir .. "/AppTest",
          "{COPY} $(SolutionDir)%{prj.name}/Vendor/SDL3/lib/%{cfg.architecture}/SDL3.dll ../Binaries/" .. OutputDir .. "/App",
          "{COPY} $(SolutionDir)%{prj.name}/Vendor/SDL3/lib/%{cfg.architecture}/SDL3.dll ../Binaries/" .. OutputDir .. "/AppTest",
          "{COPY} $(SolutionDir)%{prj.name}/Vendor/SDL3_Image/lib/%{cfg.architecture}/SDL3_image.dll ../Binaries/" .. OutputDir .. "/App",
          "{COPY} $(SolutionDir)%{prj.name}/Vendor/SDL3_Image/lib/%{cfg.architecture}/SDL3_image.dll ../Binaries/" .. OutputDir .. "/AppTest",
          "{COPY} $(SolutionDir)%{prj.name}/Vendor/SDL3_Mixer/lib/%{cfg.architecture}/SDL3_mixer.dll ../Binaries/" .. OutputDir .. "/App",
          "{COPY} $(SolutionDir)%{prj.name}/Vendor/SDL3_Mixer/lib/%{cfg.architecture}/SDL3_mixer.dll ../Binaries/" .. OutputDir .. "/AppTest",
          "{COPY} $(SolutionDir)%{prj.name}/Vendor/SDL3_TTF/lib/%{cfg.architecture}/SDL3_ttf.dll ../Binaries/" .. OutputDir .. "/App",
          "{COPY} $(SolutionDir)%{prj.name}/Vendor/SDL3_TTF/lib/%{cfg.architecture}/SDL3_ttf.dll ../Binaries/" .. OutputDir .. "/AppTest"
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