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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USB_Host_-_MSD_-_Simple_Demo_-_XC16.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USB_Host_-_MSD_-_Simple_Demo_-_XC16.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="../../../../Microchip/MDD File System/FSIO.c" "../../../../Microchip/USB/MSD Host Driver/usb_host_msd.c" "../../../../Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c" ../../../../Microchip/USB/usb_host.c ../main.c ../usb_config.c ../clock.c ../interrupt_manager.c ../mcc.c ../pin_manager.c ../pwm.c ../reset.c ../system.c ../tmr1.c ../traps.c ../spi.c ../spieeprom.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/491339551/FSIO.o ${OBJECTDIR}/_ext/921800108/usb_host_msd.o ${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o ${OBJECTDIR}/_ext/926206843/usb_host.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/usb_config.o ${OBJECTDIR}/_ext/1472/clock.o ${OBJECTDIR}/_ext/1472/interrupt_manager.o ${OBJECTDIR}/_ext/1472/mcc.o ${OBJECTDIR}/_ext/1472/pin_manager.o ${OBJECTDIR}/_ext/1472/pwm.o ${OBJECTDIR}/_ext/1472/reset.o ${OBJECTDIR}/_ext/1472/system.o ${OBJECTDIR}/_ext/1472/tmr1.o ${OBJECTDIR}/_ext/1472/traps.o ${OBJECTDIR}/_ext/1472/spi.o ${OBJECTDIR}/_ext/1472/spieeprom.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/491339551/FSIO.o.d ${OBJECTDIR}/_ext/921800108/usb_host_msd.o.d ${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o.d ${OBJECTDIR}/_ext/926206843/usb_host.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/usb_config.o.d ${OBJECTDIR}/_ext/1472/clock.o.d ${OBJECTDIR}/_ext/1472/interrupt_manager.o.d ${OBJECTDIR}/_ext/1472/mcc.o.d ${OBJECTDIR}/_ext/1472/pin_manager.o.d ${OBJECTDIR}/_ext/1472/pwm.o.d ${OBJECTDIR}/_ext/1472/reset.o.d ${OBJECTDIR}/_ext/1472/system.o.d ${OBJECTDIR}/_ext/1472/tmr1.o.d ${OBJECTDIR}/_ext/1472/traps.o.d ${OBJECTDIR}/_ext/1472/spi.o.d ${OBJECTDIR}/_ext/1472/spieeprom.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/491339551/FSIO.o ${OBJECTDIR}/_ext/921800108/usb_host_msd.o ${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o ${OBJECTDIR}/_ext/926206843/usb_host.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/usb_config.o ${OBJECTDIR}/_ext/1472/clock.o ${OBJECTDIR}/_ext/1472/interrupt_manager.o ${OBJECTDIR}/_ext/1472/mcc.o ${OBJECTDIR}/_ext/1472/pin_manager.o ${OBJECTDIR}/_ext/1472/pwm.o ${OBJECTDIR}/_ext/1472/reset.o ${OBJECTDIR}/_ext/1472/system.o ${OBJECTDIR}/_ext/1472/tmr1.o ${OBJECTDIR}/_ext/1472/traps.o ${OBJECTDIR}/_ext/1472/spi.o ${OBJECTDIR}/_ext/1472/spieeprom.o

# Source Files
SOURCEFILES=../../../../Microchip/MDD File System/FSIO.c ../../../../Microchip/USB/MSD Host Driver/usb_host_msd.c ../../../../Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c ../../../../Microchip/USB/usb_host.c ../main.c ../usb_config.c ../clock.c ../interrupt_manager.c ../mcc.c ../pin_manager.c ../pwm.c ../reset.c ../system.c ../tmr1.c ../traps.c ../spi.c ../spieeprom.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/USB_Host_-_MSD_-_Simple_Demo_-_XC16.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512MU810
MP_LINKER_FILE_OPTION=,--script=p33EP512MU810.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/491339551/FSIO.o: ../../../../Microchip/MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/491339551" 
	@${RM} ${OBJECTDIR}/_ext/491339551/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/491339551/FSIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../../Microchip/MDD File System/FSIO.c"  -o ${OBJECTDIR}/_ext/491339551/FSIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/491339551/FSIO.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/491339551/FSIO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/921800108/usb_host_msd.o: ../../../../Microchip/USB/MSD\ Host\ Driver/usb_host_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/921800108" 
	@${RM} ${OBJECTDIR}/_ext/921800108/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/921800108/usb_host_msd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../../Microchip/USB/MSD Host Driver/usb_host_msd.c"  -o ${OBJECTDIR}/_ext/921800108/usb_host_msd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/921800108/usb_host_msd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/921800108/usb_host_msd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o: ../../../../Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/921800108" 
	@${RM} ${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../../Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c"  -o ${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/926206843/usb_host.o: ../../../../Microchip/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/926206843" 
	@${RM} ${OBJECTDIR}/_ext/926206843/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/926206843/usb_host.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Microchip/USB/usb_host.c  -o ${OBJECTDIR}/_ext/926206843/usb_host.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/926206843/usb_host.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/926206843/usb_host.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/usb_config.o: ../usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../usb_config.c  -o ${OBJECTDIR}/_ext/1472/usb_config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/usb_config.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/clock.o: ../clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../clock.c  -o ${OBJECTDIR}/_ext/1472/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/interrupt_manager.o: ../interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../interrupt_manager.c  -o ${OBJECTDIR}/_ext/1472/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/interrupt_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/interrupt_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/mcc.o: ../mcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/mcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc.c  -o ${OBJECTDIR}/_ext/1472/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/mcc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/mcc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/pin_manager.o: ../pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../pin_manager.c  -o ${OBJECTDIR}/_ext/1472/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/pin_manager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pin_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/pwm.o: ../pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../pwm.c  -o ${OBJECTDIR}/_ext/1472/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/pwm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/reset.o: ../reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../reset.c  -o ${OBJECTDIR}/_ext/1472/reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/reset.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/reset.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/system.o: ../system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../system.c  -o ${OBJECTDIR}/_ext/1472/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/tmr1.o: ../tmr1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../tmr1.c  -o ${OBJECTDIR}/_ext/1472/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/tmr1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/tmr1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/traps.o: ../traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../traps.c  -o ${OBJECTDIR}/_ext/1472/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/spi.o: ../spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../spi.c  -o ${OBJECTDIR}/_ext/1472/spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/spi.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/spieeprom.o: ../spieeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/spieeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/spieeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../spieeprom.c  -o ${OBJECTDIR}/_ext/1472/spieeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/spieeprom.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/spieeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/491339551/FSIO.o: ../../../../Microchip/MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/491339551" 
	@${RM} ${OBJECTDIR}/_ext/491339551/FSIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/491339551/FSIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../../Microchip/MDD File System/FSIO.c"  -o ${OBJECTDIR}/_ext/491339551/FSIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/491339551/FSIO.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/491339551/FSIO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/921800108/usb_host_msd.o: ../../../../Microchip/USB/MSD\ Host\ Driver/usb_host_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/921800108" 
	@${RM} ${OBJECTDIR}/_ext/921800108/usb_host_msd.o.d 
	@${RM} ${OBJECTDIR}/_ext/921800108/usb_host_msd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../../Microchip/USB/MSD Host Driver/usb_host_msd.c"  -o ${OBJECTDIR}/_ext/921800108/usb_host_msd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/921800108/usb_host_msd.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/921800108/usb_host_msd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o: ../../../../Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/921800108" 
	@${RM} ${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o.d 
	@${RM} ${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "../../../../Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c"  -o ${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/921800108/usb_host_msd_scsi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/926206843/usb_host.o: ../../../../Microchip/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/926206843" 
	@${RM} ${OBJECTDIR}/_ext/926206843/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/926206843/usb_host.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../../../Microchip/USB/usb_host.c  -o ${OBJECTDIR}/_ext/926206843/usb_host.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/926206843/usb_host.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/926206843/usb_host.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/usb_config.o: ../usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../usb_config.c  -o ${OBJECTDIR}/_ext/1472/usb_config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/usb_config.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/clock.o: ../clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../clock.c  -o ${OBJECTDIR}/_ext/1472/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/interrupt_manager.o: ../interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../interrupt_manager.c  -o ${OBJECTDIR}/_ext/1472/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/interrupt_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/mcc.o: ../mcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/mcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc.c  -o ${OBJECTDIR}/_ext/1472/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/mcc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/mcc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/pin_manager.o: ../pin_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../pin_manager.c  -o ${OBJECTDIR}/_ext/1472/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pin_manager.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/pwm.o: ../pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../pwm.c  -o ${OBJECTDIR}/_ext/1472/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/pwm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/reset.o: ../reset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../reset.c  -o ${OBJECTDIR}/_ext/1472/reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/reset.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/reset.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/system.o: ../system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../system.c  -o ${OBJECTDIR}/_ext/1472/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/tmr1.o: ../tmr1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/tmr1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../tmr1.c  -o ${OBJECTDIR}/_ext/1472/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/tmr1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/tmr1.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/traps.o: ../traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../traps.c  -o ${OBJECTDIR}/_ext/1472/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/traps.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/spi.o: ../spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../spi.c  -o ${OBJECTDIR}/_ext/1472/spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/spi.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/spieeprom.o: ../spieeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/spieeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/spieeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../spieeprom.c  -o ${OBJECTDIR}/_ext/1472/spieeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/spieeprom.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O1 -I".." -I"../../../../Microchip/Include" -I"../../../../Microchip/Include/MDD File System" -I"../../../../Microchip/Include/USB" -I"../../../../Microchip/USB" -I"." -msmart-io=1 -Wall -msfr-warn=off   -fno-ivopts  -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/spieeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/USB_Host_-_MSD_-_Simple_Demo_-_XC16.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/USB_Host_-_MSD_-_Simple_Demo_-_XC16.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--heap=1000,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="..",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/USB_Host_-_MSD_-_Simple_Demo_-_XC16.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp=${DFP_DIR}/xc16 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/USB_Host_-_MSD_-_Simple_Demo_-_XC16.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/USB_Host_-_MSD_-_Simple_Demo_-_XC16.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=1000,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library-path="..",--library-path=".",--no-force-link,--smart-io,-Map="${DISTDIR}/USB_Host_-_MSD_-_Simple_Demo_-_XC16.X.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp=${DFP_DIR}/xc16 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/USB_Host_-_MSD_-_Simple_Demo_-_XC16.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp=${DFP_DIR}/xc16 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
