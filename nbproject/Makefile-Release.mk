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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/auth/authmanager.o \
	${OBJECTDIR}/cancelnotifyincommingcommandhandler.o \
	${OBJECTDIR}/file_watcher/filecontenteventhandler.o \
	${OBJECTDIR}/file_watcher/filewatcher.o \
	${OBJECTDIR}/filedownloader.o \
	${OBJECTDIR}/fortest.o \
	${OBJECTDIR}/gpio/gpiomanager.o \
	${OBJECTDIR}/gpio/gpiothread.o \
	${OBJECTDIR}/gpio/luatogpiomediator.o \
	${OBJECTDIR}/hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand.o \
	${OBJECTDIR}/hardwarestatuses/hardwarestatusesmanager.o \
	${OBJECTDIR}/hardwarestatuses/hardwarestatusestolualmediator.o \
	${OBJECTDIR}/hardwarestatuses/hardwarestatusestoprotocolmediator.o \
	${OBJECTDIR}/hardwarestatuses/requesthardwarestatusesincommingcommandhandler.o \
	${OBJECTDIR}/jsonfilesettings.o \
	${OBJECTDIR}/logger.o \
	${OBJECTDIR}/lua/emitsignalifhappenshandler.o \
	${OBJECTDIR}/lua/emitsignalluaevent.o \
	${OBJECTDIR}/lua/iluaeventforifhappenshandler.o \
	${OBJECTDIR}/lua/iluafunctionregistrator.o \
	${OBJECTDIR}/lua/logmessageluaevent.o \
	${OBJECTDIR}/lua/luascript.o \
	${OBJECTDIR}/lua/luascriptmanager.o \
	${OBJECTDIR}/lua/outgoingmessageluaevent.o \
	${OBJECTDIR}/lua/playlocalfilerequestluaevent.o \
	${OBJECTDIR}/lua/playnetworkaudiorequestluaevent.o \
	${OBJECTDIR}/lua/scriptfinishedluaevent.o \
	${OBJECTDIR}/lua/scriptstartedluaevent.o \
	${OBJECTDIR}/lua/sethardwarestatusesluaevent.o \
	${OBJECTDIR}/lua/stoplocalaudiorequestluaevent.o \
	${OBJECTDIR}/lua/stopnetworkaudiorequestluaevent.o \
	${OBJECTDIR}/luatoaudiomediator.o \
	${OBJECTDIR}/luatonetworkstreammediator.o \
	${OBJECTDIR}/luatoprotocolmediator.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/mainhandler.o \
	${OBJECTDIR}/network/itransport.o \
	${OBJECTDIR}/network/tcpserver.o \
	${OBJECTDIR}/network/tcpsocket.o \
	${OBJECTDIR}/networkaudio/networkaudioifhappenshandler.o \
	${OBJECTDIR}/networkaudio/networkaudiomanager.o \
	${OBJECTDIR}/networkaudio/networkaudothreadworker.o \
	${OBJECTDIR}/networkaudio/notifystatuschangedprotocoloutgoingcommand.o \
	${OBJECTDIR}/protocol/authprotocoloutgoingcommand.o \
	${OBJECTDIR}/protocol/command.o \
	${OBJECTDIR}/protocol/finishscriptprotocoloutgoingcommand.o \
	${OBJECTDIR}/protocol/hardwareprotocol.o \
	${OBJECTDIR}/protocol/hardwareprotocolfactory.o \
	${OBJECTDIR}/protocol/hardwareprotocolpacketparser.o \
	${OBJECTDIR}/protocol/outgoingmessageprotocolcommand.o \
	${OBJECTDIR}/protocol/pingincommingcommandhandler.o \
	${OBJECTDIR}/protocol/pingprotocoloutgoingcommand.o \
	${OBJECTDIR}/protocol/startnotifyincommingcommandhandler.o \
	${OBJECTDIR}/protocol/startscriptprotocoloutgoingcommand.o \
	${OBJECTDIR}/soundmanager.o \
	${OBJECTDIR}/soundmanagerifhappenshandler.o \
	${OBJECTDIR}/timer/itimer.o \
	${OBJECTDIR}/timer/timerfactory.o \
	${OBJECTDIR}/uuid.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/tst_luascript.o

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
LDLIBSOPTIONS=-pthread -llua5.3-c++ -lev -luuid -lcrypto -lportaudio

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sonet_server

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sonet_server: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sonet_server ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/auth/authmanager.o: auth/authmanager.cpp
	${MKDIR} -p ${OBJECTDIR}/auth
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/auth/authmanager.o auth/authmanager.cpp

${OBJECTDIR}/cancelnotifyincommingcommandhandler.o: cancelnotifyincommingcommandhandler.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cancelnotifyincommingcommandhandler.o cancelnotifyincommingcommandhandler.cpp

${OBJECTDIR}/file_watcher/filecontenteventhandler.o: file_watcher/filecontenteventhandler.cpp
	${MKDIR} -p ${OBJECTDIR}/file_watcher
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/file_watcher/filecontenteventhandler.o file_watcher/filecontenteventhandler.cpp

${OBJECTDIR}/file_watcher/filewatcher.o: file_watcher/filewatcher.cpp
	${MKDIR} -p ${OBJECTDIR}/file_watcher
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/file_watcher/filewatcher.o file_watcher/filewatcher.cpp

${OBJECTDIR}/filedownloader.o: filedownloader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/filedownloader.o filedownloader.cpp

${OBJECTDIR}/fortest.o: fortest.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fortest.o fortest.cpp

${OBJECTDIR}/gpio/gpiomanager.o: gpio/gpiomanager.cpp
	${MKDIR} -p ${OBJECTDIR}/gpio
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gpio/gpiomanager.o gpio/gpiomanager.cpp

