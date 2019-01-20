#ifndef _SYSTEM_OS_HPP
#define _SYSTEM_OS_HPP
 
#include <iostream>
#include <cstdlib>
#include <limits>
 
#if (defined(_WIN) || defined(WIN) || defined(_WIN32) || defined (WIN32) || defined (_WIN64) || defined(WIN64))
    #define __OS_WINDOWS
#elif defined(__CYGWIN__)
    #define __OS_WINDOWS 
#elif defined(__ANDROID__)
    #define __OS_ANDROID
#elif defined(__linux__)
    #define __OS_LINUX
#elif defined(__APPLE__) || defined(__MACH__)
    #define __OS_MAC
#elif defined(__FreeBSD__)
    #define __OS_FREEBSD
#else
    #define __OS_UNKNOWN
#endif
 
namespace System {
namespace Os {
    
    /**
     * The operating system name
     */
    const std::string Platform
    #if defined(__OS_WINDOWS)
         = "Windows";
    #elif defined(__OS_ANDROID)
         = "Android";
    #elif defined(__OS_LINUX)
         = "Linux";
    #elif defined(__OS_MAC)
         = "MacOS";
    #elif defined( __OS_FREEBSD)
         = "Free BSD";
    #else
        = "Unknown";
    #endif
    
    /**
     * The bitness of the operating system (32, 64 ect)
     */
    const std::size_t Bitness = sizeof(int) * std::numeric_limits<unsigned char>::digits;
    
    /**
     * The current user
     */
    const std::string User
    #ifdef __OS_WINDOWS
         = std::getenv("USERNAME") ? std::getenv("USERNAME") : "";
    #else
         = std::getenv("USER") ? std::getenv("USER") : "";
    #endif
    
    /**
     * The name of the computer (not guaranteed)
     */
    const std::string ComputerName
    #ifdef __OS_WINDOWS
         = std::getenv("COMPUTERNAME") ?  std::getenv("COMPUTERNAME") : "";
    #else
         = std::getenv("HOSTNAME") ? std::getenv("HOSTNAME") : "";
    #endif
    
    /**
     * System independent line separation sequence
     */
     const std::string EOL
     #ifdef __OS_WINDOWS
          = "\r\n";
     #else
          = "\n";
     #endif

    /**
     * The name of the compiler used to compile this software
     */
    //const std::string CompilerName;
    /**
     * The version string for the compiler used to compile this software
     */
    //const std::string CompilerVersion;
    #if defined(__clang__)
        /* Clang/LLVM. ---------------------------------------------- */
        const std::string CompilerName = "Clang/LLVM";
        const std::string CompilerVersion = __clang_version__;
    #elif defined(__ICC) || defined(__INTEL_COMPILER)
        /* Intel ICC/ICPC. ------------------------------------------ */
        const std::string CompilerName = "Intel ICC/ICPC";
        const std::string CompilerVersion = __VERSION__;
    #elif defined(__GNUC__) || defined(__GNUG__)
        /* GNU GCC/G++. --------------------------------------------- */
        const std::string CompilerName = "GNU GCC/G++";
        const std::string CompilerVersion = __VERSION__;
    #elif defined(__HP_cc) || defined(__HP_aCC)
        /* Hewlett-Packard C/aC++. ---------------------------------- */
        const std::string CompilerName = "Hewlett-Packard C/aC++";
        const std::string CompilerVersion = __HP_aCC;
    #elif defined(__IBMC__) || defined(__IBMCPP__)
        /* IBM XL C/C++. -------------------------------------------- */
        const std::string CompilerName = "IBM XL C/C++";
        const std::string CompilerVersion = __xlc__;
    #elif defined(_MSC_VER)
        /* Microsoft Visual Studio. --------------------------------- */
        const std::string CompilerName = "Microsoft Visual Studio";
        const std::string CompilerVersion = std::to_string(_MSC_VER);
    #elif defined(__PGI)
        /* Portland Group PGCC/PGCPP. ------------------------------- */
        const std::string CompilerName = "Portland Group PGCC/PGCPP";
        const std::string CompilerVersion = __PGIC__"."__PGIC_MINOR__"."__PGIC_PATCHLEVEL__;
    #elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
        /* Oracle Solaris Studio. ----------------------------------- */
        const std::string CompilerName = "Oracle Solaris Studio";
        const std::string CompilerVersion = __SUNPRO_CC;
    #else
        const std::string CompilerName = "Unknown";
        const std::string CompilerVersion = "--";
    #endif
    
