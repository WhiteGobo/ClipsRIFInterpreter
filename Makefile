SRC=src
BUILD ?= build
CMAKE=cmake
ASSETPATH ?=brubrubru

TMPDIR = tmp
CLIPSPATHDIRECTORY=${TMPDIR}/clipspatch

CRIFI_SCRIPT_GENERATOR_PATH ?= ${BUILD}/generate_crifi_script/
ENV_GENERATOR=env PATH=$$PATH:${CRIFI_SCRIPT_GENERATOR_PATH}

#eg more logging: (env CMAKE_CONFIGURE_OPT="--log-level=DEBUG" make)
CMAKE_CONFIGURE_OPT ?=
CMAKE_CONFIGURE_OPT += -D REL_ASSETPATH_CLIPSSCRIPTS=${ASSETPATH}
TESTFILTER ?=
ifdef TESTFILTER
CTEST_OPT = -R ${TESTFILTER}
endif

default: configure build test

include resources.mk

.PHONY: configure
configure:
	${CMAKE} -S ${SRC} -B ${BUILD} ${CMAKE_CONFIGURE_OPT}

.PHONY: build
build:
	${CMAKE} --build ${BUILD}

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
