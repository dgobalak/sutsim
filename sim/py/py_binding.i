%module sutsim

%{
#include "py_binding.h"
#include <Python.h>
%}

// Float handling
%typemap(in) float {
    if (PyFloat_Check($input)) {
        $1 = (float)PyFloat_AsDouble($input);
    } else {
        SWIG_exception_fail(SWIG_TypeError, "Expected a float");
    }
}

%typemap(out) float {
    $result = PyFloat_FromDouble($1);
}

// Int32 handling
%typemap(in) int32_t {
    if (PyLong_Check($input)) {
        $1 = (int32_t)PyLong_AsLong($input);
    } else {
        SWIG_exception_fail(SWIG_TypeError, "Expected an integer");
    }
}

%typemap(out) int32_t {
    $result = PyLong_FromLong($1);
}

// UInt32 handling
%typemap(in) uint32_t {
    if (PyLong_Check($input)) {
        $1 = (uint32_t)PyLong_AsUnsignedLong($input);
    } else {
        SWIG_exception_fail(SWIG_TypeError, "Expected an unsigned integer");
    }
}

%typemap(out) uint32_t {
    $result = PyLong_FromUnsignedLong($1);
}

// Bool handling
%typemap(in) bool {
    $1 = PyObject_IsTrue($input);
}

%typemap(out) bool {
    $result = PyBool_FromLong($1);
}

void initSim(const char* sut_name, const char* lib_path);
void runTick();
void setSutData(const char* tag, PyObject* value);
PyObject* getSutData(const char* tag);
