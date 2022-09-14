#!/usr/bin/env python
# Copyright (C) <2022> Fotric Corporation
#

"""
Prepare development environment.
"""

import os
import sys
import argparse
import subprocess
import shutil

HOME_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
GN_ARGS = []

def gngen(arch, scheme, tests):
  gn_args = list(GN_ARGS)
  gn_args.append('target_cpu="%s"' % arch)
  using_llvm = False
  if arch == 'arm64':
    using_llvm = True
  if  not using_llvm:
    gn_args.append('is_clang=false')
  else:
    gn_args.append('libcxx_abi_unstable=false')
    gn_args.append('use_custom_libcxx_for_host=false')
    gn_args.append('use_custom_libcxx=false')
  if scheme == 'release':
    gn_args.append('is_debug=false')
  else:
    gn_args.append('is_debug=true')
  if tests:
    gn_args.append('aonyx_include_tests=true')
  else:
    gn_args.append('aonyx_include_tests=false')
  flattened_args = ' '.join(gn_args)
  print(gn_args)
  ret = subprocess.call(['gn', 'gen', 'out/%s-%s' % (scheme, arch), '--args=' + flattened_args],
                        cwd=HOME_PATH, shell=False)
  if ret == 0:
    return True
  return False

def getoutputpath(arch, scheme):
  bin_path = 'out/%s-%s' % (scheme, arch)
  obj_path = os.path.join(HOME_PATH, bin_path)
  return obj_path

def ninjabuild(arch, scheme):
  out_path = getoutputpath(arch, scheme)
  cmd = 'ninja -C ' + out_path
  if subprocess.call(['ninja', '-C', out_path], cwd=HOME_PATH, shell=False) != 0:
    return False
  return True

def main(argv):
  parser = argparse.ArgumentParser()
  parser.add_argument('--arch', default='x86', dest='arch', choices=('x86', 'x64', 'arm64'),
                      help='Target architecture. Supported value: x86, x64, arm64')
  parser.add_argument('--scheme', default='debug', choices=('debug', 'release'),
                      help='Schemes for building. Supported value: debug, release')
  parser.add_argument('--gn_gen', default=False, action='store_true',
                      help='Explicitly ninja file generation.')
  parser.add_argument('--tests', default=False, action='store_true', help='Run unit tests.')
  parser.add_argument('--sdk', default=False, action='store_true', help='To build sdk lib.')
  parser.add_argument('--output_path', help='Path to copy sdk.')
  opts = parser.parse_args()
  print(opts)
  if opts.gn_gen:
    if not gngen(opts.arch, opts.scheme, opts.tests):
      return 1
  if opts.sdk:
    if not ninjabuild(opts.arch, opts.scheme):
      return 1
  # if opts.tests:
  #   if not runtest(opts.arch, opts.scheme):
  #     return 1
  # if opts.output_path:
  #   pack_sdk(opts.scheme, opts.output_path)
  print('Done')
  return 0  

if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))
