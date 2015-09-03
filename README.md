# sourceline

# Description
The aim of the project is to create cross-platform client for popular version control systems (VCS), such as Subversion, Git, Mercurial.
As bug tracking system we are using free redmine server
http://hostedredmine.com/projects/source_line

# Dependencies

Dependencies are stored in src/app/3rdparty folder

## boost
Boost was added as a submodule. To get it use:
```text
git submodule update --init --recursive
```
and you will get modular boost into 3rdparty/boost folder
Refer to git submodules documentation for more information.

# Build

Use Qt5 and compiler that supports at least C++11 features. Qt must be built with the compiler that supports C++11 also.
For example, Qt5 with latest gcc or clang on Linux and Qt5 VS 2013 or Qt5MinGW on Windows.

# Project workflow

## Directory Structure

```text
sourceline
├── docs
└── src
    ├── app
    │   ├── 3rdparty
    │   ├── pluginsupport
    │   ├── resources
    │   ├── settings_dialog
    │   └── ui
    ├── extensionlib
    ├── plugin
    ├──tools
    └── sourceline.pro
```

## Branches, git workflow
Project has at least the two branches master and development. When adding new feature one creates features/feature_name branch from development branch where feature_name can start with task number. Pull requests with features are merged into development branch. Experiment features are in experiments/feature_name branches.

# Licence
The project is licenced under GPL v3.