${OBJECTDIR}/gpio/gpiothread.o: gpio/gpiothread.cpp
	${MKDIR} -p ${OBJECTDIR}/gpio
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gpio/gpiothread.o gpio/gpiothread.cpp

${OBJECTDIR}/gpio/luatogpiomediator.o: gpio/luatogpiomediator.cpp
	${MKDIR} -p ${OBJECTDIR}/gpio
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gpio/luatogpiomediator.o gpio/luatogpiomediator.cpp

${OBJECTDIR}/hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand.o: hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand.cpp
	${MKDIR} -p ${OBJECTDIR}/hardwarestatuses
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand.o hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand.cpp

${OBJECTDIR}/hardwarestatuses/hardwarestatusesmanager.o: hardwarestatuses/hardwarestatusesmanager.cpp
	${MKDIR} -p ${OBJECTDIR}/hardwarestatuses
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hardwarestatuses/hardwarestatusesmanager.o hardwarestatuses/hardwarestatusesmanager.cpp

${OBJECTDIR}/hardwarestatuses/hardwarestatusestolualmediator.o: hardwarestatuses/hardwarestatusestolualmediator.cpp
	${MKDIR} -p ${OBJECTDIR}/hardwarestatuses
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hardwarestatuses/hardwarestatusestolualmediator.o hardwarestatuses/hardwarestatusestolualmediator.cpp

${OBJECTDIR}/hardwarestatuses/hardwarestatusestoprotocolmediator.o: hardwarestatuses/hardwarestatusestoprotocolmediator.cpp
	${MKDIR} -p ${OBJECTDIR}/hardwarestatuses
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hardwarestatuses/hardwarestatusestoprotocolmediator.o hardwarestatuses/hardwarestatusestoprotocolmediator.cpp

${OBJECTDIR}/hardwarestatuses/requesthardwarestatusesincommingcommandhandler.o: hardwarestatuses/requesthardwarestatusesincommingcommandhandler.cpp
	${MKDIR} -p ${OBJECTDIR}/hardwarestatuses
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hardwarestatuses/requesthardwarestatusesincommingcommandhandler.o hardwarestatuses/requesthardwarestatusesincommingcommandhandler.cpp

${OBJECTDIR}/jsonfilesettings.o: jsonfilesettings.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/jsonfilesettings.o jsonfilesettings.cpp

${OBJECTDIR}/logger.o: logger.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/logger.o logger.cpp

${OBJECTDIR}/lua/emitsignalifhappenshandler.o: lua/emitsignalifhappenshandler.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/emitsignalifhappenshandler.o lua/emitsignalifhappenshandler.cpp

${OBJECTDIR}/lua/emitsignalluaevent.o: lua/emitsignalluaevent.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/emitsignalluaevent.o lua/emitsignalluaevent.cpp

${OBJECTDIR}/lua/iluaeventforifhappenshandler.o: lua/iluaeventforifhappenshandler.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/iluaeventforifhappenshandler.o lua/iluaeventforifhappenshandler.cpp

${OBJECTDIR}/lua/iluafunctionregistrator.o: lua/iluafunctionregistrator.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/iluafunctionregistrator.o lua/iluafunctionregistrator.cpp

${OBJECTDIR}/lua/logmessageluaevent.o: lua/logmessageluaevent.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/logmessageluaevent.o lua/logmessageluaevent.cpp

${OBJECTDIR}/lua/luascript.o: lua/luascript.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/luascript.o lua/luascript.cpp

${OBJECTDIR}/lua/luascriptmanager.o: lua/luascriptmanager.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/luascriptmanager.o lua/luascriptmanager.cpp

${OBJECTDIR}/lua/outgoingmessageluaevent.o: lua/outgoingmessageluaevent.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/outgoingmessageluaevent.o lua/outgoingmessageluaevent.cpp

${OBJECTDIR}/lua/playlocalfilerequestluaevent.o: lua/playlocalfilerequestluaevent.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/playlocalfilerequestluaevent.o lua/playlocalfilerequestluaevent.cpp

${OBJECTDIR}/lua/playnetworkaudiorequestluaevent.o: lua/playnetworkaudiorequestluaevent.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/playnetworkaudiorequestluaevent.o lua/playnetworkaudiorequestluaevent.cpp

${OBJECTDIR}/lua/scriptfinishedluaevent.o: lua/scriptfinishedluaevent.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/scriptfinishedluaevent.o lua/scriptfinishedluaevent.cpp

${OBJECTDIR}/lua/scriptstartedluaevent.o: lua/scriptstartedluaevent.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/scriptstartedluaevent.o lua/scriptstartedluaevent.cpp

${OBJECTDIR}/lua/sethardwarestatusesluaevent.o: lua/sethardwarestatusesluaevent.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/sethardwarestatusesluaevent.o lua/sethardwarestatusesluaevent.cpp

${OBJECTDIR}/lua/stoplocalaudiorequestluaevent.o: lua/stoplocalaudiorequestluaevent.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/stoplocalaudiorequestluaevent.o lua/stoplocalaudiorequestluaevent.cpp

${OBJECTDIR}/lua/stopnetworkaudiorequestluaevent.o: lua/stopnetworkaudiorequestluaevent.cpp
	${MKDIR} -p ${OBJECTDIR}/lua
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/stopnetworkaudiorequestluaevent.o lua/stopnetworkaudiorequestluaevent.cpp

${OBJECTDIR}/luatoaudiomediator.o: luatoaudiomediator.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/luatoaudiomediator.o luatoaudiomediator.cpp

