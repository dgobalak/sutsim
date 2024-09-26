#!/bin/bash
# Auto-generated script to run tests with correct PYTHONPATH
export PYTHONPATH=/mnt/c/Users/Daniel/Desktop/dg-sim/build/../test/sim_artifacts:$PYTHONPATH
pytest
if [ $? -eq 0 ]; then
    echo 'All tests passed!'
else
    echo 'Some tests failed. Check the output above for details.'
fi
