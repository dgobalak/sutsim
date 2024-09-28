# Set the path to the sim_artifacts directory (where the SWIG Python module is generated)
set(SIM_ARTIFACTS_DIR "${CMAKE_BINARY_DIR}/../test/sim_artifacts")

# Generate the run_tests.sh script to run tests with the correct PYTHONPATH
file(WRITE ${CMAKE_BINARY_DIR}/../test/run_tests.sh
"#!/bin/bash\n"
"# Auto-generated script to run tests with correct PYTHONPATH\n"
"export PYTHONPATH=${SIM_ARTIFACTS_DIR}:\$PYTHONPATH\n"
"python -m pytest\n"
"if [ \$? -eq 0 ]; then\n"
"    echo 'All tests passed!'\n"
"else\n"
"    echo 'Some tests failed. Check the output above for details.'\n"
"fi\n"
)

# Make the run_tests.sh script executable
file(COPY ${CMAKE_BINARY_DIR}/../test/run_tests.sh
     DESTINATION ${CMAKE_BINARY_DIR}/../test
     FILE_PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
