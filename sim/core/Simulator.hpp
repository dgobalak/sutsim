#pragma once

#include "SutContext.hpp"
#include <unordered_map>
#include <string>
#include <memory>

class Simulator {
public:
    Simulator();
    ~Simulator();

    void init_sut(const std::string& sut_name, const std::string& library_path);
    void tick_sut();

    void setSutData(const std::string& tag, const void* value, const std::string& type);
    void getSutData(const std::string& tag, void* value, const std::string& type);

private:
    std::unordered_map<std::string, SutContext> sut_contexts;

    std::pair<std::string, std::string> splitTag(const std::string& tag) const;
};
