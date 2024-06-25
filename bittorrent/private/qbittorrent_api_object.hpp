#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include "proto_base.hpp"
#include "json_serializer.hpp"
#include "serializer_base.hpp"

typedef std::variant<int, std::string> ScanDirs;

NEKO_BEGIN_NAMESPACE

template <typename WriterT, typename ValueT, typename T, class enable = void>
struct ParametersConvert;

class ParametersSerializer {
public:
    using WriterType = std::vector<char>;
    using ValueType  = std::vector<char>;

public:
    ~ParametersSerializer() = default;
    void startSerialize(std::vector<char>* data) NEKO_NOEXCEPT;
    inline bool endSerialize() NEKO_NOEXCEPT;
    template <typename T>
    bool insert(const char* name, const size_t len,
                const T& value) NEKO_NOEXCEPT;
    bool startDeserialize(const std::vector<char>& data) NEKO_NOEXCEPT;
    bool endDeserialize() NEKO_NOEXCEPT;
    template <typename T>
    bool get(const char* name, const size_t len, T* value) NEKO_NOEXCEPT;

private:
    union {
        std::vector<char>* data = nullptr;
        const std::vector<char>* constData;
    } mData;
    int mOffset = 0;
};

inline void ParametersSerializer::startSerialize(std::vector<char>* data)
    NEKO_NOEXCEPT {
    mData.data = data;
}

inline bool ParametersSerializer::endSerialize() NEKO_NOEXCEPT {
    mData.data = nullptr;
    return true;
}

template <typename T>
bool ParametersSerializer::insert(const char* name, const size_t len,
                                  const T& value) NEKO_NOEXCEPT {
    return ParametersConvert<WriterType, ValueType, T>::doumpToString(
        name, len, *(mData.data), value);
}

inline bool ParametersSerializer::startDeserialize(
    const std::vector<char>& data) NEKO_NOEXCEPT {
    return false;
}

inline bool ParametersSerializer::endDeserialize() NEKO_NOEXCEPT {
    return true;
}

template <typename T>
bool ParametersSerializer::get(const char* name, const size_t len,
                               T* value) NEKO_NOEXCEPT {
    return false;
}

template <typename WriterT, typename ValueT>
struct ParametersConvert<WriterT, ValueT, std::string, void> {
    static bool doumpToString(const char* name, const size_t len,
                              WriterT& writer, const std::string& value) {
        writer.insert(writer.end(), name, name + len);
        writer.push_back('=');
        writer.insert(writer.end(), value.begin(), value.end());
        return true;
    }
};

template <typename WriterT, typename ValueT>
struct JsonConvert<WriterT, ValueT, ScanDirs, void> {
    static bool toJsonValue(WriterT& writer, const ScanDirs value) {
        if (std::holds_alternative<int>(value)) {
            return writer.Int(std::get<int>(value));
        }

        if (std::holds_alternative<std::string>(value)) {
            return writer.String(std::get<std::string>(value).c_str());
        }
        return false;
    }
    static bool fromJsonValue(ScanDirs* dst, const ValueT& value) {
        if (value.IsInt()) {
            std::get<int>(*dst) = value.GetInt();
            return true;
        }

        if (value.IsString()) {
            std::get<std::string>(*dst) =
                std::string(value.GetString(), value.GetStringLength());
            return true;
        }
        return false;
    }
};
NEKO_END_NAMESPACE