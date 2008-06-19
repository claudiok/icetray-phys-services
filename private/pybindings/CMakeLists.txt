
if(BUILD_PYBINDINGS)
  i3_add_pybindings(phys_services
    I3CutValues.cxx
    USE_TOOLS boost python log4cplus root
    USE_PROJECTS phys-services
    )
endif(BUILD_PYBINDINGS)
