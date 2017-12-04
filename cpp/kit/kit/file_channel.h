#ifndef __KIT_FILE_CHANNEL_H__
#define __KIT_FILE_CHANNEL_H__

#include "utility.h"
#include "channel.h"

NAMESPACE_BEGIN(Kit)

class FileChannel : public Channel
{
public:
    explicit FileChannel(const std::string &file_path);
    virtual ~FileChannel();
    
public:
    virtual bool Open();
    virtual void Close();
    virtual void DumpMessage(const std::string &msg);
    
private:
    const std::string file_path_;
    int               fd_;
};

NAMESPACE_END(Kit)

#endif /* __KIT_FILE_CHANNEL_H__ */