${OBJECTDIR}/luatonetworkstreammediator.o: luatonetworkstreammediator.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/luatonetworkstreammediator.o luatonetworkstreammediator.cpp

${OBJECTDIR}/luatoprotocolmediator.o: luatoprotocolmediator.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/luatoprotocolmediator.o luatoprotocolmediator.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/mainhandler.o: mainhandler.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mainhandler.o mainhandler.cpp

${OBJECTDIR}/network/itransport.o: network/itransport.cpp
	${MKDIR} -p ${OBJECTDIR}/network
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/network/itransport.o network/itransport.cpp

${OBJECTDIR}/network/tcpserver.o: network/tcpserver.cpp
	${MKDIR} -p ${OBJECTDIR}/network
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/network/tcpserver.o network/tcpserver.cpp

${OBJECTDIR}/network/tcpsocket.o: network/tcpsocket.cpp
	${MKDIR} -p ${OBJECTDIR}/network
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/network/tcpsocket.o network/tcpsocket.cpp

${OBJECTDIR}/networkaudio/networkaudioifhappenshandler.o: networkaudio/networkaudioifhappenshandler.cpp
	${MKDIR} -p ${OBJECTDIR}/networkaudio
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/networkaudio/networkaudioifhappenshandler.o networkaudio/networkaudioifhappenshandler.cpp

${OBJECTDIR}/networkaudio/networkaudiomanager.o: networkaudio/networkaudiomanager.cpp
	${MKDIR} -p ${OBJECTDIR}/networkaudio
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/networkaudio/networkaudiomanager.o networkaudio/networkaudiomanager.cpp

${OBJECTDIR}/networkaudio/networkaudothreadworker.o: networkaudio/networkaudothreadworker.cpp
	${MKDIR} -p ${OBJECTDIR}/networkaudio
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/networkaudio/networkaudothreadworker.o networkaudio/networkaudothreadworker.cpp

${OBJECTDIR}/networkaudio/notifystatuschangedprotocoloutgoingcommand.o: networkaudio/notifystatuschangedprotocoloutgoingcommand.cpp
	${MKDIR} -p ${OBJECTDIR}/networkaudio
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/networkaudio/notifystatuschangedprotocoloutgoingcommand.o networkaudio/notifystatuschangedprotocoloutgoingcommand.cpp

${OBJECTDIR}/protocol/authprotocoloutgoingcommand.o: protocol/authprotocoloutgoingcommand.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/authprotocoloutgoingcommand.o protocol/authprotocoloutgoingcommand.cpp

${OBJECTDIR}/protocol/command.o: protocol/command.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/command.o protocol/command.cpp

${OBJECTDIR}/protocol/finishscriptprotocoloutgoingcommand.o: protocol/finishscriptprotocoloutgoingcommand.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/finishscriptprotocoloutgoingcommand.o protocol/finishscriptprotocoloutgoingcommand.cpp

${OBJECTDIR}/protocol/hardwareprotocol.o: protocol/hardwareprotocol.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/hardwareprotocol.o protocol/hardwareprotocol.cpp

${OBJECTDIR}/protocol/hardwareprotocolfactory.o: protocol/hardwareprotocolfactory.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/hardwareprotocolfactory.o protocol/hardwareprotocolfactory.cpp

${OBJECTDIR}/protocol/hardwareprotocolpacketparser.o: protocol/hardwareprotocolpacketparser.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/hardwareprotocolpacketparser.o protocol/hardwareprotocolpacketparser.cpp

${OBJECTDIR}/protocol/outgoingmessageprotocolcommand.o: protocol/outgoingmessageprotocolcommand.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/outgoingmessageprotocolcommand.o protocol/outgoingmessageprotocolcommand.cpp

${OBJECTDIR}/protocol/pingincommingcommandhandler.o: protocol/pingincommingcommandhandler.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/pingincommingcommandhandler.o protocol/pingincommingcommandhandler.cpp

${OBJECTDIR}/protocol/pingprotocoloutgoingcommand.o: protocol/pingprotocoloutgoingcommand.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/pingprotocoloutgoingcommand.o protocol/pingprotocoloutgoingcommand.cpp

${OBJECTDIR}/protocol/startnotifyincommingcommandhandler.o: protocol/startnotifyincommingcommandhandler.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/startnotifyincommingcommandhandler.o protocol/startnotifyincommingcommandhandler.cpp

${OBJECTDIR}/protocol/startscriptprotocoloutgoingcommand.o: protocol/startscriptprotocoloutgoingcommand.cpp
	${MKDIR} -p ${OBJECTDIR}/protocol
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/startscriptprotocoloutgoingcommand.o protocol/startscriptprotocoloutgoingcommand.cpp

${OBJECTDIR}/soundmanager.o: soundmanager.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/soundmanager.o soundmanager.cpp

${OBJECTDIR}/soundmanagerifhappenshandler.o: soundmanagerifhappenshandler.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/soundmanagerifhappenshandler.o soundmanagerifhappenshandler.cpp

${OBJECTDIR}/timer/itimer.o: timer/itimer.cpp
	${MKDIR} -p ${OBJECTDIR}/timer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/timer/itimer.o timer/itimer.cpp

${OBJECTDIR}/timer/timerfactory.o: timer/timerfactory.cpp
	${MKDIR} -p ${OBJECTDIR}/timer
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/timer/timerfactory.o timer/timerfactory.cpp

${OBJECTDIR}/uuid.o: uuid.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/uuid.o uuid.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/tst_luascript.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   -lgtest -lgmock 


${TESTDIR}/tests/tst_luascript.o: tests/tst_luascript.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/tst_luascript.o tests/tst_luascript.cpp


