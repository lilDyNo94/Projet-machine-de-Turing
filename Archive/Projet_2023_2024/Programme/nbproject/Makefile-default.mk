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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/machine_de_turing.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/machine_de_turing.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=machine_de_turing_main.c lib_i2c_pic24_ll.c lib_mcp23017.c lib_machine_de_turing.c lib_sept_seg.c lib_sk9822.c lib_l154a4surkqbdzgw.c lib_spi.c lib_calculs.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/machine_de_turing_main.o ${OBJECTDIR}/lib_i2c_pic24_ll.o ${OBJECTDIR}/lib_mcp23017.o ${OBJECTDIR}/lib_machine_de_turing.o ${OBJECTDIR}/lib_sept_seg.o ${OBJECTDIR}/lib_sk9822.o ${OBJECTDIR}/lib_l154a4surkqbdzgw.o ${OBJECTDIR}/lib_spi.o ${OBJECTDIR}/lib_calculs.o
POSSIBLE_DEPFILES=${OBJECTDIR}/machine_de_turing_main.o.d ${OBJECTDIR}/lib_i2c_pic24_ll.o.d ${OBJECTDIR}/lib_mcp23017.o.d ${OBJECTDIR}/lib_machine_de_turing.o.d ${OBJECTDIR}/lib_sept_seg.o.d ${OBJECTDIR}/lib_sk9822.o.d ${OBJECTDIR}/lib_l154a4surkqbdzgw.o.d ${OBJECTDIR}/lib_spi.o.d ${OBJECTDIR}/lib_calculs.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/machine_de_turing_main.o ${OBJECTDIR}/lib_i2c_pic24_ll.o ${OBJECTDIR}/lib_mcp23017.o ${OBJECTDIR}/lib_machine_de_turing.o ${OBJECTDIR}/lib_sept_seg.o ${OBJECTDIR}/lib_sk9822.o ${OBJECTDIR}/lib_l154a4surkqbdzgw.o ${OBJECTDIR}/lib_spi.o ${OBJECTDIR}/lib_calculs.o

