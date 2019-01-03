#ifndef _SYSTEM_IO_PATH_HPP
#define _SYSTEM_IO_PATH_HPP

#include "System.Text.String.hpp"
#include <iostream>
#include <vector>

namespace System {
namespace Io {

/**
 * Class representing a path on the filesystem. All operations are performed in a cross-platform manor. 
 */
class Path {
    private:
        System::Text::String device;
        System::Text::String root;
        System::Text::String name;
        System::Text::String ext;

    public:
        /**
         * Create a path to the current working directory 
         */
        Path();
        /**
         * Create a new path by parsing a string 
         */
        explicit Path(const System::Text::String& pathlike);
        /**
         * Copy an existing path 
         */
        Path(const Path& path);
        /**
         * Path destructor
         */
        ~Path();

        /**
         * Get the current working directory 
         */
        static Path CurrentDirectory();
        static Path RelativePath(const Path& from, const Path& to);

        System::Text::String GetDeviceName();
        System::Text::String GetExtension();
        System::Text::String GetName();
        System::Text::String GetFullName();
        System::Text::String GetFullPath();

        Path GetParent();
        std::vector<Path> GetChildren();

        Path& Join(const System::Text::String& next);
        Path& Join(const Path& next);

        void Normalize();

        bool IsDirectory();
        bool IsFile();
        bool Exists();
        bool HasExtension();
        bool IsAbsolute();
        bool IsRelative();

        bool IsReadable();
        bool IsWritable();

        bool MkDirs();
        bool Create();
        bool Delete();
        bool Rename(const System::Text::String& newName);
        size_t Size();

};
    
}
}

#endif