${OBJECTDIR}/auth/authmanager_nomain.o: ${OBJECTDIR}/auth/authmanager.o auth/authmanager.cpp 
	${MKDIR} -p ${OBJECTDIR}/auth
	@NMOUTPUT=`${NM} ${OBJECTDIR}/auth/authmanager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/auth/authmanager_nomain.o auth/authmanager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/auth/authmanager.o ${OBJECTDIR}/auth/authmanager_nomain.o;\
	fi

${OBJECTDIR}/cancelnotifyincommingcommandhandler_nomain.o: ${OBJECTDIR}/cancelnotifyincommingcommandhandler.o cancelnotifyincommingcommandhandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cancelnotifyincommingcommandhandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cancelnotifyincommingcommandhandler_nomain.o cancelnotifyincommingcommandhandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cancelnotifyincommingcommandhandler.o ${OBJECTDIR}/cancelnotifyincommingcommandhandler_nomain.o;\
	fi

${OBJECTDIR}/file_watcher/filecontenteventhandler_nomain.o: ${OBJECTDIR}/file_watcher/filecontenteventhandler.o file_watcher/filecontenteventhandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/file_watcher
	@NMOUTPUT=`${NM} ${OBJECTDIR}/file_watcher/filecontenteventhandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/file_watcher/filecontenteventhandler_nomain.o file_watcher/filecontenteventhandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/file_watcher/filecontenteventhandler.o ${OBJECTDIR}/file_watcher/filecontenteventhandler_nomain.o;\
	fi

${OBJECTDIR}/file_watcher/filewatcher_nomain.o: ${OBJECTDIR}/file_watcher/filewatcher.o file_watcher/filewatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/file_watcher
	@NMOUTPUT=`${NM} ${OBJECTDIR}/file_watcher/filewatcher.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/file_watcher/filewatcher_nomain.o file_watcher/filewatcher.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/file_watcher/filewatcher.o ${OBJECTDIR}/file_watcher/filewatcher_nomain.o;\
	fi

${OBJECTDIR}/filedownloader_nomain.o: ${OBJECTDIR}/filedownloader.o filedownloader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/filedownloader.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/filedownloader_nomain.o filedownloader.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/filedownloader.o ${OBJECTDIR}/filedownloader_nomain.o;\
	fi

${OBJECTDIR}/fortest_nomain.o: ${OBJECTDIR}/fortest.o fortest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/fortest.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fortest_nomain.o fortest.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/fortest.o ${OBJECTDIR}/fortest_nomain.o;\
	fi

${OBJECTDIR}/gpio/gpiomanager_nomain.o: ${OBJECTDIR}/gpio/gpiomanager.o gpio/gpiomanager.cpp 
	${MKDIR} -p ${OBJECTDIR}/gpio
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gpio/gpiomanager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gpio/gpiomanager_nomain.o gpio/gpiomanager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/gpio/gpiomanager.o ${OBJECTDIR}/gpio/gpiomanager_nomain.o;\
	fi

${OBJECTDIR}/gpio/gpiothread_nomain.o: ${OBJECTDIR}/gpio/gpiothread.o gpio/gpiothread.cpp 
	${MKDIR} -p ${OBJECTDIR}/gpio
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gpio/gpiothread.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gpio/gpiothread_nomain.o gpio/gpiothread.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/gpio/gpiothread.o ${OBJECTDIR}/gpio/gpiothread_nomain.o;\
	fi

${OBJECTDIR}/gpio/luatogpiomediator_nomain.o: ${OBJECTDIR}/gpio/luatogpiomediator.o gpio/luatogpiomediator.cpp 
	${MKDIR} -p ${OBJECTDIR}/gpio
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gpio/luatogpiomediator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gpio/luatogpiomediator_nomain.o gpio/luatogpiomediator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/gpio/luatogpiomediator.o ${OBJECTDIR}/gpio/luatogpiomediator_nomain.o;\
	fi

${OBJECTDIR}/hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand_nomain.o: ${OBJECTDIR}/hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand.o hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/hardwarestatuses
	@NMOUTPUT=`${NM} ${OBJECTDIR}/hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand_nomain.o hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand.o ${OBJECTDIR}/hardwarestatuses/hardwarestatuschangedprotocoloutgoingcommand_nomain.o;\
	fi

${OBJECTDIR}/hardwarestatuses/hardwarestatusesmanager_nomain.o: ${OBJECTDIR}/hardwarestatuses/hardwarestatusesmanager.o hardwarestatuses/hardwarestatusesmanager.cpp 
	${MKDIR} -p ${OBJECTDIR}/hardwarestatuses
	@NMOUTPUT=`${NM} ${OBJECTDIR}/hardwarestatuses/hardwarestatusesmanager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hardwarestatuses/hardwarestatusesmanager_nomain.o hardwarestatuses/hardwarestatusesmanager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/hardwarestatuses/hardwarestatusesmanager.o ${OBJECTDIR}/hardwarestatuses/hardwarestatusesmanager_nomain.o;\
	fi

${OBJECTDIR}/hardwarestatuses/hardwarestatusestolualmediator_nomain.o: ${OBJECTDIR}/hardwarestatuses/hardwarestatusestolualmediator.o hardwarestatuses/hardwarestatusestolualmediator.cpp 
	${MKDIR} -p ${OBJECTDIR}/hardwarestatuses
	@NMOUTPUT=`${NM} ${OBJECTDIR}/hardwarestatuses/hardwarestatusestolualmediator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hardwarestatuses/hardwarestatusestolualmediator_nomain.o hardwarestatuses/hardwarestatusestolualmediator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/hardwarestatuses/hardwarestatusestolualmediator.o ${OBJECTDIR}/hardwarestatuses/hardwarestatusestolualmediator_nomain.o;\
	fi

