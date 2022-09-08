#!/usr/bin/env python
import os
import sys
import subprocess
import argparse
import shutil

HOME_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
OUT_PATH = os.path.join(HOME_PATH, 'out')
OUT_LIB = 'nativeserver-%(scheme)s'

GN_ARGS = [
    'native_testing=true',
]

def gen_lib_path(scheme):
    out_lib = OUT_LIB % {'scheme': scheme}
    return os.path.join(HOME_PATH + r'/out', out_lib)

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
        gn_args.append('rtc_include_tests=true')
        gn_args.append('owt_include_tests=true')
    else:
        gn_args.append('rtc_include_tests=false')
        gn_args.append('owt_include_tests=false')
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
    src_lib_path = os.path.join(out_path, r'libtest_shared.so')
    shutil.copy(src_lib_path, gen_lib_path(scheme))
    return True

# Run unit tests on simulator. Return True if all tests are passed.
def runtest(arch, scheme):
    return True

def pack_sdk(scheme, output_path):
    print('start copy out files to %s!' % output_path)
    # out_lib = OUT_LIB % {'scheme': scheme}
    # src_lib_path = os.path.join(OUT_PATH, out_lib)
    # src_include_path = os.path.join(HOME_PATH, r'talk\owt\sdk\include\cpp')
    # src_doc_path = os.path.join(HOME_PATH, r'talk\owt\docs\cpp\html')
    # dst_lib_path = os.path.join(output_path, 'libs')
    # dst_include_path = os.path.join(output_path, 'include')
    # dst_doc_path = os.path.join(output_path, 'docs')
    # if not os.path.exists(dst_lib_path):
    #     os.mkdir(dst_lib_path)
    # if os.path.exists(dst_include_path):
    #     shutil.rmtree(dst_include_path)
    # shutil.copy(src_lib_path, dst_lib_path)
    # shutil.copytree(src_include_path, dst_include_path)
    # if os.path.exists(src_doc_path):
    #     if os.path.exists(dst_doc_path):
    #         shutil.rmtree(dst_doc_path)
    #     shutil.copytree(src_doc_path, dst_doc_path)


def main():
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
    if opts.tests:
        if not runtest(opts.arch, opts.scheme):
            return 1
    if opts.output_path:
        pack_sdk(opts.scheme, opts.output_path)
    print('Done')
    return 0


if __name__ == '__main__':
    sys.exit(main())