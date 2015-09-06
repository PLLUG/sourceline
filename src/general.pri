SL_ROOT = $$clean_path($$PWD/..)
DEFINES += SL_ROOT=$$SL_ROOT

SL_BIN_DIRECTORY = $$clean_path($$SL_ROOT/bin)
message(SourceLine bin directory: $$SL_BIN_DIRECTORY)
DEFINES += SL_BIN_DIRECTORY=$$SL_BIN_DIRECTORY

SL_LIB_DIRECTORY = $$clean_path($$SL_ROOT/lib)
message(SourceLine lib directory: $$SL_LIB_DIRECTORY)
DEFINES += SL_LIB_DIRECTORY=$$SL_LIB_DIRECTORY

SL_INCLUDE_DIRECTORY = $$clean_path($$SL_ROOT/include)
message(SourceLine include directory: $$SL_INCLUDE_DIRECTORY)

SL_INCLUDE_PLUGINAPI_DIRECTORY = $$clean_path($$SL_INCLUDE_DIRECTORY/pluginapi)
message(SourceLine pluginapi directory: $$SL_INCLUDE_PLUGINAPI_DIRECTORY)

# Pro file is a part of source line project structure
CONFIG += sl_project

# Use latest standard
CONFIG += c++14

INCLUDEPATH += $$SL_INCLUDE_DIRECTORY
INCLUDEPATH += $$SL_INCLUDE_PLUGINAPI_DIRECTORY

LIBS += -L$$SL_LIB_DIRECTORY
