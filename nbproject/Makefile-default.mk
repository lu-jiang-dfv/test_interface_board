#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/test_interface_board.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/test_interface_board.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/code_base/drivers/nano_pic18f47k42/adc.c src/code_base/drivers/nano_pic18f47k42/board.c src/code_base/drivers/nano_pic18f47k42/eusart.c src/code_base/drivers/nano_pic18f47k42/hal.c src/code_base/drivers/nano_pic18f47k42/i2c_host.c src/code_base/libs/display.c src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1 ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1 ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1 ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1 ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1 ${OBJECTDIR}/src/code_base/libs/display.p1 ${OBJECTDIR}/src/main.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1.d ${OBJECTDIR}/src/code_base/libs/display.p1.d ${OBJECTDIR}/src/main.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1 ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1 ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1 ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1 ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1 ${OBJECTDIR}/src/code_base/libs/display.p1 ${OBJECTDIR}/src/main.p1

# Source Files
SOURCEFILES=src/code_base/drivers/nano_pic18f47k42/adc.c src/code_base/drivers/nano_pic18f47k42/board.c src/code_base/drivers/nano_pic18f47k42/eusart.c src/code_base/drivers/nano_pic18f47k42/hal.c src/code_base/drivers/nano_pic18f47k42/i2c_host.c src/code_base/libs/display.c src/main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/test_interface_board.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F47K42
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1: src/code_base/drivers/nano_pic18f47k42/adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42" 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1.d 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit5   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1 src/code_base/drivers/nano_pic18f47k42/adc.c 
	@-${MV} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1: src/code_base/drivers/nano_pic18f47k42/board.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42" 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1.d 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit5   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1 src/code_base/drivers/nano_pic18f47k42/board.c 
	@-${MV} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1: src/code_base/drivers/nano_pic18f47k42/eusart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42" 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1.d 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit5   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1 src/code_base/drivers/nano_pic18f47k42/eusart.c 
	@-${MV} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1: src/code_base/drivers/nano_pic18f47k42/hal.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42" 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1.d 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit5   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1 src/code_base/drivers/nano_pic18f47k42/hal.c 
	@-${MV} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1: src/code_base/drivers/nano_pic18f47k42/i2c_host.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42" 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1.d 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit5   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1 src/code_base/drivers/nano_pic18f47k42/i2c_host.c 
	@-${MV} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/code_base/libs/display.p1: src/code_base/libs/display.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src/code_base/libs" 
	@${RM} ${OBJECTDIR}/src/code_base/libs/display.p1.d 
	@${RM} ${OBJECTDIR}/src/code_base/libs/display.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit5   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/code_base/libs/display.p1 src/code_base/libs/display.c 
	@-${MV} ${OBJECTDIR}/src/code_base/libs/display.d ${OBJECTDIR}/src/code_base/libs/display.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/code_base/libs/display.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/main.p1: src/main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.p1.d 
	@${RM} ${OBJECTDIR}/src/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit5   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/main.p1 src/main.c 
	@-${MV} ${OBJECTDIR}/src/main.d ${OBJECTDIR}/src/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1: src/code_base/drivers/nano_pic18f47k42/adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42" 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1.d 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1 src/code_base/drivers/nano_pic18f47k42/adc.c 
	@-${MV} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1: src/code_base/drivers/nano_pic18f47k42/board.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42" 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1.d 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1 src/code_base/drivers/nano_pic18f47k42/board.c 
	@-${MV} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/board.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1: src/code_base/drivers/nano_pic18f47k42/eusart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42" 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1.d 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1 src/code_base/drivers/nano_pic18f47k42/eusart.c 
	@-${MV} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1: src/code_base/drivers/nano_pic18f47k42/hal.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42" 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1.d 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1 src/code_base/drivers/nano_pic18f47k42/hal.c 
	@-${MV} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/hal.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1: src/code_base/drivers/nano_pic18f47k42/i2c_host.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42" 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1.d 
	@${RM} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1 src/code_base/drivers/nano_pic18f47k42/i2c_host.c 
	@-${MV} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.d ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/code_base/drivers/nano_pic18f47k42/i2c_host.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/code_base/libs/display.p1: src/code_base/libs/display.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src/code_base/libs" 
	@${RM} ${OBJECTDIR}/src/code_base/libs/display.p1.d 
	@${RM} ${OBJECTDIR}/src/code_base/libs/display.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/code_base/libs/display.p1 src/code_base/libs/display.c 
	@-${MV} ${OBJECTDIR}/src/code_base/libs/display.d ${OBJECTDIR}/src/code_base/libs/display.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/code_base/libs/display.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/main.p1: src/main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.p1.d 
	@${RM} ${OBJECTDIR}/src/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/src/main.p1 src/main.c 
	@-${MV} ${OBJECTDIR}/src/main.d ${OBJECTDIR}/src/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/test_interface_board.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/test_interface_board.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=pickit5  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/test_interface_board.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/test_interface_board.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/test_interface_board.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/test_interface_board.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/test_interface_board.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
