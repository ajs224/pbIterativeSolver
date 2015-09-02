# CMake generated Testfile for 
# Source directory: /home/userspace/ajs224/C++/pbIterativeSolver
# Build directory: /home/userspace/ajs224/C++/pbIterativeSolver/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(SolversRuns "bin/pbIterativeSolver")
add_test(ConstantKernelMulticell "build/bin/pbIterativeSolver" "-cells" "100" "-length" "1" "-u" "1" "-k" "constant" "-p" "12" "-res" "1e-12" "-mass" "-nin" "mono")
set_tests_properties(ConstantKernelMulticell PROPERTIES  WORKING_DIRECTORY "/home/userspace/ajs224/C++/pbIterativeSolver")
