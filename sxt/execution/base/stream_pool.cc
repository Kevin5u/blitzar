#include "sxt/execution/base/stream_pool.h"

#include <cuda_runtime.h>

#include <string>

#include "sxt/base/error/assert.h"
#include "sxt/base/error/panic.h"
#include "sxt/execution/base/stream_handle.h"

namespace sxt::xenb {
//--------------------------------------------------------------------------------------------------
// make_stream_handle
//--------------------------------------------------------------------------------------------------
static stream_handle* make_stream_handle() noexcept {
  auto res = new stream_handle{};
  auto rcode = cudaStreamCreate(&res->stream);
  if (rcode != cudaSuccess) {
    baser::panic("cudaStreamCreate failed: " + std::string(cudaGetErrorString(rcode)));
  }
  res->next = nullptr;
  return res;
};

//--------------------------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------------------------
stream_pool::stream_pool(size_t initial_size) noexcept {
  head_ = nullptr;
  while (initial_size-- > 0) {
    auto handle = make_stream_handle();
    handle->next = head_;
    head_ = handle;
  }
}

//--------------------------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------------------------
stream_pool::~stream_pool() noexcept {
  auto handle = head_;
  while (handle != nullptr) {
    auto next = handle->next;
    auto rcode = cudaStreamDestroy(handle->stream);
    if (rcode != cudaSuccess) {
      baser::panic("cudaStreamDestroy failed: " + std::string(cudaGetErrorString(rcode)));
    }
    delete handle;
    handle = next;
  }
}

//--------------------------------------------------------------------------------------------------
// aquire_handle
//--------------------------------------------------------------------------------------------------
stream_handle* stream_pool::aquire_handle() noexcept {
  if (head_ == nullptr) {
    return make_stream_handle();
  }
  auto res = head_;
  head_ = res->next;
  res->next = nullptr;
  return res;
}

//--------------------------------------------------------------------------------------------------
// release_handle
//--------------------------------------------------------------------------------------------------
void stream_pool::release_handle(stream_handle* handle) noexcept {
  SXT_DEBUG_ASSERT(handle != nullptr);
  handle->next = head_;
  head_ = handle;
}

//--------------------------------------------------------------------------------------------------
// get_stream_pool
//--------------------------------------------------------------------------------------------------
stream_pool* get_stream_pool(size_t initial_size) noexcept {
  // Allocate a thread local pool that's available for the duration of the process.
  static thread_local auto pool = new stream_pool{initial_size};
  return pool;
}
} // namespace sxt::xenb