-- premake5.lua
workspace "JanjiProject"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }
    flags { "MultiProcessorCompile" }
    startproject "AppTest"
    
    -- Workspace-wide build options for MSVC
    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }
    
OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
    
include "Core/Vendor/glad"
    
group "Core"
    include "Core/Build-Core.lua"
group ""
    
include "App/Build-App.lua"
include "AppTest/Build-AppTest.lua"