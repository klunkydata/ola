# LIBRARIES
##################################################
if USE_PATHPORT
plugin_LTLIBRARIES += plugins/pathport/libolapathport.la
plugins_pathport_libolapathport_la_SOURCES = \
    plugins/pathport/PathportDevice.cpp \
    plugins/pathport/PathportDevice.h \
    plugins/pathport/PathportNode.cpp \
    plugins/pathport/PathportNode.h \
    plugins/pathport/PathportPackets.h \
    plugins/pathport/PathportPlugin.cpp \
    plugins/pathport/PathportPlugin.h \
    plugins/pathport/PathportPort.cpp \
    plugins/pathport/PathportPort.h
plugins_pathport_libolapathport_la_LIBADD = common/libolacommon.la
endif
