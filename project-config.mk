
TEST_SRCDIR_NAMES := test

# Anything you don't want to compile (must be full path?)
CXX_EXCLUDE_SRCS :=

# ROOT_EXCLUDE_NAMES :=  what was this?

# has filtered out from what is automagically put into linkdef
ROOT_NON_CLASSES :=  
# exactly same function as ROOT_NON_CLASSES
ROOT_TEMPLATES := 

# public directories for these projects are added to #include path,
# and libraries are added to link.
USES_PROJECTS := dataclasses icetray root-icetray

# same as above, but for external tools.  Paths found in config.mk
USES_TOOLS := root log4cplus TUT gsl boost

# this is now globally "root" by default
BUILD_FLAVOR := root