${OBJECTDIR}/hardwarestatuses/hardwarestatusestoprotocolmediator_nomain.o: ${OBJECTDIR}/hardwarestatuses/hardwarestatusestoprotocolmediator.o hardwarestatuses/hardwarestatusestoprotocolmediator.cpp 
	${MKDIR} -p ${OBJECTDIR}/hardwarestatuses
	@NMOUTPUT=`${NM} ${OBJECTDIR}/hardwarestatuses/hardwarestatusestoprotocolmediator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hardwarestatuses/hardwarestatusestoprotocolmediator_nomain.o hardwarestatuses/hardwarestatusestoprotocolmediator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/hardwarestatuses/hardwarestatusestoprotocolmediator.o ${OBJECTDIR}/hardwarestatuses/hardwarestatusestoprotocolmediator_nomain.o;\
	fi

${OBJECTDIR}/hardwarestatuses/requesthardwarestatusesincommingcommandhandler_nomain.o: ${OBJECTDIR}/hardwarestatuses/requesthardwarestatusesincommingcommandhandler.o hardwarestatuses/requesthardwarestatusesincommingcommandhandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/hardwarestatuses
	@NMOUTPUT=`${NM} ${OBJECTDIR}/hardwarestatuses/requesthardwarestatusesincommingcommandhandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hardwarestatuses/requesthardwarestatusesincommingcommandhandler_nomain.o hardwarestatuses/requesthardwarestatusesincommingcommandhandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/hardwarestatuses/requesthardwarestatusesincommingcommandhandler.o ${OBJECTDIR}/hardwarestatuses/requesthardwarestatusesincommingcommandhandler_nomain.o;\
	fi

${OBJECTDIR}/jsonfilesettings_nomain.o: ${OBJECTDIR}/jsonfilesettings.o jsonfilesettings.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/jsonfilesettings.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/jsonfilesettings_nomain.o jsonfilesettings.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/jsonfilesettings.o ${OBJECTDIR}/jsonfilesettings_nomain.o;\
	fi

${OBJECTDIR}/logger_nomain.o: ${OBJECTDIR}/logger.o logger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/logger.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/logger_nomain.o logger.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/logger.o ${OBJECTDIR}/logger_nomain.o;\
	fi

${OBJECTDIR}/lua/emitsignalifhappenshandler_nomain.o: ${OBJECTDIR}/lua/emitsignalifhappenshandler.o lua/emitsignalifhappenshandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/emitsignalifhappenshandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/emitsignalifhappenshandler_nomain.o lua/emitsignalifhappenshandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/emitsignalifhappenshandler.o ${OBJECTDIR}/lua/emitsignalifhappenshandler_nomain.o;\
	fi

${OBJECTDIR}/lua/emitsignalluaevent_nomain.o: ${OBJECTDIR}/lua/emitsignalluaevent.o lua/emitsignalluaevent.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/emitsignalluaevent.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/emitsignalluaevent_nomain.o lua/emitsignalluaevent.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/emitsignalluaevent.o ${OBJECTDIR}/lua/emitsignalluaevent_nomain.o;\
	fi

${OBJECTDIR}/lua/iluaeventforifhappenshandler_nomain.o: ${OBJECTDIR}/lua/iluaeventforifhappenshandler.o lua/iluaeventforifhappenshandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/iluaeventforifhappenshandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/iluaeventforifhappenshandler_nomain.o lua/iluaeventforifhappenshandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/iluaeventforifhappenshandler.o ${OBJECTDIR}/lua/iluaeventforifhappenshandler_nomain.o;\
	fi

${OBJECTDIR}/lua/iluafunctionregistrator_nomain.o: ${OBJECTDIR}/lua/iluafunctionregistrator.o lua/iluafunctionregistrator.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/iluafunctionregistrator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/iluafunctionregistrator_nomain.o lua/iluafunctionregistrator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/iluafunctionregistrator.o ${OBJECTDIR}/lua/iluafunctionregistrator_nomain.o;\
	fi

${OBJECTDIR}/lua/logmessageluaevent_nomain.o: ${OBJECTDIR}/lua/logmessageluaevent.o lua/logmessageluaevent.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/logmessageluaevent.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/logmessageluaevent_nomain.o lua/logmessageluaevent.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/logmessageluaevent.o ${OBJECTDIR}/lua/logmessageluaevent_nomain.o;\
	fi

${OBJECTDIR}/lua/luascript_nomain.o: ${OBJECTDIR}/lua/luascript.o lua/luascript.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/luascript.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/luascript_nomain.o lua/luascript.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/luascript.o ${OBJECTDIR}/lua/luascript_nomain.o;\
	fi

${OBJECTDIR}/lua/luascriptmanager_nomain.o: ${OBJECTDIR}/lua/luascriptmanager.o lua/luascriptmanager.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/luascriptmanager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/luascriptmanager_nomain.o lua/luascriptmanager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/luascriptmanager.o ${OBJECTDIR}/lua/luascriptmanager_nomain.o;\
	fi

${OBJECTDIR}/lua/outgoingmessageluaevent_nomain.o: ${OBJECTDIR}/lua/outgoingmessageluaevent.o lua/outgoingmessageluaevent.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/outgoingmessageluaevent.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/outgoingmessageluaevent_nomain.o lua/outgoingmessageluaevent.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/outgoingmessageluaevent.o ${OBJECTDIR}/lua/outgoingmessageluaevent_nomain.o;\
	fi

