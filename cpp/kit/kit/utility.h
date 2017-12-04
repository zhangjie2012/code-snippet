#ifndef __KIT_UTILITY_H__
#define __KIT_UTILITY_H__

#include <stddef.h>

#define NAMESPACE_BEGIN(name) namespace name {
#define NAMESPACE_END(name) } /* name */

/* Usage:
  KIT_SCORE_EXIT {
  // your exit code
  } KIT_SCORE_END ;
*/
#define KIT_SCORE_EXIT class KitScoreTmpClass { \
    public: ~KitScoreTmpClass()
#define KIT_SCORE_END }; \
    KitScoreTmpClass kit_tmp_var;

const size_t CHUNK_SIZE = 64 * 1024; // 64K
const size_t PAGE_SIZE  = 4 * 1024;  // 4K

// 字节对齐
inline size_t Align(const size_t size, const size_t block_size)
{
    return (size + block_size - 1) / block_size * block_size;
}

// 按照 chunk 大小对齐
inline size_t AlignByChunkSize(const size_t size)
{
    return Align(size, CHUNK_SIZE);
}

// 按照 页大小(page size) 对齐
inline size_t AlignByPageSize(const size_t size)
{
    return Align(size, PAGE_SIZE);
}

#endif /* __KIT_UTILITY_H__ */
