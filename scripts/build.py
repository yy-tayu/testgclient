#!/usr/bin/env python
# Copyright (C) <2022> Fotric Corporation
#
# SPDX-License-Identifier: Apache-2.0

"""
Prepare development environment.
"""

import os
import shutil
import sys
import subprocess

HOME_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
PATCH_PATH = os.path.join(HOME_PATH, 'talk', 'owt', 'patches')
TESTING_PATH = os.path.join(HOME_PATH, 'testing')
THIRD_PARTY_PATH = os.path.join(HOME_PATH, 'third_party')
LIBSRTP_PATH = os.path.join(THIRD_PARTY_PATH, 'libsrtp')
FFMPEG_PATH = os.path.join(THIRD_PARTY_PATH, 'ffmpeg')
LIBVPX_PATH = os.path.join(THIRD_PARTY_PATH, 'libvpx')
LIBVPX_SOURCE_PATH = os.path.join(LIBVPX_PATH, 'source/libvpx')
WEBRTC_OVERRIDES_PATH = os.path.join(THIRD_PARTY_PATH, 'webrtc_overrides')
BUILD_PATH = os.path.join(HOME_PATH, 'build')
CONFIG_PATH = os.path.join(BUILD_PATH, 'config')
TOOL_PATH = os.path.join(HOME_PATH, 'tools')
BASE_PATH = os.path.join(HOME_PATH, 'base')
platform = os.name
useShell = False
if (platform == "nt"):
  useShell = True


def main(argv):
  print("debug symlink :::::::::::::::::::::::::::::::::::::::::::")
  owt_build = "/home/tayu/Documents/testgclient/src/third_party/owt_client_native/build"
  owt_base = "/home/tayu/Documents/testgclient/src/third_party/owt_client_native/build"
  owt_buildtools = "/home/tayu/Documents/testgclient/src/third_party/owt_client_native/build"
  owt_third_party = "/home/tayu/Documents/testgclient/src/third_party/owt_client_native/build"
  owt_testing = "/home/tayu/Documents/testgclient/src/third_party/owt_client_native/testing"
  owt_tools = "/home/tayu/Documents/testgclient/src/third_party/owt_client_native/tools"
  if not os.path.exists(owt_build):
    os.symlink("/home/tayu/Documents/testgclient/src/build", owt_build)
  if not os.path.exists(owt_base):
    os.symlink("/home/tayu/Documents/testgclient/src/base", owt_base)
  if not os.path.exists(owt_buildtools):
    os.symlink("/home/tayu/Documents/testgclient/src/buildtools", owt_buildtools)
  if not os.path.exists(owt_third_party):
    os.symlink("/home/tayu/Documents/testgclient/src/third_party", owt_third_party)
  if not os.path.exists(owt_testing):
    os.symlink("/home/tayu/Documents/testgclient/src/testing", owt_testing)
  if not os.path.exists(owt_tools):
    os.symlink("/home/tayu/Documents/testgclient/src/tools", owt_tools)
  return 0

if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))
