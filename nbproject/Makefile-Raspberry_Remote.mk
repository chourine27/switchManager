#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Raspberry_Remote
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/USBRelais.o \
	${OBJECTDIR}/clientudp.o \
	${OBJECTDIR}/fastlogger/fastlogger.o \
	${OBJECTDIR}/gestioncommandes.o \
	${OBJECTDIR}/gestionfichier.o \
	${OBJECTDIR}/gestiongpio.o \
	${OBJECTDIR}/gestionlog.o \
	${OBJECTDIR}/initialisation.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/minuterie.o \
	${OBJECTDIR}/raspberryGPIO.o \
	${OBJECTDIR}/serveurudp.o \
	${OBJECTDIR}/tools.o \
	${OBJECTDIR}/voCoreGPIO.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f3

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/Test_gestioncommandes.o \
	${TESTDIR}/tests/Test_gestionfichier.o \
	${TESTDIR}/tests/Test_gestiongpio.o

# C Compiler Flags
CFLAGS=-pthread -lwiringPi -lwiringPiDev

# CC Compiler Flags
CCFLAGS=-m32
CXXFLAGS=-m32

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/switchmanager

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/switchmanager: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/switchmanager ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/USBRelais.o: USBRelais.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/USBRelais.o USBRelais.c

${OBJECTDIR}/clientudp.o: clientudp.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clientudp.o clientudp.c

${OBJECTDIR}/fastlogger/fastlogger.o: fastlogger/fastlogger.c
	${MKDIR} -p ${OBJECTDIR}/fastlogger
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fastlogger/fastlogger.o fastlogger/fastlogger.c

${OBJECTDIR}/gestioncommandes.o: gestioncommandes.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gestioncommandes.o gestioncommandes.c

${OBJECTDIR}/gestionfichier.o: gestionfichier.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gestionfichier.o gestionfichier.c

${OBJECTDIR}/gestiongpio.o: gestiongpio.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gestiongpio.o gestiongpio.c

${OBJECTDIR}/gestionlog.o: gestionlog.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gestionlog.o gestionlog.c

${OBJECTDIR}/initialisation.o: initialisation.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/initialisation.o initialisation.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/minuterie.o: minuterie.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/minuterie.o minuterie.c

${OBJECTDIR}/raspberryGPIO.o: raspberryGPIO.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raspberryGPIO.o raspberryGPIO.c

${OBJECTDIR}/serveurudp.o: serveurudp.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/serveurudp.o serveurudp.c

${OBJECTDIR}/tools.o: tools.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tools.o tools.c

${OBJECTDIR}/voCoreGPIO.o: voCoreGPIO.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/voCoreGPIO.o voCoreGPIO.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/Test_gestioncommandes.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   `cppunit-config --libs`   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/Test_gestionfichier.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}   `cppunit-config --libs`   

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/Test_gestiongpio.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS}   `cppunit-config --libs`   


${TESTDIR}/tests/Test_gestioncommandes.o: tests/Test_gestioncommandes.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_gestioncommandes.o tests/Test_gestioncommandes.c


${TESTDIR}/tests/Test_gestionfichier.o: tests/Test_gestionfichier.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_gestionfichier.o tests/Test_gestionfichier.c


${TESTDIR}/tests/Test_gestiongpio.o: tests/Test_gestiongpio.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/Test_gestiongpio.o tests/Test_gestiongpio.c


${OBJECTDIR}/USBRelais_nomain.o: ${OBJECTDIR}/USBRelais.o USBRelais.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/USBRelais.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/USBRelais_nomain.o USBRelais.c;\
	else  \
	    ${CP} ${OBJECTDIR}/USBRelais.o ${OBJECTDIR}/USBRelais_nomain.o;\
	fi

${OBJECTDIR}/clientudp_nomain.o: ${OBJECTDIR}/clientudp.o clientudp.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/clientudp.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/clientudp_nomain.o clientudp.c;\
	else  \
	    ${CP} ${OBJECTDIR}/clientudp.o ${OBJECTDIR}/clientudp_nomain.o;\
	fi

