set(SOURCE_FILES_SOLVER solver.h solver.c
                        linear-system.h linear-system.c
                        newton-cotes.h newton-cotes.c
                        problem.h problem.c
                        )

ADD_LIBRARY(solver STATIC ${SOURCE_FILES_SOLVER})

set_property(TARGET solver PROPERTY POSITION_INDEPENDENT_CODE ON)