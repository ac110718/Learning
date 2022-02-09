#include <iostream>
#include <filesystem>

using namespace std;

int main() {
    //OS dependent parsing
    filesystem::path kernel32{ R"(/Windows/System32/kernel32.dll)" };
    cout << "Root name: " << kernel32.root_name()
         << "\nRoot directory: " << kernel32.root_directory()
         << "\nRoot path: " << kernel32.root_path()
         << "\nRelative path: " << kernel32.relative_path()
         << "\nParent path: " << kernel32.parent_path()
         << "\nFilename: " << kernel32.filename()
         << "\nStem: " << kernel32.stem()
         << "\nExtension: " << kernel32.extension()
         << endl;
    cout << kernel32 << endl;
    kernel32.make_preferred();
    cout << kernel32 << endl;
    kernel32.replace_filename("win32kfull.sys");
    cout << kernel32 << endl;
    kernel32.remove_filename();
    cout << kernel32 << endl;
    kernel32.clear();
    cout << "Is empty: " << boolalpha << kernel32.empty() << endl;
}