    /**
     * The name of the architecture this software is compiled for
     */
    const std::string Architecture
    #if defined(__ia64) || defined(__itanium__) || defined(_M_IA64)
         = "Intel IA64";
        #define __ARCH_IA64
    #elif defined(__powerpc__) || defined(__powerpc64__) || defined(__ppc__) || defined(__ppc64__) || defined(__PPC__) || defined(__PPC64__)
         = "PowerPC";
        #define __ARCH_POWERPC
   #elif defined(__sparc)
         = "SPARC";
        #define __ARCH_SPARC
    #elif defined(__s390__)
         = "SystemZ";
        #define __ARCH_SYSTEM_Z
    #elif defined(__sh__)
         = "SuperH";
        #define __ARCH SUPER_H
    #elif defined(__mips__) || defined(__MIPS__) || defined(__mips)
         = "MIPS";
        #define __ARCH_MIPS
    #elif defined(__BFIN__)
         = "Blackfin";
        #define __ARCH_BLACKFIN
    #elif defined(__convex__)
         = "Convex";
        #define __ARCH_CONVEX
    #elif defined(__epiphany__)
         = "Epiphany";
        #define __ARCH_EPIPHANY
    #elif defined(__hppa__) || defined(__HPPA__)
         = "HP/PA RISC";
        #define __ARCH_HP
    #elif defined(__aarch64__)
         = "ARM64";
        #define __ARCH_ARM64
    #elif defined(__arm__) || defined(_M_ARM)
         = "ARM";
        #define __ARCH_ARM
    #elif defined(__x86_64__) || defined(_M_X64)
         = "X86_64";
        #define __ARCH_X86_64
    #elif defined(__i386) || defined(_M_IX86)
         = "X86";
        #define __ARCH_X86
    #else
         = "Unknown";
        #define __ARCH_UNKNOWN
    #endif
    
    namespace Environment {
        /**
         * The value of the current PATH (not guaranteed)
         */
        const std::string Path = std::getenv("PATH") ? std::getenv("PATH") : "";
    }
    
    namespace Path {
        /**
         * The symbol used to separate directories in the filesystem
         */
        const std::string Separator
        #ifdef __OS_WINDOWS
             = "\\";
        #else
             = "/";
        #endif
        
        /**
         * The symbol used as a separator between paths in the PATH variable
         */
        const std::string Delimeter
        #ifdef __OS_WINDOWS
             = ";";
        #else
             = ":";
        #endif  
        
        /**
         * The symbol used to represent the root of the computer's file-system
         * C:\ in Windows and / in Unix or Linux environments
         */
        const std::string Root
        #ifdef __OS_WINDOWS
             =  std::getenv("HOMEDRIVE") ? std::getenv("HOMEDRIVE") : "C:\\";
        #else
             = "/";
        #endif
        
        /**
         * The symbol used to represent the directory where temp files are stored
         */
        const std::string Temp
        #ifdef __OS_WINDOWS
             = std::getenv("TEMP") ? std::getenv("TEMP") : "%TEMP%";
        #else
             = "/tmp";
        #endif
        
        /**
         * The symbol used to represent the directory where application data files are stored
         */
        const std::string AppData
        #if defined(__OS_WINDOWS)
             = std::getenv("APPDATA") ? std::getenv("APPDATA") : "%APPDATA%";
        #elif defined(__OS_MAC)
             = "~/Library/Application Support/";
        #else
             = "/var/lib";
        #endif
        
        /**
         * The symbol used to represent the directory where user files are stored
         */
        const std::string UserHome
        #ifdef __OS_WINDOWS
             = FileRoot + std::getenv("HOMEPATH") ? std::getenv("HOMEPATH") : "%HOMEPATH%";
        #else
             = (User == "" ? "~" : ("/home/" + User));
        #endif
    }
 
}
}
 
#endif