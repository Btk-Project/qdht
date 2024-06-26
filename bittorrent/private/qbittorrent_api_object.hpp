#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include "json_serializer.hpp"
#include "proto_base.hpp"
#include "serializer_base.hpp"

typedef std::variant<int, std::string> ScanDir;

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
    bool insert(const char* name, const size_t len, const T& value) NEKO_NOEXCEPT;
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

inline void ParametersSerializer::startSerialize(std::vector<char>* data) NEKO_NOEXCEPT { mData.data = data; }

inline bool ParametersSerializer::endSerialize() NEKO_NOEXCEPT {
    mData.data = nullptr;
    return true;
}

template <typename T>
bool ParametersSerializer::insert(const char* name, const size_t len, const T& value) NEKO_NOEXCEPT {
    return ParametersConvert<WriterType, ValueType, T>::doumpToString(name, len, *(mData.data), value);
}

inline bool ParametersSerializer::startDeserialize(const std::vector<char>& data) NEKO_NOEXCEPT { return false; }

inline bool ParametersSerializer::endDeserialize() NEKO_NOEXCEPT { return true; }

template <typename T>
bool ParametersSerializer::get(const char* name, const size_t len, T* value) NEKO_NOEXCEPT {
    return false;
}

namespace {
template <typename T>
void write_string_to_url(T& writer, std::string_view value) {
    for (auto& c : value) {
        switch (c) {
            case ' ':
                writer.push_back('%');
                writer.push_back('2');
                writer.push_back('0');
                break;
            case '/':
                writer.push_back('%');
                writer.push_back('2');
                writer.push_back('F');
                break;
            case '&':
                writer.push_back('%');
                writer.push_back('2');
                writer.push_back('6');
                break;
            case '=':
                writer.push_back('%');
                writer.push_back('3');
                writer.push_back('D');
                break;
            case '#':
                writer.push_back('%');
                writer.push_back('2');
                writer.push_back('3');
                break;
            default:
                writer.push_back(c);
                break;
        }
    }
}
}  // namespace

template <typename WriterT, typename ValueT, typename T>
struct ParametersConvert<WriterT, ValueT, std::optional<T>, void> {
    static bool doumpToString(const char* name, const size_t len, WriterT& writer, const std::optional<T>& value) {
        if (!value.has_value()) {
            return true;
        }
        return ParametersConvert<WriterT, ValueT, T>::doumpToString(name, len, writer, *value);
    }
};

template <typename WriterT, typename ValueT>
struct ParametersConvert<WriterT, ValueT, std::string, void> {
    static bool doumpToString(const char* name, const size_t len, WriterT& writer, const std::string& value) {
        if (writer.size() > 0) writer.push_back('&');
        write_string_to_url(writer, {name, len});
        writer.push_back('=');
        write_string_to_url(writer, value);
        return true;
    }
};

template <typename WriterT, typename ValueT>
struct ParametersConvert<WriterT, ValueT, uint64_t, void> {
    static bool doumpToString(const char* name, const size_t len, WriterT& writer, const uint64_t& value) {
        if (writer.size() > 0) writer.push_back('&');
        write_string_to_url(writer, {name, len});
        writer.push_back('=');
        auto str = std::to_string(value);
        writer.insert(writer.end(), str.begin(), str.end());
        return true;
    }
};

template <typename WriterT, typename ValueT>
struct ParametersConvert<WriterT, ValueT, int64_t, void> {
    static bool doumpToString(const char* name, const size_t len, WriterT& writer, const int64_t& value) {
        if (writer.size() > 0) writer.push_back('&');
        write_string_to_url(writer, {name, len});
        writer.push_back('=');
        auto str = std::to_string(value);
        writer.insert(writer.end(), str.begin(), str.end());
        return true;
    }
};

template <typename WriterT, typename ValueT>
struct ParametersConvert<WriterT, ValueT, double, void> {
    static bool doumpToString(const char* name, const size_t len, WriterT& writer, const double& value) {
        if (writer.size() > 0) writer.push_back('&');
        write_string_to_url(writer, {name, len});
        writer.push_back('=');
        auto str = std::to_string(value);
        writer.insert(writer.end(), str.begin(), str.end());
        return true;
    }
};

template <typename WriterT, typename ValueT>
struct ParametersConvert<WriterT, ValueT, bool, void> {
    static bool doumpToString(const char* name, const size_t len, WriterT& writer, const bool& value) {
        if (writer.size() > 0) writer.push_back('&');
        write_string_to_url(writer, {name, len});
        writer.push_back('=');
        std::string str = value ? "true" : "false";
        writer.insert(writer.end(), str.begin(), str.end());
        return true;
    }
};

template <typename WriterT, typename ValueT, typename T>
struct ParametersConvert<WriterT, ValueT, T,
                         typename std::enable_if<std::is_base_of<IProto, typename T::ProtoType>::value>::type> {
    static bool doumpToString(const char* name, const size_t len, WriterT& writer, const T& value) {
        if (writer.size() > 0) writer.push_back('&');
        write_string_to_url(writer, {name, len});
        writer.push_back('=');
        auto data = T::ProtoType::Serialize(value);
        writer.insert(writer.end(), data.begin(), data.end());
        return true;
    }
};

template <typename T>
std::vector<T> ListFromData(std::string_view data) {
    std::vector<T> ret;
    if (data.empty()) return ret;
    rapidjson::Document doc;
    doc.Parse(data.data(), data.size());
    if (doc.HasParseError()) {
        NEKO_LOG_WARN("parse error: {}", (int)doc.GetParseError());
        return ret;
    }
    if (!JsonConvert<JsonSerializer::WriterType, JsonSerializer::ValueType, std::vector<T>>::fromJsonValue(&ret, doc)) {
        NEKO_LOG_WARN("parse error: not array");
        return ret;
    }
    return ret;
}

NEKO_END_NAMESPACE