${OBJECTDIR}/fastlogger/fastlogger_nomain.o: ${OBJECTDIR}/fastlogger/fastlogger.o fastlogger/fastlogger.c 
	${MKDIR} -p ${OBJECTDIR}/fastlogger
	@NMOUTPUT=`${NM} ${OBJECTDIR}/fastlogger/fastlogger.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fastlogger/fastlogger_nomain.o fastlogger/fastlogger.c;\
	else  \
	    ${CP} ${OBJECTDIR}/fastlogger/fastlogger.o ${OBJECTDIR}/fastlogger/fastlogger_nomain.o;\
	fi

${OBJECTDIR}/gestioncommandes_nomain.o: ${OBJECTDIR}/gestioncommandes.o gestioncommandes.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gestioncommandes.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gestioncommandes_nomain.o gestioncommandes.c;\
	else  \
	    ${CP} ${OBJECTDIR}/gestioncommandes.o ${OBJECTDIR}/gestioncommandes_nomain.o;\
	fi

${OBJECTDIR}/gestionfichier_nomain.o: ${OBJECTDIR}/gestionfichier.o gestionfichier.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gestionfichier.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gestionfichier_nomain.o gestionfichier.c;\
	else  \
	    ${CP} ${OBJECTDIR}/gestionfichier.o ${OBJECTDIR}/gestionfichier_nomain.o;\
	fi

${OBJECTDIR}/gestiongpio_nomain.o: ${OBJECTDIR}/gestiongpio.o gestiongpio.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gestiongpio.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gestiongpio_nomain.o gestiongpio.c;\
	else  \
	    ${CP} ${OBJECTDIR}/gestiongpio.o ${OBJECTDIR}/gestiongpio_nomain.o;\
	fi

${OBJECTDIR}/gestionlog_nomain.o: ${OBJECTDIR}/gestionlog.o gestionlog.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gestionlog.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gestionlog_nomain.o gestionlog.c;\
	else  \
	    ${CP} ${OBJECTDIR}/gestionlog.o ${OBJECTDIR}/gestionlog_nomain.o;\
	fi

${OBJECTDIR}/initialisation_nomain.o: ${OBJECTDIR}/initialisation.o initialisation.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/initialisation.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/initialisation_nomain.o initialisation.c;\
	else  \
	    ${CP} ${OBJECTDIR}/initialisation.o ${OBJECTDIR}/initialisation_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.c;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/minuterie_nomain.o: ${OBJECTDIR}/minuterie.o minuterie.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/minuterie.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/minuterie_nomain.o minuterie.c;\
	else  \
	    ${CP} ${OBJECTDIR}/minuterie.o ${OBJECTDIR}/minuterie_nomain.o;\
	fi

${OBJECTDIR}/raspberryGPIO_nomain.o: ${OBJECTDIR}/raspberryGPIO.o raspberryGPIO.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/raspberryGPIO.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/raspberryGPIO_nomain.o raspberryGPIO.c;\
	else  \
	    ${CP} ${OBJECTDIR}/raspberryGPIO.o ${OBJECTDIR}/raspberryGPIO_nomain.o;\
	fi

${OBJECTDIR}/serveurudp_nomain.o: ${OBJECTDIR}/serveurudp.o serveurudp.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/serveurudp.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/serveurudp_nomain.o serveurudp.c;\
	else  \
	    ${CP} ${OBJECTDIR}/serveurudp.o ${OBJECTDIR}/serveurudp_nomain.o;\
	fi

${OBJECTDIR}/tools_nomain.o: ${OBJECTDIR}/tools.o tools.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tools.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tools_nomain.o tools.c;\
	else  \
	    ${CP} ${OBJECTDIR}/tools.o ${OBJECTDIR}/tools_nomain.o;\
	fi

${OBJECTDIR}/voCoreGPIO_nomain.o: ${OBJECTDIR}/voCoreGPIO.o voCoreGPIO.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/voCoreGPIO.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -DRASPBERRY -DREMOTE -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/voCoreGPIO_nomain.o voCoreGPIO.c;\
	else  \
	    ${CP} ${OBJECTDIR}/voCoreGPIO.o ${OBJECTDIR}/voCoreGPIO_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
