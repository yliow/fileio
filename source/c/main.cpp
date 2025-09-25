/*
  http://courses.cs.vt.edu/~cs2604/fall00/binio.html


  File object:
  - throw exception when open fails.
  - size() returns file size (in bytes ... what is the type? unsigned long long?)
 */

#include <iostream>
#include <fstream>
#include <sys/stat.h>

class FileOpenError{};
class FileSizeError{};

class FileData
{
public:
    unsigned char * data_;
    unsigned int size_;
    unsigned int capacity_; // ?? unsigned long long??
    FileData(int size)
        : data_(new unsigned char[size]), capacity_(size), size_(0)
    {}
    ~FileData()
    {
        delete [] data_;
    }
};

class File
{
public:
    std::fstream file_;
    unsigned int blocksize_; // maximum number of bytes per read/write
    std::string path_;
    FileData data;

    File(const std::string & path="", unsigned int blocksize=1024)
        : path_(path), blocksize_(blocksize), data(blocksize)
    {}
    
    std::string & path() { return path_; }
    
    void open(const std::string & path)
    {
        // Warning: does not check is file is opened
        path_ = path;
        file_.open(path_.c_str(),
                   std::ios::in | std::ios::out | std::ios::binary);
        if (!file_.is_open()) throw FileOpenError();
    }
    void close() { file_.close(); }

    static off_t size(const std::string & path) 
    {
        struct stat results;
        
        if (stat(path.c_str(), &results) == 0)
        {
            return results.st_size;
        }
        else
        {
            throw FileSizeError();
        }
    }

    // Read
    void read(int i)
    {
        
    }

    // Write
    void write()
    {
    }
};



void test()
{
    std::cout << "Test open ... ";
    try
    {
        File f;
        f.open("main.cpp");
        std::cout << "pass" << std::endl;
    }
    catch (FileOpenError & e)
    { std::cout << "FAIL!" << std::endl; }
    
    std::cout << "Test open ... ";
    try
    {
        File f;
        f.open("main12423453.cpp");
        std::cout << "FAIL!" << std::endl;
    }
    catch (FileOpenError & e)
    { std::cout << "pass" << std::endl; }

    std::cout << "Test size ... ";
    try
    {
        File::size("asdasdasd");
        std::cout << "FAIL!" << std::endl;
    }
    catch (FileSizeError & e)
    { std::cout << "pass" << std::endl; }
    
    std::cout << "Test size ... ";
    try
    {
        off_t size = File::size("test.txt");
        std::cout << (size == 16 ? "pass" : "FAIL!") << std::endl;
    }
    catch (FileSizeError & e)
    { std::cout << "FAIL!" << std::endl; }
}


int main()
{
    test();
    return 0;
}
