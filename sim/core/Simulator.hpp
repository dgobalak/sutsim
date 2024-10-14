#pragma once

#include "SutContext.hpp"
#include "StateTag.hpp"

#include <unordered_map>
#include <string>
#include <memory>

class Simulator {
public:
    Simulator();
    ~Simulator();

    void init_sut(const std::string& sut_name, const std::string& library_path);
    void tick_sut();

    void setSutData(const StateTag& tag, const void* value, const std::string& type);
    void getSutData(const StateTag& tag, void* value, const std::string& type);

    std::string getSutDataType(const StateTag& tag);

private:
    std::unordered_map<std::string, SutContext> sut_contexts;
};
