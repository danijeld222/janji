project "AppTest"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "Binaries/%{cfg.buildcfg}"
    staticruntime "on"
    
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
        "../Core/Vendor/spdlog/include",
        "../Core/Vendor/imgui",
        "../Core/Vendor/imgui/backends"
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
    
    postbuildcommands
    {
        "{COPYDIR} $(SolutionDir)%{prj.name}/DebugGraphics/*.* ../Binaries/" .. OutputDir .. "/%{prj.name}/DebugGraphics",
    }
    
    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS", "COREIMPORT" }
   
    filter "configurations:Debug"
        defines { "DEBUG", "COREIMPORT" }
        runtime "Debug"
        symbols "On"
   
    filter "configurations:Release"
        defines { "RELEASE", "COREIMPORT" }
        runtime "Release"
        optimize "On"
        symbols "On"
   
    filter "configurations:Dist"
        defines { "DIST", "COREIMPORT" }
        runtime "Release"
        optimize "On"
        symbols "Off"