${OBJECTDIR}/lua/playlocalfilerequestluaevent_nomain.o: ${OBJECTDIR}/lua/playlocalfilerequestluaevent.o lua/playlocalfilerequestluaevent.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/playlocalfilerequestluaevent.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/playlocalfilerequestluaevent_nomain.o lua/playlocalfilerequestluaevent.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/playlocalfilerequestluaevent.o ${OBJECTDIR}/lua/playlocalfilerequestluaevent_nomain.o;\
	fi

${OBJECTDIR}/lua/playnetworkaudiorequestluaevent_nomain.o: ${OBJECTDIR}/lua/playnetworkaudiorequestluaevent.o lua/playnetworkaudiorequestluaevent.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/playnetworkaudiorequestluaevent.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/playnetworkaudiorequestluaevent_nomain.o lua/playnetworkaudiorequestluaevent.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/playnetworkaudiorequestluaevent.o ${OBJECTDIR}/lua/playnetworkaudiorequestluaevent_nomain.o;\
	fi

${OBJECTDIR}/lua/scriptfinishedluaevent_nomain.o: ${OBJECTDIR}/lua/scriptfinishedluaevent.o lua/scriptfinishedluaevent.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/scriptfinishedluaevent.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/scriptfinishedluaevent_nomain.o lua/scriptfinishedluaevent.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/scriptfinishedluaevent.o ${OBJECTDIR}/lua/scriptfinishedluaevent_nomain.o;\
	fi

${OBJECTDIR}/lua/scriptstartedluaevent_nomain.o: ${OBJECTDIR}/lua/scriptstartedluaevent.o lua/scriptstartedluaevent.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/scriptstartedluaevent.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/scriptstartedluaevent_nomain.o lua/scriptstartedluaevent.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/scriptstartedluaevent.o ${OBJECTDIR}/lua/scriptstartedluaevent_nomain.o;\
	fi

${OBJECTDIR}/lua/sethardwarestatusesluaevent_nomain.o: ${OBJECTDIR}/lua/sethardwarestatusesluaevent.o lua/sethardwarestatusesluaevent.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/sethardwarestatusesluaevent.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/sethardwarestatusesluaevent_nomain.o lua/sethardwarestatusesluaevent.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/sethardwarestatusesluaevent.o ${OBJECTDIR}/lua/sethardwarestatusesluaevent_nomain.o;\
	fi

${OBJECTDIR}/lua/stoplocalaudiorequestluaevent_nomain.o: ${OBJECTDIR}/lua/stoplocalaudiorequestluaevent.o lua/stoplocalaudiorequestluaevent.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/stoplocalaudiorequestluaevent.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/stoplocalaudiorequestluaevent_nomain.o lua/stoplocalaudiorequestluaevent.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/stoplocalaudiorequestluaevent.o ${OBJECTDIR}/lua/stoplocalaudiorequestluaevent_nomain.o;\
	fi

${OBJECTDIR}/lua/stopnetworkaudiorequestluaevent_nomain.o: ${OBJECTDIR}/lua/stopnetworkaudiorequestluaevent.o lua/stopnetworkaudiorequestluaevent.cpp 
	${MKDIR} -p ${OBJECTDIR}/lua
	@NMOUTPUT=`${NM} ${OBJECTDIR}/lua/stopnetworkaudiorequestluaevent.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lua/stopnetworkaudiorequestluaevent_nomain.o lua/stopnetworkaudiorequestluaevent.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/lua/stopnetworkaudiorequestluaevent.o ${OBJECTDIR}/lua/stopnetworkaudiorequestluaevent_nomain.o;\
	fi

${OBJECTDIR}/luatoaudiomediator_nomain.o: ${OBJECTDIR}/luatoaudiomediator.o luatoaudiomediator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/luatoaudiomediator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/luatoaudiomediator_nomain.o luatoaudiomediator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/luatoaudiomediator.o ${OBJECTDIR}/luatoaudiomediator_nomain.o;\
	fi

${OBJECTDIR}/luatonetworkstreammediator_nomain.o: ${OBJECTDIR}/luatonetworkstreammediator.o luatonetworkstreammediator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/luatonetworkstreammediator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/luatonetworkstreammediator_nomain.o luatonetworkstreammediator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/luatonetworkstreammediator.o ${OBJECTDIR}/luatonetworkstreammediator_nomain.o;\
	fi

${OBJECTDIR}/luatoprotocolmediator_nomain.o: ${OBJECTDIR}/luatoprotocolmediator.o luatoprotocolmediator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/luatoprotocolmediator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/luatoprotocolmediator_nomain.o luatoprotocolmediator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/luatoprotocolmediator.o ${OBJECTDIR}/luatoprotocolmediator_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/mainhandler_nomain.o: ${OBJECTDIR}/mainhandler.o mainhandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/mainhandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mainhandler_nomain.o mainhandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/mainhandler.o ${OBJECTDIR}/mainhandler_nomain.o;\
	fi

${OBJECTDIR}/network/itransport_nomain.o: ${OBJECTDIR}/network/itransport.o network/itransport.cpp 
	${MKDIR} -p ${OBJECTDIR}/network
	@NMOUTPUT=`${NM} ${OBJECTDIR}/network/itransport.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/network/itransport_nomain.o network/itransport.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/network/itransport.o ${OBJECTDIR}/network/itransport_nomain.o;\
	fi

${OBJECTDIR}/network/tcpserver_nomain.o: ${OBJECTDIR}/network/tcpserver.o network/tcpserver.cpp 
	${MKDIR} -p ${OBJECTDIR}/network
	@NMOUTPUT=`${NM} ${OBJECTDIR}/network/tcpserver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/network/tcpserver_nomain.o network/tcpserver.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/network/tcpserver.o ${OBJECTDIR}/network/tcpserver_nomain.o;\
	fi

${OBJECTDIR}/network/tcpsocket_nomain.o: ${OBJECTDIR}/network/tcpsocket.o network/tcpsocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/network
	@NMOUTPUT=`${NM} ${OBJECTDIR}/network/tcpsocket.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/network/tcpsocket_nomain.o network/tcpsocket.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/network/tcpsocket.o ${OBJECTDIR}/network/tcpsocket_nomain.o;\
	fi

