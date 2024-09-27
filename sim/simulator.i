%module simulator

%{
#include "simulator_binding.h"
%}

// Typemaps to automatically handle Python type conversion

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

// Expose Pythonic overloaded versions of setSutData and getSutData
%inline %{
    void set_sut_data_float(const char* tag, float value) {
        setSutDataFloat(tag, value);
    }

    void set_sut_data_int32(const char* tag, int32_t value) {
        setSutDataInt32(tag, value);
    }

    void set_sut_data_uint32(const char* tag, uint32_t value) {
        setSutDataUInt32(tag, value);
    }

    void set_sut_data_bool(const char* tag, bool value) {
        setSutDataBool(tag, value);
    }

    float get_sut_data_float(const char* tag) {
        return getSutDataFloat(tag);
    }

    int32_t get_sut_data_int32(const char* tag) {
        return getSutDataInt32(tag);
    }

    uint32_t get_sut_data_uint32(const char* tag) {
        return getSutDataUInt32(tag);
    }

    bool get_sut_data_bool(const char* tag) {
        return getSutDataBool(tag);
    }

    void init_simulator(const char* lib_path) {
        initSimulator(lib_path);
    }

    void run_tick() {
        runTick();
    }
%}
