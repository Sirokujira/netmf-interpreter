APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += 

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(WORKSPACE_LIB_DIR)/libcpp-ev3/Makefile

endif
