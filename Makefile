#############################################################################
# Makefile for building: STAGR
# Generated by qmake (2.01a) (Qt 4.7.4) on: Tue Mar 20 01:25:19 2012
# Project:  STAGR.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile STAGR.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I. -I/usr/include/python2.7
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lQtGui -lQtCore -lpthread -lpython2.7
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = blastnSettingsDialog.cpp \
		blatSettingsDialog.cpp \
		block.cpp \
		chordDiagram.cpp \
		contigData.cpp \
		hsp.cpp \
		layerArcs.cpp \
		main.cpp \
		MultipleMatchesDialog.cpp \
		multipleMatchesView.cpp \
		pathSettingsDialog.cpp \
		plotLayer.cpp \
		scriptEditDialog.cpp \
		scriptHighlighter.cpp \
		sequenceView.cpp \
		STAGR.cpp \
		Table.cpp moc_blastnSettingsDialog.cpp \
		moc_blatSettingsDialog.cpp \
		moc_chordDiagram.cpp \
		moc_MultipleMatchesDialog.cpp \
		moc_multipleMatchesView.cpp \
		moc_pathSettingsDialog.cpp \
		moc_scriptEditDialog.cpp \
		moc_scriptHighlighter.cpp \
		moc_sequenceView.cpp \
		moc_STAGR.cpp \
		moc_Table.cpp \
		qrc_STAGR.cpp
OBJECTS       = blastnSettingsDialog.o \
		blatSettingsDialog.o \
		block.o \
		chordDiagram.o \
		contigData.o \
		hsp.o \
		layerArcs.o \
		main.o \
		MultipleMatchesDialog.o \
		multipleMatchesView.o \
		pathSettingsDialog.o \
		plotLayer.o \
		scriptEditDialog.o \
		scriptHighlighter.o \
		sequenceView.o \
		STAGR.o \
		Table.o \
		moc_blastnSettingsDialog.o \
		moc_blatSettingsDialog.o \
		moc_chordDiagram.o \
		moc_MultipleMatchesDialog.o \
		moc_multipleMatchesView.o \
		moc_pathSettingsDialog.o \
		moc_scriptEditDialog.o \
		moc_scriptHighlighter.o \
		moc_sequenceView.o \
		moc_STAGR.o \
		moc_Table.o \
		qrc_STAGR.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		STAGR.pro
QMAKE_TARGET  = STAGR
DESTDIR       = 
TARGET        = STAGR

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: STAGR.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile STAGR.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile STAGR.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/STAGR1.0.0 || $(MKDIR) .tmp/STAGR1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/STAGR1.0.0/ && $(COPY_FILE) --parents blastnSettingsDialog.h blatSettingsDialog.h block.h chordDiagram.h contigData.h hsp.h layerArcs.h MultipleMatchesDialog.h multipleMatchesView.h pathSettingsDialog.h plotLayer.h scriptEditDialog.h scriptHighlighter.h sequenceView.h STAGR.h Table.h .tmp/STAGR1.0.0/ && $(COPY_FILE) --parents STAGR.qrc .tmp/STAGR1.0.0/ && $(COPY_FILE) --parents blastnSettingsDialog.cpp blatSettingsDialog.cpp block.cpp chordDiagram.cpp contigData.cpp hsp.cpp layerArcs.cpp main.cpp MultipleMatchesDialog.cpp multipleMatchesView.cpp pathSettingsDialog.cpp plotLayer.cpp scriptEditDialog.cpp scriptHighlighter.cpp sequenceView.cpp STAGR.cpp Table.cpp .tmp/STAGR1.0.0/ && (cd `dirname .tmp/STAGR1.0.0` && $(TAR) STAGR1.0.0.tar STAGR1.0.0 && $(COMPRESS) STAGR1.0.0.tar) && $(MOVE) `dirname .tmp/STAGR1.0.0`/STAGR1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/STAGR1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_blastnSettingsDialog.cpp moc_blatSettingsDialog.cpp moc_chordDiagram.cpp moc_MultipleMatchesDialog.cpp moc_multipleMatchesView.cpp moc_pathSettingsDialog.cpp moc_scriptEditDialog.cpp moc_scriptHighlighter.cpp moc_sequenceView.cpp moc_STAGR.cpp moc_Table.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_blastnSettingsDialog.cpp moc_blatSettingsDialog.cpp moc_chordDiagram.cpp moc_MultipleMatchesDialog.cpp moc_multipleMatchesView.cpp moc_pathSettingsDialog.cpp moc_scriptEditDialog.cpp moc_scriptHighlighter.cpp moc_sequenceView.cpp moc_STAGR.cpp moc_Table.cpp
moc_blastnSettingsDialog.cpp: blastnSettingsDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) blastnSettingsDialog.h -o moc_blastnSettingsDialog.cpp

