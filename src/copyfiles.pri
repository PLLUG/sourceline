# This pri file copy files COPYFILES_FILELIST from project in COPYFILES_PATH to dir COPYFILES_TARGET_DIR
# COPYFILES_PATH should contain full pathes to files
#COPYFILES_PATH =
#COPYFILES_FILELIST =
#COPYFILES_TARGET_DIR =

## === define copy files for installation and build ===
copytarget.path    = $$COPYFILES_PATH
copytarget.files  += $$COPYFILES_FILELIST

## wildcard for filename1 filename2 filename3 ...
## === os specific dir separator ===
win32: copytarget.files ~= s,/,\\,g

## === copy compiler for makefile ===
DirSep = /
win32: DirSep = \\

# TODO: move to separate function
#for(f,copytarget.files) {
#    if ()
#    tmp += $$PWD$$DirSep$${f} ## make absolute paths
#}
#copycompiler.input        = tmp

copycompiler.input        = copytarget.files

# TODO: move to separate pri file (to make more re usable)
isEmpty(DESTDIR):DESTDIR=.
win32 {
    COPYFILES_TARGET_DIR = $$replace(COPYFILES_TARGET_DIR, /, \\)
}
copycompiler.output       = $$COPYFILES_TARGET_DIR$$DirSep${QMAKE_FILE_BASE}${QMAKE_FILE_EXT}
copycompiler.commands     = $(COPY_FILE) ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copycompiler.CONFIG       = no_link no_clean
## other CONFIG options are: depends explicit_dependencies target_predeps

copycompiler.variable_out = QMAKE_DISTCLEAN
QMAKE_EXTRA_COMPILERS += copycompiler

## == makefile copy target ===
copyfiles.recurse_target = compiler_copycompiler_make_all
copyfiles.depends        = $$copyfiles.recurse_target
copyfiles.CONFIG        += recursive

QMAKE_EXTRA_TARGETS += copyfiles
PRE_TARGETDEPS     += copyfiles ## copy files after source compilation

INSTALLS += copytarget
