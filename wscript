# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('bgp-monitor', ['core'])
    module.source = [
        'model/bgp-monitor.cc',
        'model/bgpmon-fdreader.cc',
        'helper/bgp-monitor-helper.cc',
        ]

    module_test = bld.create_ns3_module_test_library('bgp-monitor')
    module_test.source = [
        'test/bgp-monitor-test-suite.cc',
        ]

    headers = bld(features='ns3header')
    headers.module = 'bgp-monitor'
    headers.source = [
        'model/bgp-monitor.h',
        'model/bgpmon-fdreader.h',
        'helper/bgp-monitor-helper.h',
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

    # bld.ns3_python_bindings()

