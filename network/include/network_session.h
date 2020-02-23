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

#ifndef RAPID_NETWORK_INCLUDE_NETWORK_SESSION_H
#define RAPID_NETWORK_INCLUDE_NETWORK_SESSION_H

#include <memory>

namespace rapid::network {

// forward declarations
class NetworkInterface;
class SocketAddress;

/**
 * A network session is responsible for managing a connection through a
 * network interface. It can be used for handling connections on a server or for
 * clients connecting to a server.
 *
 * @tparam T The base packet handler class.
 */
template <class T> class NetworkSession {
public:
  /**
   * Construct a new network session instance.
   *
   * @param identifier The sessions unique identifier.
   */
  NetworkSession(const unsigned long identifier) noexcept;

  /**
   * Get the sessions unique identifier.
   *
   * @return The sessions unique identifier.
   */
  [[nodiscard]] unsigned long getIdentifier() const noexcept;

  /**
   * Get the sessions current packet handler instance.
   *
   * @return The session current packet handler.
   */
  [[nodiscard]] std::shared_ptr<T> getHandler() const noexcept;

  /**
   * Set the sessions packet handler.
   *
   * @param handler The new packet handler.
   */
  void setHandler(std::shared_ptr<T> handler) noexcept;

  /**
   * Check if the session has been closed.
   *
   * @return True if closed, false if still active.
   */
  [[nodiscard]] bool closed() const noexcept;

  /**
   * Start the process of closing the session.
   */
  void close() noexcept;

protected:
  /**
   * Called when the session is closed, all child classes should implement their
   * close logic in this method.
   */
  virtual void doClose() noexcept;

private:
  /**
   * The sessions unique identifier.
   */
  const unsigned long identifier;

  /**
   * The sessions source internet address.
   */
  std::shared_ptr<SocketAddress> address;

  /**
   * The current package handler.
   */
  std::unique_ptr<T> handler;

  /**
   * Stores whether the session has been closed.
   */
  std::atomic_bool isClosed{false};
};

} // namespace rapid::network

#endif // RAPID_NETWORK_INCLUDE_NETWORK_SESSION_H
