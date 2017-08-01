#pragma once

#include <inttypes.h>
#include <json/json.h>
#include <map>
#include <memory>
#include <string>

#include "common/libs/fs/shared_fd.h"
#include "uapi/vsoc_shm.h"

namespace ivserver {

class VSoCSharedMemory {
 public:
  // Region describes a VSoCSharedMem region.
  struct Region {
    std::string name;
    avd::SharedFD host_fd;
    avd::SharedFD guest_fd;
  };

  // Max name length of a memory region.
  static constexpr int32_t kMaxRegionNameLength = sizeof(vsoc_device_name);

  VSoCSharedMemory() = default;
  virtual ~VSoCSharedMemory() = default;

  static std::unique_ptr<VSoCSharedMemory> New(const uint32_t size_mib,
                                               const std::string &name,
                                               const Json::Value &json_root);

  virtual bool GetEventFdPairForRegion(const std::string &region_name,
                                       avd::SharedFD *guest_to_host,
                                       avd::SharedFD *host_to_guest) const = 0;

  virtual const avd::SharedFD &SharedMemFD() const = 0;
  virtual const std::vector<Region> &Regions() const = 0;

 private:
  VSoCSharedMemory(const VSoCSharedMemory &) = delete;
  VSoCSharedMemory &operator=(const VSoCSharedMemory &other) = delete;
};

}  // namespace ivserver