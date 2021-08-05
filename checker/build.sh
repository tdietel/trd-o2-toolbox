#!/bin/sh

SOURCEDIR=$(pwd)

export FAIRROOTPATH=/Users/tom/alice/sw/osx_x86-64/FairRoot/latest

# case $ARCHITECTURE in
#     osx*)
#         [[ ! $BOOST_ROOT ]] && BOOST_ROOT=$(brew --prefix boost)
#         [[ ! $FMT_ROOT ]] && FMT_ROOT=$(brew --prefix fmt)
#         [[ ! $PROTOBUF_ROOT ]] && PROTOBUF_ROOT=$(brew --prefix protobuf)
#     ;;
# esac
#
# cmake $SOURCEDIR                                                \
#       ${CMAKE_GENERATOR:+-G "$CMAKE_GENERATOR"}                 \
#       -DCMAKE_INSTALL_PREFIX=$INSTALLROOT                       \
#       ${BOOST_ROOT:+-DBoost_ROOT=$BOOST_ROOT}                   \
#       ${FAIRLOGGER_ROOT:+-DFairLogger_ROOT=$FAIRLOGGER_ROOT}    \
#       ${INFOLOGGER_ROOT:+-DInfoLogger_ROOT=$INFOLOGGER_ROOT}    \
#       ${FAIRMQ_ROOT:+-DFairMQ_ROOT=$FAIRMQ_ROOT}                \
#       ${PPCONSUL_ROOT:+-Dppconsul_DIR=${PPCONSUL_ROOT}/cmake}   \
#       ${O2_ROOT:+-DO2_ROOT=$O2_ROOT}                            \
#       ${MONITORING_ROOT:+-DMonitoring_ROOT=$MONITORING_ROOT}    \
#       ${PROTOBUF_ROOT:+-DProtobuf_ROOT=$PROTOBUF_ROOT}          \
#       -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
#
cmake . \
    -DBoost_ROOT=$BOOST_ROOT \
    -Dfmt_DIR=/Users/tom/alice/sw/osx_x86-64/fmt/7.1.0-local1/ \
    -DFAIRROOTPATH=/Users/tom/alice/sw/osx_x86-64/FairRoot/latest \
    -Dfmt_DIR=/Users/tom/alice/sw/osx_x86-64/fmt/7.1.0-local1 \
    -DBoost_ROOT=/Users/tom/alice/sw/osx_x86-64/boost/latest \
    -DFairLogger_ROOT=/Users/tom/alice/sw/osx_x86-64/FairLogger/latest \