${OBJECTDIR}/networkaudio/networkaudioifhappenshandler_nomain.o: ${OBJECTDIR}/networkaudio/networkaudioifhappenshandler.o networkaudio/networkaudioifhappenshandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/networkaudio
	@NMOUTPUT=`${NM} ${OBJECTDIR}/networkaudio/networkaudioifhappenshandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/networkaudio/networkaudioifhappenshandler_nomain.o networkaudio/networkaudioifhappenshandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/networkaudio/networkaudioifhappenshandler.o ${OBJECTDIR}/networkaudio/networkaudioifhappenshandler_nomain.o;\
	fi

${OBJECTDIR}/networkaudio/networkaudiomanager_nomain.o: ${OBJECTDIR}/networkaudio/networkaudiomanager.o networkaudio/networkaudiomanager.cpp 
	${MKDIR} -p ${OBJECTDIR}/networkaudio
	@NMOUTPUT=`${NM} ${OBJECTDIR}/networkaudio/networkaudiomanager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/networkaudio/networkaudiomanager_nomain.o networkaudio/networkaudiomanager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/networkaudio/networkaudiomanager.o ${OBJECTDIR}/networkaudio/networkaudiomanager_nomain.o;\
	fi

${OBJECTDIR}/networkaudio/networkaudothreadworker_nomain.o: ${OBJECTDIR}/networkaudio/networkaudothreadworker.o networkaudio/networkaudothreadworker.cpp 
	${MKDIR} -p ${OBJECTDIR}/networkaudio
	@NMOUTPUT=`${NM} ${OBJECTDIR}/networkaudio/networkaudothreadworker.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/networkaudio/networkaudothreadworker_nomain.o networkaudio/networkaudothreadworker.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/networkaudio/networkaudothreadworker.o ${OBJECTDIR}/networkaudio/networkaudothreadworker_nomain.o;\
	fi

${OBJECTDIR}/networkaudio/notifystatuschangedprotocoloutgoingcommand_nomain.o: ${OBJECTDIR}/networkaudio/notifystatuschangedprotocoloutgoingcommand.o networkaudio/notifystatuschangedprotocoloutgoingcommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/networkaudio
	@NMOUTPUT=`${NM} ${OBJECTDIR}/networkaudio/notifystatuschangedprotocoloutgoingcommand.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/networkaudio/notifystatuschangedprotocoloutgoingcommand_nomain.o networkaudio/notifystatuschangedprotocoloutgoingcommand.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/networkaudio/notifystatuschangedprotocoloutgoingcommand.o ${OBJECTDIR}/networkaudio/notifystatuschangedprotocoloutgoingcommand_nomain.o;\
	fi

${OBJECTDIR}/protocol/authprotocoloutgoingcommand_nomain.o: ${OBJECTDIR}/protocol/authprotocoloutgoingcommand.o protocol/authprotocoloutgoingcommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/protocol
	@NMOUTPUT=`${NM} ${OBJECTDIR}/protocol/authprotocoloutgoingcommand.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/authprotocoloutgoingcommand_nomain.o protocol/authprotocoloutgoingcommand.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/protocol/authprotocoloutgoingcommand.o ${OBJECTDIR}/protocol/authprotocoloutgoingcommand_nomain.o;\
	fi

${OBJECTDIR}/protocol/command_nomain.o: ${OBJECTDIR}/protocol/command.o protocol/command.cpp 
	${MKDIR} -p ${OBJECTDIR}/protocol
	@NMOUTPUT=`${NM} ${OBJECTDIR}/protocol/command.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/command_nomain.o protocol/command.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/protocol/command.o ${OBJECTDIR}/protocol/command_nomain.o;\
	fi

${OBJECTDIR}/protocol/finishscriptprotocoloutgoingcommand_nomain.o: ${OBJECTDIR}/protocol/finishscriptprotocoloutgoingcommand.o protocol/finishscriptprotocoloutgoingcommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/protocol
	@NMOUTPUT=`${NM} ${OBJECTDIR}/protocol/finishscriptprotocoloutgoingcommand.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/finishscriptprotocoloutgoingcommand_nomain.o protocol/finishscriptprotocoloutgoingcommand.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/protocol/finishscriptprotocoloutgoingcommand.o ${OBJECTDIR}/protocol/finishscriptprotocoloutgoingcommand_nomain.o;\
	fi

${OBJECTDIR}/protocol/hardwareprotocol_nomain.o: ${OBJECTDIR}/protocol/hardwareprotocol.o protocol/hardwareprotocol.cpp 
	${MKDIR} -p ${OBJECTDIR}/protocol
	@NMOUTPUT=`${NM} ${OBJECTDIR}/protocol/hardwareprotocol.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/hardwareprotocol_nomain.o protocol/hardwareprotocol.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/protocol/hardwareprotocol.o ${OBJECTDIR}/protocol/hardwareprotocol_nomain.o;\
	fi

