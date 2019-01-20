#include "System.Io.Path.hpp"
#include "System.Os.hpp"

#include <iostream>

namespace System {
namespace Io {

Path::Path() : Path(Path::CurrentDirectory()) {}

Path::Path(const System::Text::String& pathlike): device(), root(), name(), ext(){
    /*
    // Regex to split a windows path into three parts: [*, device, slash,
    // tail] windows-only
    var splitDeviceRe =
        /^([a-zA-Z]:|[\\\/]{2}[^\\\/]+[\\\/]+[^\\\/]+)?([\\\/])?([\s\S]*?)$/;

    // Regex to split the tail part of the above into [*, dir, basename, ext]
    var splitTailRe =
        /^([\s\S]*?)((?:\.{1,2}|[^\\\/]+?|)(\.[^.\/\\]*|))(?:[\\\/]*)$/;


    function win32SplitPath(filename) {
        // Separate device+slash from tail C: ... not needed on posix
        var result = splitDeviceRe.exec(filename),
            device = (result[1] || '') + (result[2] || ''),
            tail = result[3] || '';
        // Split the tail into dir, basename and extension
        var result2 = splitTailRe.exec(tail),
            dir = result2[1],
            basename = result2[2],
            ext = result2[3];
        return [device, dir, basename, ext];
    }
    */
    //Parse Path

}

Path::Path(const Path& other): device(other.device), root(other.root), name(other.name), ext(other.ext) {}

Path::~Path() {}

System::Text::String  Path::GetDeviceName () {
    return this->device;
}

System::Text::String Path::GetExtension() {
    return this->ext;
}

System::Text::String Path::GetName() {
    return this->name;
}

System::Text::String Path::GetFullName() {
    return this->name + '.' + this->ext;
}

System::Text::String Path::GetFullPath() {
    return this->root + System::Os::Path::Separator + this->name + '.' + this->ext;
}

#ifdef __OS_WINDOWS
    #include <direct.h>
    #define __OP_GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define __OP_GetCurrentDir getcwd
#endif
Path Path::CurrentDirectory() {
    char buff[FILENAME_MAX];
    __OP_GetCurrentDir( buff, FILENAME_MAX );
    return Path(System::Text::String(buff));
}
#undef __OP_GetCurrentDir

}
}