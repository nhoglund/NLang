"""Script that generates the ninja build scripts."""

import os
import sys
from optparse import OptionParser
sys.path.insert(0, 'misc')
import ninja_syntax

compilers = ['clang', 'gcc']

parser = OptionParser()
parser.add_option('-d', '--debug',
				  help='configure for a debug build', action="store_true")

(options, args) = parser.parse_args()
if len(args) != 1:
    print('Usage: configure.py <options> <compiler>')
    sys.exit(1)

compiler = args[0]

if not compiler in compilers:
	print('Compiler must be set to one of: ' + ' '.join(compilers))
	sys.exit(1)

if compiler == 'clang':
	cflags = '-std=c++11 -I. -fcolor-diagnostics'
	compile = 'clang++ -MMD -MT $out -MF $out.d $cflags -c $in -o $out'
	link = 'clang++ $ldflags -o $out $in $libs'
elif compiler == 'gcc':
	cflags = '-std=c++0x -I.'
	compile = 'g++ -MMD -MT $out -MF $out.d $cflags -c $in -o $out'
	link = 'g++ $ldflags -o $out $in $libs'

objext = '.o'
exeext = ''
if sys.platform == 'win32':
	objext = '.obj'
	exeext = '.exe'

config = 'release'
if options.debug:
	config = 'debug'

dir = os.path.join('build', sys.platform + '-' + compiler + '-' + config)
try:
	os.makedirs(dir)
except FileExistsError:
	pass

build_file_name = 'build.ninja'
build_file = open(build_file_name, 'w')
n = ninja_syntax.Writer(build_file)
n.variable('builddir', dir)
n.variable('cflags', cflags)
n.newline()

n.rule('cxx',
    command=compile,
    depfile='$out.d',
    description='CXX $out')
n.newline()

n.rule('link',
	command=link,
	description='LINK $out')
n.newline()

n.rule('test',
	command='$exe',
	description='TEST $name')
n.newline()

def cxx(name, **kwargs):
	return n.build(os.path.join('$builddir', name + objext), 'cxx', name + '.cc', **kwargs)

def exe_path(name):
	return os.path.join('$builddir', name + exeext)

def executable(name, sources, libs=[]):
	objs = []

	for name in sources:
		objs += cxx(name)

	n.build(exe_path(name), 'link', objs, variables=[('libs', libs)])
	n.newline()

def test(name, sources, libs=[]):
	executable(name, sources, libs)
	n.build('run_' + name, 'test', exe_path(name), variables=[('name', name), ('exe', exe_path(name))])
	n.newline()

test('simpletest_test', ['simpletest_test'])
test('types_test', ['types', 'types_test'])