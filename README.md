# Geant4 Based Simulations

This is may Geant4 playground which is primarily intended to host
detector simulations I can use to explore and develop smeagol.

# Visualization
We got OpenGL and VRML going on. One can set the `G4VRMLFILE_VIEWER` 
environment variable to point to a viewer like FreeWRL for geant to launch 
the viewer immediately after a run.

# Data Collection
Need to think about this.  My preferred option of HDF5 is poorly supported.
Make suer to compile HDF5 to be thread safe and compatible with geant.
The native geant HDF5 interface seems dominated by the ROOT API rather 
than an interface that makes sense for HDF5.

I do have an HDF5 reader to read the optical properties of materials.
This makes plotting and editing these properties a little easier than
the typical hard-coded array shown in the various examples.


# Setup
Source the `scripts/g4setup.sh` script to prepare a working environment to
compile the simulations.

## Debugging
Set the `G4DEBUG` environment variable to build the application with
debugging symbols.
```
export G4DEBUG=1
```


# Geometries
The following simulation executables implement various geometries and
scenarios to study.  Some of these may leverage common code in the
`include` and `src` directories.

## Simple Ecal `simple_ecal.cc`


# Setup and Running

# General References

* https://geant4.kek.jp/LXR/
* https://geant4.kek.jp/Reference/10.06/index.html
* http://geant4.web.cern.ch/support/user_documentation
* https://portal.hdfgroup.org/display/HDF5/HDF5+Application+Developer%27s+Guide
* 
 
