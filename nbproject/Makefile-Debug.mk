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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/gestioncommandes.o \
	${OBJECTDIR}/gestionfichier.o \
	${OBJECTDIR}/gestiongpio.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/serveurudp.o \
	${OBJECTDIR}/voCoreGPIO.o


# C Compiler Flags
CFLAGS=-m32 -pthread

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

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

${OBJECTDIR}/gestioncommandes.o: gestioncommandes.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gestioncommandes.o gestioncommandes.c

${OBJECTDIR}/gestionfichier.o: gestionfichier.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gestionfichier.o gestionfichier.c

${OBJECTDIR}/gestiongpio.o: gestiongpio.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gestiongpio.o gestiongpio.c

${OBJECTDIR}/main.o: main.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/serveurudp.o: serveurudp.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/serveurudp.o serveurudp.c

${OBJECTDIR}/voCoreGPIO.o: voCoreGPIO.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DDEBUG -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/voCoreGPIO.o voCoreGPIO.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
