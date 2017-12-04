#include "file_channel.h"

#include <fcntl.h>
#include <unistd.h>
#include <string>

NAMESPACE_BEGIN(Kit)

FileChannel::FileChannel(const std::string &file_path) :
    file_path_(file_path), fd_(0)
{    
}

FileChannel::~FileChannel()
{
    Close();
}

bool FileChannel::Open()
{
    if (fd_ == 0)
    {
        fd_ = open(file_path_.c_str(), O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
        return fd_ != 0;
    }
    else
    {
        return true;
    }
}

void FileChannel::Close()
{
    if (fd_ != 0)
    {
        close(fd_);
        fd_ = 0;
    }
}

void FileChannel::DumpMessage(const std::string &msg)
{
    if (fd_ != 0)
    {
        write(fd_, msg.data(), msg.size());
        write(fd_, "\n", 1);
    }
}

NAMESPACE_END(Kit)
