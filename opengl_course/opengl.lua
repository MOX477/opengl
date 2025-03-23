project "opengl"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"



    targetdir ("%{wks.location}/bin/%{cfg.buildcfg}-%{cfg.architecture}")
    objdir ("%{wks.location}/bin-int/%{cfg.platform}/%{cfg.buildcfg}")


    files {"**.h","**.cpp",
        "src/**.cpp","src/**.h",
        "headers/**.h","headers/**.cpp",
        "implementation/**.h","implementation/**.cpp"}

    includedirs {
        "headers",
        "../ThirdParty/GLFW/include",
        "../ThirdParty/GLEW/include",
        "../ThirdParty/GLM"}

    libdirs {
        "../ThirdParty/GLEW/lib/Release\\x64",
        "../ThirdParty/GLFW/lib"
    }

    links {"opengl32.lib","glfw3.lib","glew32s.lib"}

    function clear()
        print("Cleaning build directories...")
    
        -- Remove build output directories
        os.rmdir("bin")
        os.rmdir("bin-int")
        os.rmdir(".vs")  -- Remove Visual Studio folder
    
        -- Remove Visual Studio solution and project files
        os.remove("*.sln")              -- Remove solution files
        os.remove("**.vcxproj")         -- Remove Visual Studio project files
        os.remove("**.vcxproj.filters") -- Remove project filters
        os.remove("**.vcxproj.user")    -- Remove user settings
    
        print("Clean complete.")
    end
    
    newaction {
        trigger = "clear",
        description = "Removes all build files,",
        execute = clear
    }
    
    

    filter "configurations:Debug"
        symbols "On"
    

    filter "configurations:Release"
        optimize "On"

    
        
        