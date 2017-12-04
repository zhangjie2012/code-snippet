#include <unistd.h>

#include <iostream>
#include <set>
#include <string>
#include <iterator>
#include <iomanip>

#include "kit/any.h"
#include "kit/assert.h"
#include "kit/date_time.h"
#include "kit/file_channel.h"
#include "kit/guid_gen.h"
#include "kit/logger.h"
#include "kit/mmap_data.h"
#include "kit/mmap_vector.h"
#include "kit/non_copyable.h"
#include "kit/thread.h"
#include "kit/random.h"
#include "kit/composite_key.h"
#include "kit/net_addr.h"

void InitApp()
{
    // Init log system
    Kit::FileChannel *file_channel = new Kit::FileChannel(std::string("log.txt"));
    Kit::Logger::Instance()->SetChannel(file_channel);
    Kit::Logger::Instance()->SetLev(Kit::LOG_LEV_DEBUG);
    Kit::LOG_DEBUG(0, "日志系统初始化");
}

void ClearApp()
{
    Kit::LOG_DEBUG(0, "关闭日志系统");
    if (auto c = Kit::Logger::Instance()->SetChannel(NULL))
    {
        delete c;
    }
}

struct Data
{
    int a;
    float b;
    double c;
};

int main(int argc, char *argv[])
{
    InitApp();
    KIT_SCORE_EXIT {
        ClearApp();
    } KIT_SCORE_END ;
    
    // {
    //     Kit::DateTime dt;
    //     std::cout << dt.sec() << std::endl;
    //     std::cout << dt.min() << std::endl;
    //     std::cout << dt.hour() << std::endl;
    //     std::cout << dt.wday() << std::endl;
    //     std::cout << dt.mday() << std::endl;
    //     std::cout << dt.yday() << std::endl;
    //     std::cout << dt.mon() << std::endl;
    //     std::cout << dt.year() << std::endl;
    //     std::cout << dt.Format() << std::endl;

    //     Kit::DateTime dt1(dt);
    //     std::cout << dt1.Format() << std::endl;

    //     Kit::DateTime dt2(dt.TimeStamp());
    //     std::cout << dt2.Format() << std::endl;
    //     dt2.Update();
    //     std::cout << dt2.Format() << std::endl;

    //     Kit::DateTime dt3;
    //     dt3.Parse("2015-01-02 10:10:10");
    //     std::cout << dt3.Format() << std::endl;
    //     dt3.Update();
    //     std::cout << dt3.Format() << std::endl;

    //     Kit::DateTime dt4(2015, 8, 25, 11, 20, 20, 500);
    //     std::cout << dt4.Format() << std::endl;
    //     dt4.Update();
    //     std::cout << dt4.Format() << std::endl;
    // }

    // {
    //     Kit::MMapData<struct Data> mmap_data;
    //     std::string file_name = "./test_mmap_data.mmap";
    //     mmap_data.Attach(file_name);
    //     mmap_data->a = 1;
    //     mmap_data->b = 1.0f;
    //     mmap_data->c = 2.0;
    // }
    // {
    //     Kit::MMapData<struct Data> mmap_data;
    //     std::string file_name = "./test_mmap_data.mmap";
    //     mmap_data.Attach(file_name);
    //     std::cout << mmap_data->a << std::endl;
    //     std::cout << mmap_data->b << std::endl;
    //     std::cout << mmap_data->c << std::endl;
    //     std::cout << mmap_data.MMapFileName() << std::endl;
    //     std::cout << mmap_data.Size() << std::endl;
    // }
    
    // {
    //     Kit::MMapVector<struct Data> mmap_vector;
    //     std::string file_name = "./test_mmap_vector.mmap";
    //     mmap_vector.Attach(file_name);
    //     std::cout << mmap_vector.Size() << std::endl;
    //     std::cout << mmap_vector.Capacity() << std::endl;
    //     mmap_vector.Resize(10);
        
    //     std::cout << mmap_vector.Size() << std::endl;
    //     std::cout << mmap_vector.Capacity() << std::endl;
    //     std::cout << mmap_vector.Empty() << std::endl;

    //     for (size_t i = 0; i < mmap_vector.Size(); ++i)
    //     {
    //         mmap_vector[i].a = i;
    //         mmap_vector[i].b= i * i;
    //         mmap_vector[i].c= i * i * i;
    //     }
        
    //     std::cout << mmap_vector.Size() << std::endl;
    //     std::cout << mmap_vector.Capacity() << std::endl;
    //     std::cout << mmap_vector.Empty() << std::endl;
        
    //     for (size_t i = 0; i < mmap_vector.Size(); ++i)
    //     {
    //         std::cout << mmap_vector[i].a
    //                   << mmap_vector[i].b
    //                   << mmap_vector[i].c
    //                   << std::endl;
    //     }
        
    //     struct Data data;
    //     data.a = 100;
    //     data.b = 100;
    //     data.c = 100;
    //     mmap_vector.PushBack(data);

    //     for (size_t i = 0; i < mmap_vector.Size(); ++i)
    //     {
    //         std::cout << mmap_vector[i].a
    //                   << mmap_vector[i].b
    //                   << mmap_vector[i].c
    //                   << std::endl;
    //     }
        
    //     std::cout << mmap_vector.Size() << std::endl;
    //     std::cout << mmap_vector.Capacity() << std::endl;
    //     std::cout << mmap_vector.Empty() << std::endl;

    //     mmap_vector.PopBack();

    //     for (size_t i = 0; i < mmap_vector.Size(); ++i)
    //     {
    //         std::cout << mmap_vector[i].a
    //                   << mmap_vector[i].b
    //                   << mmap_vector[i].c
    //                   << std::endl;
    //     }
    //     std::cout << mmap_vector.Size() << std::endl;
    //     std::cout << mmap_vector.Capacity() << std::endl;
    //     std::cout << mmap_vector.Empty() << std::endl;
    // }

    // Kit::Any any1("123.111");
    // std::cout << (double)any1 << std::endl;

    // std::set<unsigned long> s;
    // int total = 1000000;
    // {
    //     Kit::GUIDGen<Kit::GUID_UNIT_BILLION> guid_gen;
    //     for (auto i = 0; i < total; ++i)
    //     {
    //         s.insert(guid_gen.Next());
    //     }
    //     std::cout << total << ", " << s.size() << std::endl;
    // }
    
    // {
    //     Kit::GUIDGen<Kit::GUID_UNIT_BILLION> guid_gen;
    //     for (auto i = 0; i < total; ++i)
    //     {
    //         s.insert(guid_gen.Next());
    //     }
        
    //     std::cout << total << ", " << s.size() << std::endl;
    // }
    

    // Kit::Random::SetSeed();
    // for (int i = 0; i < 10000; ++i)
    // {
    //     std::cout << Kit::Random::RandomInt(0, 100) << std::endl;
    // }

    // std::vector<int> v = Kit::Random::RandomIntList(0, 10000, 90);
    // std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ", "));
    // std::cout << std::endl;


    // std::cout << Kit::CompositeKey("aa") << std::endl;
    // std::cout << Kit::CompositeKey("aa", "bb") << std::endl;
    // std::cout << Kit::CompositeKey("aa", "bb", "cc") << std::endl;
    // std::cout << Kit::CompositeKey("aa", "bb", "cc", "dd") << std::endl;

    // char a = 0x11;
    // char b = 0x22;
    // char c = 0x33;
    // char d = 0x44;
    // std::cout << std::hex << Kit::NumericCompositeKey(a) << std::endl;
    // std::cout << std::hex << Kit::NumericCompositeKey(a, b) << std::endl;
    // std::cout << std::hex << Kit::NumericCompositeKey(a, b, c) << std::endl;
    // std::cout << std::hex << Kit::NumericCompositeKey(a, b, c, d) << std::endl;
    
    // std::cout << Kit::HashCompositeKey("aa") << std::endl;
    // std::cout << Kit::HashCompositeKey("aa", "bb") << std::endl;
    // std::cout << Kit::HashCompositeKey("aa", "bb", "cc") << std::endl;
    // std::cout << Kit::HashCompositeKey("aa", "bb", "cc", "dd") << std::endl;
    
    Kit::IPAddr ip_addr("127.0.0.1");
    std::cout << (std::string)ip_addr << std::endl;
    std::cout << (uint32_t)ip_addr << std::endl;
    
    return 0;
}

