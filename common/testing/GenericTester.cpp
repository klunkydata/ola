/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * GenericTester.cpp
 * Run the tests.
 * Copyright (C) 2012 Simon Newton
 */

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <string>

#include "ola/base/Env.h"
#include "ola/base/Flags.h"
#include "ola/base/Init.h"
#include "ola/Logging.h"
#include "ola/StringUtils.h"

using std::string;

#ifdef HAVE_EPOLL
DECLARE_bool(use_epoll);
#endif

DECLARE_uint8(log_level);

int main(int argc, char* argv[]) {
  // Default to INFO since it's tests.
  FLAGS_log_level = ola::OLA_LOG_INFO;

#ifdef HAVE_EPOLL
  string epoll_var;
  bool use_epoll = false;
  if (ola::GetEnv("OLA_USE_EPOLL", &epoll_var) &&
      ola::StringToBool(epoll_var, &use_epoll) &&
      use_epoll) {
    FLAGS_use_epoll = true;
  }
#endif

  ola::AppInit(&argc, argv, "[options]", "");

  CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(suite);

  runner.setOutputter(
      new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
  bool wasSucessful = runner.run();
  return wasSucessful ? 0 : 1;
}
