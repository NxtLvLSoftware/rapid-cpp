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

#ifndef RAPID_NETWORK_INCLUDE_NETWORK_INTERFACE_H
#define RAPID_NETWORK_INCLUDE_NETWORK_INTERFACE_H

#include <memory>
#include <mutex>

#include <folly/AtomicHashMap.h>

namespace rapid::network {

/**
 * Base interface defining common methods for a network interface. This
 * base type can be used where we don't need to know the underlying
 * session type.
 */
class INetworkInterface {
private:
  /**
   * A simple counter used for assigning sessions unique ids.
   */
  std::atomic_ulong sessionCount{0};

public:
  INetworkInterface() = default;

  /**
   * Retrieve the next usable session identifier.
   *
   * @return A new unique session identifier.
   */
  [[nodiscard]] unsigned long nextSessionIdentifier() noexcept;
};

/**
 * A network interface is responsible for managing a group of sessions for a
 * single session implementation.
 *
 * @tparam T The network session class type to use.
 */
template <class T> class NetworkInterface : public INetworkInterface {
public:
  NetworkInterface() = default;

  /**
   * Register a network session to the interface.
   *
   * @param session The session instance to add.
   */
  void addSession(std::unique_ptr<T> &session) const noexcept;

  /**
   * Retrieve a network session instance using its identifier.
   *
   * @param identifier The unique session identifier.
   * @return The session corresponding to the identifier.
   */
  [[nodiscard]] const std::unique_ptr<T> &
  getSession(const long identifier) const noexcept;

  /**
   * Remove a session from the manager
   *
   * @param session The session instance to remove.
   */
  void removeSession(const std::unique_ptr<T> &session) const noexcept;

private:
  /**
   * Mapping of session identifiers to session instances.
   */
  folly::AtomicHashMap<unsigned long, std::unique_ptr<T>> sessions;
};

} // namespace rapid::network

#endif // RAPID_NETWORK_INCLUDE_NETWORK_INTERFACE_H
