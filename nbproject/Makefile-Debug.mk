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
	${OBJECTDIR}/auth/authmanager.o \
	${OBJECTDIR}/fortest.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/mainhandler.o \
	${OBJECTDIR}/network/itransport.o \
	${OBJECTDIR}/network/tcpserver.o \
	${OBJECTDIR}/network/tcpsocket.o \
	${OBJECTDIR}/protocol/authprotocoloutgoingcommand.o \
	${OBJECTDIR}/protocol/command.o \
	${OBJECTDIR}/protocol/hardwareprotocol.o \
	${OBJECTDIR}/protocol/hardwareprotocolfactory.o \
	${OBJECTDIR}/protocol/hardwareprotocolpacketparser.o \
	${OBJECTDIR}/protocol/pingprotocolincommingcommand.o \
	${OBJECTDIR}/timer/itimer.o \
	${OBJECTDIR}/timer/timerfactory.o \
	${OBJECTDIR}/uuid.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-pthread -llua5.3 -lev -luuid -lcrypto

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rewriteclient

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rewriteclient: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rewriteclient ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/auth/authmanager.o: auth/authmanager.cpp
	${MKDIR} -p ${OBJECTDIR}/auth
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/auth/authmanager.o auth/authmanager.cpp

${OBJECTDIR}/fortest.o: fortest.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fortest.o fortest.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/mainhandler.o: mainhandler.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mainhandler.o mainhandler.cpp

${OBJECTDIR}/network/itransport.o: network/itransport.cpp
	${MKDIR} -p ${OBJECTDIR}/network
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/network/itransport.o network/itransport.cpp

${OBJECTDIR}/network/tcpserver.o: network/tcpserver.cpp
	${MKDIR} -p ${OBJECTDIR}/network
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/network/tcpserver.o network/tcpserver.cpp

${OBJECTDIR}/network/tcpsocket.o: network/tcpsocket.cpp
	${MKDIR} -p ${OBJECTDIR}/network
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/network/tcpsocket.o network/tcpsocket.cpp

${OBJECTDIR}/protocol/authprotocoloutgoingcommand.o: protocol/authprotocoloutgoingcommand.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/authprotocoloutgoingcommand.o protocol/authprotocoloutgoingcommand.cpp

${OBJECTDIR}/protocol/command.o: protocol/command.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/command.o protocol/command.cpp

${OBJECTDIR}/protocol/hardwareprotocol.o: protocol/hardwareprotocol.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/hardwareprotocol.o protocol/hardwareprotocol.cpp

${OBJECTDIR}/protocol/hardwareprotocolfactory.o: protocol/hardwareprotocolfactory.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/hardwareprotocolfactory.o protocol/hardwareprotocolfactory.cpp

${OBJECTDIR}/protocol/hardwareprotocolpacketparser.o: protocol/hardwareprotocolpacketparser.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/hardwareprotocolpacketparser.o protocol/hardwareprotocolpacketparser.cpp

${OBJECTDIR}/protocol/pingprotocolincommingcommand.o: protocol/pingprotocolincommingcommand.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/pingprotocolincommingcommand.o protocol/pingprotocolincommingcommand.cpp

${OBJECTDIR}/timer/itimer.o: timer/itimer.cpp
	${MKDIR} -p ${OBJECTDIR}/timer
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/timer/itimer.o timer/itimer.cpp

${OBJECTDIR}/timer/timerfactory.o: timer/timerfactory.cpp
	${MKDIR} -p ${OBJECTDIR}/timer
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/timer/timerfactory.o timer/timerfactory.cpp

${OBJECTDIR}/uuid.o: uuid.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/uuid.o uuid.cpp

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