moc_blatSettingsDialog.cpp: blatSettingsDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) blatSettingsDialog.h -o moc_blatSettingsDialog.cpp

moc_chordDiagram.cpp: plotLayer.h \
		contigData.h \
		layerArcs.h \
		chordDiagram.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) chordDiagram.h -o moc_chordDiagram.cpp

moc_MultipleMatchesDialog.cpp: Table.h \
		hsp.h \
		sequenceView.h \
		block.h \
		multipleMatchesView.h \
		plotLayer.h \
		contigData.h \
		layerArcs.h \
		MultipleMatchesDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) MultipleMatchesDialog.h -o moc_MultipleMatchesDialog.cpp

moc_multipleMatchesView.cpp: hsp.h \
		multipleMatchesView.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) multipleMatchesView.h -o moc_multipleMatchesView.cpp

moc_pathSettingsDialog.cpp: pathSettingsDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) pathSettingsDialog.h -o moc_pathSettingsDialog.cpp

moc_scriptEditDialog.cpp: scriptHighlighter.h \
		scriptEditDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) scriptEditDialog.h -o moc_scriptEditDialog.cpp

moc_scriptHighlighter.cpp: scriptHighlighter.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) scriptHighlighter.h -o moc_scriptHighlighter.cpp

moc_sequenceView.cpp: block.h \
		hsp.h \
		sequenceView.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) sequenceView.h -o moc_sequenceView.cpp

moc_STAGR.cpp: MultipleMatchesDialog.h \
		Table.h \
		hsp.h \
		sequenceView.h \
		block.h \
		multipleMatchesView.h \
		plotLayer.h \
		contigData.h \
		layerArcs.h \
		blastnSettingsDialog.h \
		blatSettingsDialog.h \
		scriptEditDialog.h \
		scriptHighlighter.h \
		pathSettingsDialog.h \
		STAGR.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) STAGR.h -o moc_STAGR.cpp

moc_Table.cpp: hsp.h \
		Table.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Table.h -o moc_Table.cpp

compiler_rcc_make_all: qrc_STAGR.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_STAGR.cpp
qrc_STAGR.cpp: STAGR.qrc \
		MAC.fasta \
		MIC.fasta \
		output2dict.py \
		icons/loadSequencesIcon.png \
		icons/pythonIcon.png \
		icons/stagrSettingsIcon.png \
		icons/settingsIcon.png \
		icons/startIcon.png
	/usr/bin/rcc -name STAGR STAGR.qrc -o qrc_STAGR.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

blastnSettingsDialog.o: blastnSettingsDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o blastnSettingsDialog.o blastnSettingsDialog.cpp

blatSettingsDialog.o: blatSettingsDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o blatSettingsDialog.o blatSettingsDialog.cpp

block.o: block.cpp block.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o block.o block.cpp

chordDiagram.o: chordDiagram.cpp chordDiagram.h \
		plotLayer.h \
		contigData.h \
		layerArcs.h \
		hsp.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o chordDiagram.o chordDiagram.cpp

contigData.o: contigData.cpp contigData.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o contigData.o contigData.cpp

