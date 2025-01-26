import argparse
import os
from argparse import ArgumentError

main_header_template = """#pragma once
#include "neuron/{name}/compile_mode.hpp"

namespace neuron::{name} {{
    NEURON_{modname}_API int version_major();
    NEURON_{modname}_API int version_minor();
    NEURON_{modname}_API int version_patch();
    NEURON_{modname}_API const char* version_str();
}}
"""

main_source_template = """#include "neuron/{name}/{name}.hpp"

namespace neuron::{name} {{
    int version_major() {{
        return NEURON_{modname}_VERSION_MAJOR;
    }}

    int version_minor() {{
        return NEURON_{modname}_VERSION_MINOR;
    }}

    int version_patch() {{
        return NEURON_{modname}_VERSION_PATCH;
    }}

    const char *version_str() {{
        return NEURON_{modname}_VERSION;
    }}
}}"""

cmake_template = """cmake_minimum_required(VERSION 3.30)
project(neuron_{name} VERSION 0.1.0)

add_library(neuron_{name} src/neuron/{name}/{name}.hpp src/neuron/{name}/{name}.cpp)
target_include_directories(neuron_{name} PUBLIC src/)
target_link_libraries(neuron_{name} PUBLIC neuron::core {extra_libs})
add_library(neuron::{name} ALIAS neuron_{name})

Neuron_PrepModule(neuron_{name} {modname} neuron/{name})"""

parser = argparse.ArgumentParser(add_help=True)
parser.add_argument("name", type=str)
parser.add_argument("module_name", type=str, nargs="?")
parser.add_argument("extra_libs", nargs="*", type=str)
parser.add_argument("-x", "--extra", action='store_true')

args = parser.parse_args()

name = args.name
if args.module_name is None:
    modname = name.upper()
    print(f"Defaulting modname to '{modname}'")
else:
    modname = args.module_name.upper()
extra_libs = ' '.join(args.extra_libs)
extra = args.extra

if not os.path.exists("modules/CMakeLists.txt"):
    raise ArgumentError("This script must be run from the root directory of the neuron project (the folder should contain a folder called modules).")

module_dir = os.path.join('modules', name)

if os.path.exists(os.path.join(module_dir, 'CMakeLists.txt')):
    raise FileExistsError(f"Module '{name}' already exists")

os.makedirs(module_dir, exist_ok=True)
print(f"Created {module_dir}{os.pathsep}")

with open(os.path.join(module_dir, 'CMakeLists.txt'), 'w+') as f:
    f.write(cmake_template.format(name=name, modname=modname, extra_libs=extra_libs))
    print(f"Wrote {f.name}")

src_dir = os.path.join(module_dir, 'src', 'neuron', name)

os.makedirs(src_dir, exist_ok=True)
print(f"Created {src_dir}{os.pathsep}")

with open(os.path.join(src_dir, f'{name}.hpp'), 'w+') as f:
    f.write(main_header_template.format(name=name, modname=modname))
    print(f"Wrote {f.name}")

with open(os.path.join(src_dir, f'{name}.cpp'), 'w+') as f:
    f.write(main_source_template.format(name=name, modname=modname))
    print(f"Wrote {f.name}")

with open('modules/CMakeLists.txt', 'a') as f:
    f.write(f"""
# Generated
add_subdirectory("{name}/")
""")
    print(f"Added '{name}' to 'modules/CMakeLists.txt'")

if not extra:
    with open('CMakeLists.txt', 'a') as f:
        f.write(f"""
# Generated
target_link_libraries(neuron_all INTERFACE neuron::{name})
""")
        print(f"Added '{name}' to neuron::all target.")

print(f"Done generating module skeleton for '{name}'")
