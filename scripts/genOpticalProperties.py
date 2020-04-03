#!/usr/bin/env python

'''
This script generates a basic set of optical properties.
The raw properties table has the following format:
N x 3
with the following column definitions:
  * energy (eV)
  * refractive index
  * absorption length
'''

import os,sys

import matplotlib as mpl
import pylab as plt

import numpy as np

import tables


nPoints = 100

raw_props = np.zeros((nPoints,3))

#
# create a list of energy
raw_props[:,0] = np.linspace(2,5,nPoints)


#
#  set the refractive index
raw_props[:,1] = 1.7


#
# set the absorption length
raw_props[:,2] = 55


#
# create the h5 file and store the data
h5file = tables.open_file("prop_table.h5",mode="w",title="Optical Properties")
gr = h5file.create_group("/",'lead-glass','Lead Glass Optical Properties')
h5file.create_array('/lead-glass','props',raw_props)

h5file.close()




