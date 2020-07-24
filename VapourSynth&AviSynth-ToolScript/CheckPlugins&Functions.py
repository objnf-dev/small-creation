#!/usr/bin/env python3

# Author: ANLOF
# Change: zhouweitong3

from vapoursynth import core

plugins = core.get_plugins()
for key in plugins:
    print('Key: {}'.format(key))
    print('    Namespace: {}'.format(plugins[key]['namespace']))
    print('    Identifier: {}'.format(plugins[key]['identifier']))
    print('    Name: {}'.format(plugins[key]['name']))
    print('  - Functions: ')
    for funckey in plugins[key]['functions']:
        print('      - Function Name: {}'.format(funckey))
        print('        Function Definition: {}'.format(plugins[key]['functions'].get(funckey)))
    print('\n\n')