hsp.o: hsp.cpp hsp.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o hsp.o hsp.cpp

layerArcs.o: layerArcs.cpp layerArcs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o layerArcs.o layerArcs.cpp

main.o: main.cpp STAGR.h \
		MultipleMatchesDialog.h \
		Table.h \
		hsp.h \
		sequenceView.h \
		block.h \
		multipleMatchesView.h \
		plotLayer.h \
		contigData.h \
		layerArcs.h \
		blastnSettingsDialog.h \
		blatSettingsDialog.h \
		scriptEditDialog.h \
		scriptHighlighter.h \
		pathSettingsDialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

MultipleMatchesDialog.o: MultipleMatchesDialog.cpp MultipleMatchesDialog.h \
		Table.h \
		hsp.h \
		sequenceView.h \
		block.h \
		multipleMatchesView.h \
		plotLayer.h \
		contigData.h \
		layerArcs.h \
		chordDiagram.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MultipleMatchesDialog.o MultipleMatchesDialog.cpp

multipleMatchesView.o: multipleMatchesView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o multipleMatchesView.o multipleMatchesView.cpp

pathSettingsDialog.o: pathSettingsDialog.cpp pathSettingsDialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o pathSettingsDialog.o pathSettingsDialog.cpp

plotLayer.o: plotLayer.cpp plotLayer.h \
		contigData.h \
		layerArcs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o plotLayer.o plotLayer.cpp

scriptEditDialog.o: scriptEditDialog.cpp scriptHighlighter.h \
		scriptEditDialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o scriptEditDialog.o scriptEditDialog.cpp

scriptHighlighter.o: scriptHighlighter.cpp scriptHighlighter.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o scriptHighlighter.o scriptHighlighter.cpp

sequenceView.o: sequenceView.cpp sequenceView.h \
		block.h \
		hsp.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sequenceView.o sequenceView.cpp

STAGR.o: STAGR.cpp STAGR.h \
		MultipleMatchesDialog.h \
		Table.h \
		hsp.h \
		sequenceView.h \
		block.h \
		multipleMatchesView.h \
		plotLayer.h \
		contigData.h \
		layerArcs.h \
		blastnSettingsDialog.h \
		blatSettingsDialog.h \
		scriptEditDialog.h \
		scriptHighlighter.h \
		pathSettingsDialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o STAGR.o STAGR.cpp

Table.o: Table.cpp Table.h \
		hsp.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Table.o Table.cpp

moc_blastnSettingsDialog.o: moc_blastnSettingsDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_blastnSettingsDialog.o moc_blastnSettingsDialog.cpp

moc_blatSettingsDialog.o: moc_blatSettingsDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_blatSettingsDialog.o moc_blatSettingsDialog.cpp

moc_chordDiagram.o: moc_chordDiagram.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_chordDiagram.o moc_chordDiagram.cpp

moc_MultipleMatchesDialog.o: moc_MultipleMatchesDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MultipleMatchesDialog.o moc_MultipleMatchesDialog.cpp

moc_multipleMatchesView.o: moc_multipleMatchesView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_multipleMatchesView.o moc_multipleMatchesView.cpp

moc_pathSettingsDialog.o: moc_pathSettingsDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_pathSettingsDialog.o moc_pathSettingsDialog.cpp

moc_scriptEditDialog.o: moc_scriptEditDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_scriptEditDialog.o moc_scriptEditDialog.cpp

moc_scriptHighlighter.o: moc_scriptHighlighter.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_scriptHighlighter.o moc_scriptHighlighter.cpp

moc_sequenceView.o: moc_sequenceView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_sequenceView.o moc_sequenceView.cpp

moc_STAGR.o: moc_STAGR.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_STAGR.o moc_STAGR.cpp

moc_Table.o: moc_Table.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Table.o moc_Table.cpp

qrc_STAGR.o: qrc_STAGR.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_STAGR.o qrc_STAGR.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

