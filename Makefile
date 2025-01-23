SRC=src
BUILD ?= build
CMAKE=cmake
ASSETPATH ?=brubrubru
DESTDIR ?=

TMPDIR = tmp
CLIPSPATHDIRECTORY=${TMPDIR}/clipspatch

CRIFI_SCRIPT_GENERATOR_PATH ?= ${BUILD}/generate_crifi_script/
ENV_GENERATOR=env PATH=$$PATH:${CRIFI_SCRIPT_GENERATOR_PATH}

CMAKE_BUILD_OPT ?=
CMAKE_CONFIGURE_OPT ?=
ifdef V
	CMAKE_BUILD_OPT += -v
	#CMAKE_CONFIGURE_OPT += --log-level=DEBUG
endif
CMAKE_CONFIGURE_OPT += -D REL_ASSETPATH_CLIPSSCRIPTS=${ASSETPATH}
CMAKE_CONFIGURE_OPT += -DBUILD_SHARED_LIBS=ON
ifdef prefix
	CMAKE_CONFIGURE_OPT += --install-prefix ${prefix}
endif
ifdef CLIPS_HEADER
	CMAKE_CONFIGURE_OPT += -DCLIPS_HEADER=${CLIPS_HEADER} 
endif
ifdef CLIPS_LIBRARY
	CMAKE_CONFIGURE_OPT += -DCLIPS_LIBRARY=${CLIPS_LIBRARY} 
endif
ifdef LINKED_CLIPS_LIB
	CMAKE_CONFIGURE_OPT += -DLINKED_CLIPS_LIB=${LINKED_CLIPS_LIB}
endif


CTEST_OPT =
ifdef TESTFILTER
CTEST_OPT += -R ${TESTFILTER}
endif

MAKE_INSTALL_OPT ?= 
ifdef DESTDIR
#MAKE_INSTALL_OPT += --prefix $(realpath ${DESTDIR})
endif

default: configure build test

QQTEST = qqtestinstall
tt:
	-rm -rf ${QQTEST}
	mkdir -p ${QQTEST}
	env DESTDIR=${QQTEST} ${CMAKE} --install ${BUILD}

install:
	${CMAKE} --install ${BUILD} ${MAKE_INSTALL_OPT}
	#${CMAKE} DESTDIR=${DESTDIR} --build ${BUILD} --target install --config debug
.PHONY: install

include resources.mk

configure:
	${CMAKE}  -S ${SRC} -B ${BUILD} ${CMAKE_CONFIGURE_OPT}
.PHONY: configure

build:
	${CMAKE} --build ${BUILD} ${CMAKE_BUILD_OPT}
.PHONY: build

.PHONY: test
test: configure build ${BUILD}/${ASSETPATH}
	echo "path to assets: $<"
	cd ${BUILD} && env ASSETPATH_CLIPSSCRIPTS=$(realpath $<) ctest --output-on-failure ${CTEST_OPT}

.PHONY: memtest
memtest: configure build ${BUILD}/${ASSETPATH}
	echo "path to assets: $<"
	cd ${BUILD} && env ASSETPATH_CLIPSSCRIPTS=$(realpath $<) ctest -T memcheck --output-on-failure ${CTEST_OPT}

.PHONY: clean
clean:
	-rm -rf ${BUILD}
	-rm -rf ${TMPDIR}


.PHONY: doc
doc:
	cd doc && doxygen


${TMPDIR}/clips_core_source_641.zip:
	mkdir -p ${TMPDIR}
	wget -P ${TMPDIR} https://sourceforge.net/projects/clipsrules/files/CLIPS/6.4.1/clips_core_source_641.zip

#CLIPSPATCHFILES=$(shell find ${CLIPSPATHDIRECTORY}/ -type f)
CLIPSPATCHFILES=$(wildcard ${CLIPSPATHDIRECTORY}/original/*) $(wildcard ${CLIPSPATHDIRECTORY}/clips-src/*)
CURRENTPATCH=src/clips_interface/clips.patch

${CLIPSPATHDIRECTORY}: ${TMPDIR}/clips_core_source_641.zip ${CURRENTPATCH}
	mkdir -p ${CLIPSPATHDIRECTORY}/
	unzip $< -d ${CLIPSPATHDIRECTORY}/
	-rm -rf ${CLIPSPATHDIRECTORY}/clips-src
	mv ${CLIPSPATHDIRECTORY}/clips_core_source_641 ${CLIPSPATHDIRECTORY}/clips-src
	patch -s -p0 -d ${CLIPSPATHDIRECTORY}/ < ${CURRENTPATCH}
	unzip $< -d ${CLIPSPATHDIRECTORY}/
	mv ${CLIPSPATHDIRECTORY}/clips_core_source_641 ${CLIPSPATHDIRECTORY}/original

${TMPDIR}/clips.patch: ${CLIPSPATHDIRECTORY} ${CLIPSPATCHFILES}
	echo ${CLIPSPATCHFILES}
	-cd ${CLIPSPATHDIRECTORY}/ && diff -ruN original/ clips-src/ > ../clips.patch


.PHONY: opendoc
opendoc:
	xdg-open doc/html/index.html
