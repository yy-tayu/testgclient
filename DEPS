# Copyright 2015 The Chromium Authors. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#    * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#    * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
#    * Neither the name of Google Inc. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Copyright (C) <2018> Intel Corporation
#
# SPDX-License-Identifier: Apache-2.0

# This file contains dependencies for Intel CS for WebRTC Client SDKs.
# It based on Chromium project.

gclient_gn_args_file = 'src/build/config/gclient_args.gni'
gclient_gn_args = [
  'checkout_google_benchmark',
]

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # By default, do not check out Google Benchmark. The library is only used by a
  # few specialized benchmarks that most developers do not interact with. Will
  # be overridden by gclient variables.
  'checkout_google_benchmark': True,

  # By default, we should check out everything needed to run on the main
  # chromium waterfalls. More info at: crbug.com/570091.
  'checkout_configuration': 'default',
  'checkout_instrumented_libraries': 'checkout_linux and checkout_configuration == "default"',
  'deps_owt_client_native_git': 'https://github.com/open-webrtc-toolkit/owt-client-native',
  'deps_webrtc_git': 'https://github.com/open-webrtc-toolkit',
  'chromium_revision': '56e883537df53a3b3cbc39c264799bedb695b5f9',
  'boringssl_git': 'https://boringssl.googlesource.com',
  # Three lines of non-changing comments so that
  # the commit queue can handle CLs rolling swarming_client
  # and whatever else without interference from each other.
  'swarming_revision': 'd46ea7635f2911208268170512cb611412488fd8',
  # Three lines of non-changing comments so that
  # the commit queue can handle CLs rolling BoringSSL
  # and whatever else without interference from each other.
  'boringssl_revision': '1607f54fed72c6589d560254626909a64124f091',
  # Three lines of non-changing comments so that
  # the commit queue can handle CLs rolling lss
  # and whatever else without interference from each other.
  'lss_revision': '29f7c7e018f4ce706a709f0b0afbf8bacf869480',
  # Three lines of non-changing comments so that
  # the commit queue can handle CLs rolling catapult
  # and whatever else without interference from each other.
  'catapult_revision': '434681c2378b686117c2b003a58c54d78f22185f',
  # Three lines of non-changing comments so that
  # the commit queue can handle CLs rolling libFuzzer
  # and whatever else without interference from each other.
  'libfuzzer_revision': 'debe7d2d1982e540fbd6bd78604bf001753f9e74',
  # Three lines of non-changing comments so that
  # the commit queue can handle CLs rolling GN CIPD package version
  # and whatever else without interference from each other.
  'gn_version': 'git_revision:53d92014bf94c3893886470a1c7c1289f8818db0',
}
deps = {
  # TODO(kjellander): Move this to be Android-only once the libevent dependency
  # in base/third_party/libevent is solved.
  'src/base':
    Var('chromium_git') + '/chromium/src/base' + '@' + 'cdccd610777e3e49936c03a35b3ef7cb7d8a6794',
  'src/build':
    Var('chromium_git') + '/chromium/src/build' + '@' + '57d7d0ceaed77728665884b58d60230b13906a9c',
  'src/buildtools':
    Var('chromium_git') + '/chromium/src/buildtools' + '@' + '6302c1175607a436e18947a5abe9df2209e845fc',
  'src/ios': {
    'url': Var('chromium_git') + '/chromium/src/ios' + '@' + '5720c93651b31160238c133f69e7a05366360e19',
    'condition': 'checkout_ios',
  },
  # OWT Patch
  'src/third_party/usrsctp/usrsctplib':
    Var('chromium_git') + '/external/github.com/sctplab/usrsctp' + '@' + '2caaff2b0a1d550751bb6aa1aaa6ece4829848d4',
  'src/third_party/libsrtp':
   Var('chromium_git') + '/chromium/deps/libsrtp.git' + '@' + '6907d995c7975c2865f6f94f79638c25c342e95c',
  'src/third_party/ffmpeg':
    Var('chromium_git') + '/chromium/third_party/ffmpeg.git' + '@' + '6d9096c9e3f7f5d4e6528104ed77987ec9327315',

  'src/testing':
    Var('chromium_git') + '/chromium/src/testing' + '@' + 'd54c4bf27e02291ec35e4c040e47c09e02d8a452',
  'src/third_party':
    Var('chromium_git') + '/chromium/src/third_party' + '@' + '346e496c9b3e7ac74b3f0c8ac8980fe834d5fee8',
  'src/third_party/depot_tools':
    Var('chromium_git') + '/chromium/tools/depot_tools.git' + '@' + '17cd53de67f982f123bfa6458780c31705221e60',
  'src/buildtools/linux64': {
    'packages': [
      {
        'package': 'gn/gn/linux-amd64',
        'version': Var('gn_version'),
      }
    ],
    'dep_type': 'cipd',
    'condition': 'checkout_linux',
  },
  'src/buildtools/mac': {
    'packages': [
      {
        'package': 'gn/gn/mac-amd64',
        'version': Var('gn_version'),
      }
    ],
    'dep_type': 'cipd',
    'condition': 'checkout_mac',
  },
  'src/buildtools/win': {
    'packages': [
      {
        'package': 'gn/gn/windows-amd64',
        'version': Var('gn_version'),
      }
    ],
    'dep_type': 'cipd',
    'condition': 'checkout_win',
  },
  'src/buildtools/clang_format/script':
    Var('chromium_git') + '/chromium/llvm-project/cfe/tools/clang-format.git' + '@' + '96636aa0e9f047f17447f2d45a094d0b59ed7917',
  'src/buildtools/third_party/libc++/trunk':
    Var('chromium_git') + '/external/github.com/llvm/llvm-project/libcxx.git' + '@' + 'd9040c75cfea5928c804ab7c235fed06a63f743a',
  'src/buildtools/third_party/libc++abi/trunk':
    Var('chromium_git') + '/external/github.com/llvm/llvm-project/libcxxabi.git' + '@' + '196ba1aaa8ac285d94f4ea8d9836390a45360533',
  'src/buildtools/third_party/libunwind/trunk':
    Var('chromium_git') + '/external/github.com/llvm/llvm-project/libunwind.git' + '@' + 'd999d54f4bca789543a2eb6c995af2d9b5a1f3ed',
  'src/third_party/android_ndk': {
      'url': Var('chromium_git') + '/android_ndk.git' + '@' + '27c0a8d090c666a50e40fceb4ee5b40b1a2d3f87',
      'condition': 'checkout_android',
  },
  'src/tools/clang/dsymutil': {
    'packages': [
      {
        'package': 'chromium/llvm-build-tools/dsymutil',
        'version': 'M56jPzDv1620Rnm__jTMYS62Zi8rxHVq7yw0qeBFEgkC',
      }
    ],
    'condition': 'checkout_mac',
    'dep_type': 'cipd',
  },

  'src/third_party/android_system_sdk': {
      'packages': [
          {
              'package': 'chromium/third_party/android_system_sdk',
              'version': 'no8ss5nRg6uYDM08HboypuIQuix7bS1kVqRGyWmwP-YC',
          },
      ],
      'condition': 'checkout_android',
      'dep_type': 'cipd',
  },

  'src/third_party/android_build_tools/aapt2': {
      'packages': [
          {
              'package': 'chromium/third_party/android_build_tools/aapt2',
              'version': 'R2k5wwOlIaS6sjv2TIyHotiPJod-6KqnZO8NH-KFK8sC',
          },
      ],
      'condition': 'checkout_android',
      'dep_type': 'cipd',
  },

  'src/third_party/android_build_tools/bundletool': {
      'packages': [
          {
              'package': 'chromium/third_party/android_tools_bundletool',
              'version': 'gB66fGCdzqmQO6U6hxhoZDCGjOg-oqxhT_4uywaUw1oC',
          },
      ],
      'condition': 'checkout_android',
      'dep_type': 'cipd',
  },
  'src/tools':
    Var('chromium_git') + '/chromium/src/tools' + '@' + '2bb144cfe3f82806c48e30a671169eed729f070b',
  'src/tools/swarming_client':
    Var('chromium_git') + '/infra/luci/client-py.git' + '@' +  Var('swarming_revision'),
  # WebRTC-only dependencies (not present in Chromium).
  'src/third_party/owt_client_native':
    Var('deps_webrtc_git') + '/owt-client-native' + '@' + '7cbfede1d1ab14892731a2f63bea5574b9a4deb1',

  'src/tools/luci-go': {
      'packages': [
        {
          'package': 'infra/tools/luci/isolate/${{platform}}',
          'version': 'git_revision:1a022d3a4c50be4207ee93451255d71896416596',
        },
        {
          'package': 'infra/tools/luci/isolated/${{platform}}',
          'version': 'git_revision:1a022d3a4c50be4207ee93451255d71896416596',
        },
        {
          'package': 'infra/tools/luci/swarming/${{platform}}',
          'version': 'git_revision:1a022d3a4c50be4207ee93451255d71896416596',
        },
      ],
      'dep_type': 'cipd',
  },
}