# Source Files
SOURCEFILES=machine_de_turing_main.c lib_i2c_pic24_ll.c lib_mcp23017.c lib_machine_de_turing.c lib_sept_seg.c lib_sk9822.c lib_l154a4surkqbdzgw.c lib_spi.c lib_calculs.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/machine_de_turing.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ64GA002
MP_LINKER_FILE_OPTION=,--script=p24FJ64GA002.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/machine_de_turing_main.o: machine_de_turing_main.c  .generated_files/flags/default/71f8bbdd67aa79f31d1040a4e3c450a7551d93e6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/machine_de_turing_main.o.d 
	@${RM} ${OBJECTDIR}/machine_de_turing_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  machine_de_turing_main.c  -o ${OBJECTDIR}/machine_de_turing_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/machine_de_turing_main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_i2c_pic24_ll.o: lib_i2c_pic24_ll.c  .generated_files/flags/default/3bbb4ff5916e3c29333a8315071b23fa2786fdc8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_i2c_pic24_ll.o.d 
	@${RM} ${OBJECTDIR}/lib_i2c_pic24_ll.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_i2c_pic24_ll.c  -o ${OBJECTDIR}/lib_i2c_pic24_ll.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_i2c_pic24_ll.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_mcp23017.o: lib_mcp23017.c  .generated_files/flags/default/5167ccc41282b5d93d86af0394b850cc12b434 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_mcp23017.o.d 
	@${RM} ${OBJECTDIR}/lib_mcp23017.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_mcp23017.c  -o ${OBJECTDIR}/lib_mcp23017.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_mcp23017.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_machine_de_turing.o: lib_machine_de_turing.c  .generated_files/flags/default/47c426ae6cdf701ceeaa68197da98acd352c4582 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_machine_de_turing.o.d 
	@${RM} ${OBJECTDIR}/lib_machine_de_turing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_machine_de_turing.c  -o ${OBJECTDIR}/lib_machine_de_turing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_machine_de_turing.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_sept_seg.o: lib_sept_seg.c  .generated_files/flags/default/c543ba69054d2e4ce3fa0ab87fbbb2321e47dc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_sept_seg.o.d 
	@${RM} ${OBJECTDIR}/lib_sept_seg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_sept_seg.c  -o ${OBJECTDIR}/lib_sept_seg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_sept_seg.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_sk9822.o: lib_sk9822.c  .generated_files/flags/default/1eb25965876e4d06cf7ea07b42f4d85d3ba0c059 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_sk9822.o.d 
	@${RM} ${OBJECTDIR}/lib_sk9822.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_sk9822.c  -o ${OBJECTDIR}/lib_sk9822.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_sk9822.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_l154a4surkqbdzgw.o: lib_l154a4surkqbdzgw.c  .generated_files/flags/default/90a88171c879fbdaf01d9458a363786b48d2fc03 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_l154a4surkqbdzgw.o.d 
	@${RM} ${OBJECTDIR}/lib_l154a4surkqbdzgw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_l154a4surkqbdzgw.c  -o ${OBJECTDIR}/lib_l154a4surkqbdzgw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_l154a4surkqbdzgw.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_spi.o: lib_spi.c  .generated_files/flags/default/498c3e965ccffd7e81053df7555dc1e891481d2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_spi.o.d 
	@${RM} ${OBJECTDIR}/lib_spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_spi.c  -o ${OBJECTDIR}/lib_spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_spi.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_calculs.o: lib_calculs.c  .generated_files/flags/default/cf0a6430f6b256fab0b604efc160ee3be639b4a5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_calculs.o.d 
	@${RM} ${OBJECTDIR}/lib_calculs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_calculs.c  -o ${OBJECTDIR}/lib_calculs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_calculs.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/machine_de_turing_main.o: machine_de_turing_main.c  .generated_files/flags/default/77ebaec09c90a453f48183743d16927ace46aaa4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/machine_de_turing_main.o.d 
	@${RM} ${OBJECTDIR}/machine_de_turing_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  machine_de_turing_main.c  -o ${OBJECTDIR}/machine_de_turing_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/machine_de_turing_main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_i2c_pic24_ll.o: lib_i2c_pic24_ll.c  .generated_files/flags/default/8553961f7451bbc8804a55e1371ed24fc999f354 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_i2c_pic24_ll.o.d 
	@${RM} ${OBJECTDIR}/lib_i2c_pic24_ll.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_i2c_pic24_ll.c  -o ${OBJECTDIR}/lib_i2c_pic24_ll.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_i2c_pic24_ll.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_mcp23017.o: lib_mcp23017.c  .generated_files/flags/default/90dd5a982adfe298edc2d1550c5c0dcb3335465a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_mcp23017.o.d 
	@${RM} ${OBJECTDIR}/lib_mcp23017.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_mcp23017.c  -o ${OBJECTDIR}/lib_mcp23017.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_mcp23017.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_machine_de_turing.o: lib_machine_de_turing.c  .generated_files/flags/default/3b6c09379f3560c4a4920556decea3ec6bc2fc94 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_machine_de_turing.o.d 
	@${RM} ${OBJECTDIR}/lib_machine_de_turing.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_machine_de_turing.c  -o ${OBJECTDIR}/lib_machine_de_turing.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_machine_de_turing.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_sept_seg.o: lib_sept_seg.c  .generated_files/flags/default/e920c5328b34910ee6d0d782e193fdc97a69bc81 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_sept_seg.o.d 
	@${RM} ${OBJECTDIR}/lib_sept_seg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_sept_seg.c  -o ${OBJECTDIR}/lib_sept_seg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_sept_seg.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_sk9822.o: lib_sk9822.c  .generated_files/flags/default/1537d7463d57f481ec301541d9457df97b4f8dc1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_sk9822.o.d 
	@${RM} ${OBJECTDIR}/lib_sk9822.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_sk9822.c  -o ${OBJECTDIR}/lib_sk9822.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_sk9822.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_l154a4surkqbdzgw.o: lib_l154a4surkqbdzgw.c  .generated_files/flags/default/69b5142836cb839cb5721e4063d82c1b16256897 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_l154a4surkqbdzgw.o.d 
	@${RM} ${OBJECTDIR}/lib_l154a4surkqbdzgw.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_l154a4surkqbdzgw.c  -o ${OBJECTDIR}/lib_l154a4surkqbdzgw.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_l154a4surkqbdzgw.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_spi.o: lib_spi.c  .generated_files/flags/default/8884051640bd25837f352dcfa7fec93d3efeb3cb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_spi.o.d 
	@${RM} ${OBJECTDIR}/lib_spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_spi.c  -o ${OBJECTDIR}/lib_spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_spi.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/lib_calculs.o: lib_calculs.c  .generated_files/flags/default/d2dd280399bd0737e40b3abc3e9ca8e7bc457bc7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lib_calculs.o.d 
	@${RM} ${OBJECTDIR}/lib_calculs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  lib_calculs.c  -o ${OBJECTDIR}/lib_calculs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/lib_calculs.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
${DISTDIR}/machine_de_turing.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/machine_de_turing.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/machine_de_turing.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/machine_de_turing.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}/xc16-bin2hex ${DISTDIR}/machine_de_turing.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
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
