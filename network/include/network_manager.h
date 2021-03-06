/**
 * Copyright (C) NxtLvL Software Solutions
 *
 * @author Jack Noordhuis <me@jacknoordhuis.net>
 * @copyright NxtLvL Software Solutions
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 *
 */

#ifndef RAPID_NETWORK_INCLUDE_NETWORK_MANAGER_H
#define RAPID_NETWORK_INCLUDE_NETWORK_MANAGER_H

#include "network_interface.h"

#include <memory>

#include <folly/AtomicHashMap.h>
#include <rapid/support/type_identifier.h>

namespace rapid::network {

class NetworkManager {
private:
  folly::AtomicHashMap<support::TypeIdentifier,
                       std::unique_ptr<INetworkInterface>>
      interfaces;

public:
  /**
   * Add a network interface to the network manager.
   *
   * @tparam T The type of interface to add.
   * @param interface The network interface.
   */
  template <typename T> void addInterface(std::unique_ptr<T> interface);

  /**
   * Retrieve a network interface from its type.
   *
   * @tparam T The type of interface to retrieve.
   * @return The registered interface corresponding to the template type.
   */
  template <typename T> std::unique_ptr<T> &getInterface() const noexcept;
};

} // namespace rapid::network

#endif // RAPID_NETWORK_INCLUDE_NETWORK_MANAGER_H