pre_deps_hooks = []

hooks = [
  {
    # This clobbers when necessary (based on get_landmines.py). It should be
    # an early hook but it will need to be run after syncing Chromium and
    # setting up the links, so the script actually exists.
    'name': 'landmines',
    'pattern': '.',
    'action': [
        'python',
        'src/build/landmines.py',
        '--landmine-scripts',
        'src/build/get_landmines.py',
        '--src-dir',
        'src',
    ],
  },
  {
    # Ensure that the DEPS'd "depot_tools" has its self-update capability
    # disabled.
    'name': 'disable_depot_tools_selfupdate',
    'pattern': '.',
    'action': [
        'python',
        'src/third_party/depot_tools/update_depot_tools_toggle.py',
        '--disable',
    ],
  },
  {
    'name': 'sysroot_arm',
    'pattern': '.',
    'condition': 'checkout_linux and checkout_arm',
    'action': ['python', 'src/build/linux/sysroot_scripts/install-sysroot.py',
               '--arch=arm'],
  },
  {
    'name': 'sysroot_arm64',
    'pattern': '.',
    'condition': 'checkout_linux and checkout_arm64',
    'action': ['python', 'src/build/linux/sysroot_scripts/install-sysroot.py',
               '--arch=arm64'],
  },
  {
    'name': 'sysroot_x86',
    'pattern': '.',
    'condition': 'checkout_linux and (checkout_x86 or checkout_x64)',
    # TODO(mbonadei): change to --arch=x86.
    'action': ['python', 'src/build/linux/sysroot_scripts/install-sysroot.py',
               '--arch=i386'],
  },
  {
    'name': 'sysroot_mips',
    'pattern': '.',
    'condition': 'checkout_linux and checkout_mips',
    # TODO(mbonadei): change to --arch=mips.
    'action': ['python', 'src/build/linux/sysroot_scripts/install-sysroot.py',
               '--arch=mipsel'],
  },
  {
    'name': 'sysroot_x64',
    'pattern': '.',
    'condition': 'checkout_linux and checkout_x64',
    # TODO(mbonadei): change to --arch=x64.
    'action': ['python', 'src/build/linux/sysroot_scripts/install-sysroot.py',
               '--arch=amd64'],
  },
  {
    # Case-insensitivity for the Win SDK. Must run before win_toolchain below.
    'name': 'ciopfs_linux',
    'pattern': '.',
    'condition': 'checkout_win and host_os == "linux"',
    'action': [ 'python',
                'src/third_party/depot_tools/download_from_google_storage.py',
                '--no_resume',
                '--no_auth',
                '--bucket', 'chromium-browser-clang/ciopfs',
                '-s', 'src/build/ciopfs.sha1',
    ]
  },
  {
    # Update the Windows toolchain if necessary. Must run before 'clang' below.
    'name': 'win_toolchain',
    'pattern': '.',
    'condition': 'checkout_win',
    'action': ['python', 'src/build/vs_toolchain.py', 'update', '--force'],
  },
  {
    # Update the Mac toolchain if necessary.
    'name': 'mac_toolchain',
    'pattern': '.',
    'condition': 'checkout_mac',
    'action': ['python', 'src/build/mac_toolchain.py'],
  },
  {
    # Note: On Win, this should run after win_toolchain, as it may use it.
    'name': 'clang',
    'pattern': '.',
    'action': ['python', 'src/tools/clang/scripts/update.py'],
  },
  {
    # Update LASTCHANGE.
    'name': 'lastchange',
    'pattern': '.',
    'action': ['python', 'src/build/util/lastchange.py',
               '-o', 'src/build/util/LASTCHANGE'],
  },
  # Pull clang-format binaries using checked-in hashes.
  {
    'name': 'clang_format_win',
    'pattern': '.',
    'condition': 'host_os == "win"',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=win32',
                '--no_auth',
                '--bucket', 'chromium-clang-format',
                '-s', 'src/buildtools/win/clang-format.exe.sha1',
    ],
  },
  {
    'name': 'clang_format_mac',
    'pattern': '.',
    'condition': 'host_os == "mac"',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=darwin',
                '--no_auth',
                '--bucket', 'chromium-clang-format',
                '-s', 'src/buildtools/mac/clang-format.sha1',
    ],
  },
  {
    'name': 'clang_format_linux',
    'pattern': '.',
    'condition': 'host_os == "linux"',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=linux*',
                '--no_auth',
                '--bucket', 'chromium-clang-format',
                '-s', 'src/buildtools/linux64/clang-format.sha1',
    ],
  },
  # Pull rc binaries using checked-in hashes.
  {
    'name': 'rc_win',
    'pattern': '.',
    'condition': 'checkout_win and host_os == "win"',
    'action': [ 'python',
                'src/third_party/depot_tools/download_from_google_storage.py',
                '--no_resume',
                '--no_auth',
                '--bucket', 'chromium-browser-clang/rc',
                '-s', 'src/build/toolchain/win/rc/win/rc.exe.sha1',
    ],
  },
  {
    'name': 'rc_mac',
    'pattern': '.',
    'condition': 'checkout_win and host_os == "mac"',
    'action': [ 'python',
                'src/third_party/depot_tools/download_from_google_storage.py',
                '--no_resume',
                '--no_auth',
                '--bucket', 'chromium-browser-clang/rc',
                '-s', 'src/build/toolchain/win/rc/mac/rc.sha1',
    ],
  },
  {
    'name': 'rc_linux',
    'pattern': '.',
    'condition': 'checkout_win and host_os == "linux"',
    'action': [ 'python',
                'src/third_party/depot_tools/download_from_google_storage.py',
                '--no_resume',
                '--no_auth',
                '--bucket', 'chromium-browser-clang/rc',
                '-s', 'src/build/toolchain/win/rc/linux64/rc.sha1',
    ],
  },
  {
    'name': 'msan_chained_origins',
    'pattern': '.',
    'condition': 'checkout_instrumented_libraries',
    'action': [ 'python',
                'src/third_party/depot_tools/download_from_google_storage.py',
                "--no_resume",
                "--no_auth",
                "--bucket", "chromium-instrumented-libraries",
                "-s", "src/third_party/instrumented_libraries/binaries/msan-chained-origins-trusty.tgz.sha1",
              ],
  },
  {
    'name': 'msan_no_origins',
    'pattern': '.',
    'condition': 'checkout_instrumented_libraries',
    'action': [ 'python',
                'src/third_party/depot_tools/download_from_google_storage.py',
                "--no_resume",
                "--no_auth",
                "--bucket", "chromium-instrumented-libraries",
                "-s", "src/third_party/instrumented_libraries/binaries/msan-no-origins-trusty.tgz.sha1",
              ],
  },
  {
    # Download test resources, i.e. video and audio files from Google Storage.
    'pattern': '.',
    'action': ['download_from_google_storage',
               '--directory',
               '--recursive',
               '--num_threads=10',
               '--no_auth',
               '--quiet',
               '--bucket', 'chromium-webrtc-resources',
               'src/third_party/webrtc/resources'],
  },
  {
    # Prepare environment for OWT development.
    'pattern': '.',
    'action': ['python',
               'src/scripts/prepare_dev.py'],
  },
  {
    # Prepare environment for OWT development.
    'pattern': '.',
    'action': ['python',
               'src/scripts/build_linux.py',
               '--gn_gen',
               '--sdk', 
               '--output_path',
               '../test-build'
               ],
  },
]

recursedeps = []

# Define rules for which include paths are allowed in our source.
include_rules = [
]

specific_include_rules = {}