${OBJECTDIR}/protocol/hardwareprotocolfactory_nomain.o: ${OBJECTDIR}/protocol/hardwareprotocolfactory.o protocol/hardwareprotocolfactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/protocol
	@NMOUTPUT=`${NM} ${OBJECTDIR}/protocol/hardwareprotocolfactory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/hardwareprotocolfactory_nomain.o protocol/hardwareprotocolfactory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/protocol/hardwareprotocolfactory.o ${OBJECTDIR}/protocol/hardwareprotocolfactory_nomain.o;\
	fi

${OBJECTDIR}/protocol/hardwareprotocolpacketparser_nomain.o: ${OBJECTDIR}/protocol/hardwareprotocolpacketparser.o protocol/hardwareprotocolpacketparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/protocol
	@NMOUTPUT=`${NM} ${OBJECTDIR}/protocol/hardwareprotocolpacketparser.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/hardwareprotocolpacketparser_nomain.o protocol/hardwareprotocolpacketparser.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/protocol/hardwareprotocolpacketparser.o ${OBJECTDIR}/protocol/hardwareprotocolpacketparser_nomain.o;\
	fi

${OBJECTDIR}/protocol/outgoingmessageprotocolcommand_nomain.o: ${OBJECTDIR}/protocol/outgoingmessageprotocolcommand.o protocol/outgoingmessageprotocolcommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/protocol
	@NMOUTPUT=`${NM} ${OBJECTDIR}/protocol/outgoingmessageprotocolcommand.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/outgoingmessageprotocolcommand_nomain.o protocol/outgoingmessageprotocolcommand.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/protocol/outgoingmessageprotocolcommand.o ${OBJECTDIR}/protocol/outgoingmessageprotocolcommand_nomain.o;\
	fi

${OBJECTDIR}/protocol/pingincommingcommandhandler_nomain.o: ${OBJECTDIR}/protocol/pingincommingcommandhandler.o protocol/pingincommingcommandhandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/protocol
	@NMOUTPUT=`${NM} ${OBJECTDIR}/protocol/pingincommingcommandhandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/pingincommingcommandhandler_nomain.o protocol/pingincommingcommandhandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/protocol/pingincommingcommandhandler.o ${OBJECTDIR}/protocol/pingincommingcommandhandler_nomain.o;\
	fi

${OBJECTDIR}/protocol/pingprotocoloutgoingcommand_nomain.o: ${OBJECTDIR}/protocol/pingprotocoloutgoingcommand.o protocol/pingprotocoloutgoingcommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/protocol
	@NMOUTPUT=`${NM} ${OBJECTDIR}/protocol/pingprotocoloutgoingcommand.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/pingprotocoloutgoingcommand_nomain.o protocol/pingprotocoloutgoingcommand.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/protocol/pingprotocoloutgoingcommand.o ${OBJECTDIR}/protocol/pingprotocoloutgoingcommand_nomain.o;\
	fi

${OBJECTDIR}/protocol/startnotifyincommingcommandhandler_nomain.o: ${OBJECTDIR}/protocol/startnotifyincommingcommandhandler.o protocol/startnotifyincommingcommandhandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/protocol
	@NMOUTPUT=`${NM} ${OBJECTDIR}/protocol/startnotifyincommingcommandhandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/startnotifyincommingcommandhandler_nomain.o protocol/startnotifyincommingcommandhandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/protocol/startnotifyincommingcommandhandler.o ${OBJECTDIR}/protocol/startnotifyincommingcommandhandler_nomain.o;\
	fi

${OBJECTDIR}/protocol/startscriptprotocoloutgoingcommand_nomain.o: ${OBJECTDIR}/protocol/startscriptprotocoloutgoingcommand.o protocol/startscriptprotocoloutgoingcommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/protocol
	@NMOUTPUT=`${NM} ${OBJECTDIR}/protocol/startscriptprotocoloutgoingcommand.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/protocol/startscriptprotocoloutgoingcommand_nomain.o protocol/startscriptprotocoloutgoingcommand.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/protocol/startscriptprotocoloutgoingcommand.o ${OBJECTDIR}/protocol/startscriptprotocoloutgoingcommand_nomain.o;\
	fi

${OBJECTDIR}/soundmanager_nomain.o: ${OBJECTDIR}/soundmanager.o soundmanager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/soundmanager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/soundmanager_nomain.o soundmanager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/soundmanager.o ${OBJECTDIR}/soundmanager_nomain.o;\
	fi

${OBJECTDIR}/soundmanagerifhappenshandler_nomain.o: ${OBJECTDIR}/soundmanagerifhappenshandler.o soundmanagerifhappenshandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/soundmanagerifhappenshandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/soundmanagerifhappenshandler_nomain.o soundmanagerifhappenshandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/soundmanagerifhappenshandler.o ${OBJECTDIR}/soundmanagerifhappenshandler_nomain.o;\
	fi

${OBJECTDIR}/timer/itimer_nomain.o: ${OBJECTDIR}/timer/itimer.o timer/itimer.cpp 
	${MKDIR} -p ${OBJECTDIR}/timer
	@NMOUTPUT=`${NM} ${OBJECTDIR}/timer/itimer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/timer/itimer_nomain.o timer/itimer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/timer/itimer.o ${OBJECTDIR}/timer/itimer_nomain.o;\
	fi

${OBJECTDIR}/timer/timerfactory_nomain.o: ${OBJECTDIR}/timer/timerfactory.o timer/timerfactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/timer
	@NMOUTPUT=`${NM} ${OBJECTDIR}/timer/timerfactory.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/timer/timerfactory_nomain.o timer/timerfactory.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/timer/timerfactory.o ${OBJECTDIR}/timer/timerfactory_nomain.o;\
	fi

${OBJECTDIR}/uuid_nomain.o: ${OBJECTDIR}/uuid.o uuid.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/uuid.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Wall -I3rdparty -I3rdparty/sol2 -I/usr/include/ -I/usr/include/lua5.3 -I. -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/uuid_nomain.o uuid.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/uuid.o ${OBJECTDIR}/uuid_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
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
