SET(LIB_TYPE MODULE) #set the lib type

############## PROBLEM 1 ##############################
set(MODEL_FILE_CPU "problem1.c")
set(COMMON_HEADERS problem1.h)

ADD_LIBRARY(problem1 ${LIB_TYPE} ${COMMON_HEADERS} ${MODEL_FILE_CPU})
#########################################################

############## PROBLEM 2 ##############################
set(MODEL_FILE_CPU "problem2.c")
set(COMMON_HEADERS problem2.h)

ADD_LIBRARY(problem2 ${LIB_TYPE} ${COMMON_HEADERS} ${MODEL_FILE_CPU})
#########################################################
