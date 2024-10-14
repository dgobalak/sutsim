#pragma once

#include <string>
#include <stdexcept>

class StateTag {
 public:
    StateTag(const std::string& tag) {
        size_t pos = tag.find(TAG_SEPARATOR);
        if (pos == std::string::npos) {
            throw std::invalid_argument("Invalid tag");
        }

        sut_name = tag.substr(0, pos);
        sut_tag = tag.substr(pos + 1);
    }

    const std::string& getSutName() const {
        return sut_name;
    }

    const std::string& getSutTag() const {
        return sut_tag;
    }

 private:
    std::string sut_name;
    std::string sut_tag;

    static const char TAG_SEPARATOR = '.';
};
