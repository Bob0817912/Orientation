/*******************************************************************************
 * BSD 3-Clause License
 *
 * Copyright (c) 2021, Qiayuan Liao
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************/

//
// Created by qiayuan on 3/3/21.
//

#pragma once

#include <linux/can.h>
#include <net/if.h>
// Multi-threading
#include <pthread.h>
#include <boost/function.hpp>

namespace can
{
class SocketCAN
{
private:
  ifreq interface_request_{};
  sockaddr_can address_{};
  pthread_t receiver_thread_id_{};

public:
  /**
   * CAN socket file descriptor
   */
  int sock_fd_ = -1;
  /**
   * Request for the child thread to terminate
   */
  bool terminate_receiver_thread_ = false;
  bool receiver_thread_running_ = false;

  SocketCAN() = default;
  ~SocketCAN();

  /** \brief Open and bind socket.
   *
   * \param interface bus's name(example: can0).
   * \param handler Pointer to a function which shall be called when frames are being received from the CAN bus.
   *
   * \returns \c true if it successfully open and bind socket.
   */
  bool open(const std::string& interface, boost::function<void(const can_frame& frame)> handler, int thread_priority);
  /** \brief Close and unbind socket.
   *
   */
  void close();
  /** \brief Returns whether the socket is open or closed.
   *
   * \returns \c True if socket has opened.
   */
  bool isOpen() const;
  /** \brief Sends the referenced frame to the bus.
   *
   * \param frame referenced frame which you want to send.
   */
  void write(can_frame* frame) const;
  /** \brief Starts a new thread, that will wait for socket events.
   *
   */
  bool startReceiverThread(int thread_priority);
  /**
   * Pointer to a function which shall be called
   * when frames are being received from the CAN bus
   */
  boost::function<void(const can_frame& frame)> reception_handler;
};

}  // namespace can
