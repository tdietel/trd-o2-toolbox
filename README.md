TRD/O2 Toolbox
==============

This repository is meant to be a (personal) collection of tools for the ALICE
TRD software in O2.

At the moment it only contains one programme: rawreader.

rawreader
---------

`rawreader` is a standalone C++ programme that mmaps's a timeframe file, loops
through the sub-time-frames in the file and calls the `o2::trd:CruRawReader`
for all TRD STFs.

This programme is a quick hack to look into TFs without running an entire DPL
workflow, because my Mac laptop had problems with this. It also allows to keep
track of the position of the data within the raw file, without DPL interfering
with STF order or similar.

At the moment, there are a lot of hard-coded paths in the CMake setup. Any
suggestions how to clean this up are welcome.
