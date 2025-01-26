import sys

template = """#pragma once
#ifdef WIN32
  #ifdef NEURON_{modname}_SHARED
    #ifdef NEURON_{modname}_SHARED_EXPORTS
      #define NEURON_{modname}_API __declspec(dllexport)
    #else
      #define NEURON_{modname}_API __declspec(dllimport)
    #endif
  #else
    #define NEURON_{modname}_API
  #endif
#else
  #define NEURON_{modname}_API
#endif

#define NEURON_{modname}_VERSION "{versionstr}"
#define NEURON_{modname}_VERSION_MAJOR {versionmajor}
#define NEURON_{modname}_VERSION_MINOR {versionminor}
#define NEURON_{modname}_VERSION_PATCH {versionpatch}
"""

modname = sys.argv[1]
outfile = sys.argv[2]
versionmajor, versionminor, versionpatch, versionstr = sys.argv[3:7]

with open(outfile, 'w+') as f:
    f.write(template.format(modname=modname, versionmajor=versionmajor, versionminor=versionminor, versionpatch=versionpatch, versionstr=versionstr))

