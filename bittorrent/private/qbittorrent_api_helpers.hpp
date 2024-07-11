#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include "json_serializer.hpp"
#include "proto_base.hpp"
#include "serializer_base.hpp"

typedef std::variant<int, std::string> ScanDir;

NEKO_BEGIN_NAMESPACE
namespace bittorrent::detail {
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
}  // namespace bittorrent::detail
class ParametersOutputSerializer : public detail::OutputSerializer<ParametersOutputSerializer> {
public:
    using BufferType = std::vector<char>;

public:
    ParametersOutputSerializer(BufferType& out) NEKO_NOEXCEPT
        : detail::OutputSerializer<ParametersOutputSerializer>(this),
          mBuffer(out) {}
    ParametersOutputSerializer(const ParametersOutputSerializer& other) NEKO_NOEXCEPT
        : detail::OutputSerializer<ParametersOutputSerializer>(this),
          mBuffer(other.mBuffer) {}
    ParametersOutputSerializer(ParametersOutputSerializer&& other) NEKO_NOEXCEPT
        : detail::OutputSerializer<ParametersOutputSerializer>(this),
          mBuffer(other.mBuffer) {}
    template <typename T>
    inline bool saveValue(const SizeTag<T>& size) NEKO_NOEXCEPT {
        return true;
    }
    template <typename T, traits::enable_if_t<std::is_signed<T>::value, sizeof(T) <= sizeof(int64_t),
                                              !std::is_enum<T>::value> = traits::default_value_for_enable>
    inline bool saveValue(const T value) NEKO_NOEXCEPT {
        const auto& valueStr = std::to_string(static_cast<int64_t>(value));
        mBuffer.resize(mBuffer.size() + valueStr.size());
        std::copy(valueStr.begin(), valueStr.end(), mBuffer.end() - valueStr.size());
        return true;
    }
    template <typename T, traits::enable_if_t<std::is_unsigned<T>::value, sizeof(T) <= sizeof(int64_t),
                                              !std::is_enum<T>::value> = traits::default_value_for_enable>
    inline bool saveValue(const T value) NEKO_NOEXCEPT {
        const auto& valueStr = std::to_string(static_cast<uint64_t>(value));
        mBuffer.resize(mBuffer.size() + valueStr.size());
        std::copy(valueStr.begin(), valueStr.end(), mBuffer.end() - valueStr.size());
        return true;
    }
    inline bool saveValue(const float value) NEKO_NOEXCEPT {
        const auto& valueStr = std::to_string(value);
        mBuffer.resize(mBuffer.size() + valueStr.size());
        std::copy(valueStr.begin(), valueStr.end(), mBuffer.end() - valueStr.size());
        return true;
    }
    inline bool saveValue(const double value) NEKO_NOEXCEPT {
        const auto& valueStr = std::to_string(value);
        mBuffer.resize(mBuffer.size() + valueStr.size());
        std::copy(valueStr.begin(), valueStr.end(), mBuffer.end() - valueStr.size());
        return true;
    }
    inline bool saveValue(const bool value) NEKO_NOEXCEPT {
        const auto& valueStr = std::string_view(value ? "true" : "false");
        mBuffer.resize(mBuffer.size() + valueStr.size());
        std::copy(valueStr.begin(), valueStr.end(), mBuffer.end() - valueStr.size());
        return true;
    }
    inline bool saveValue(const std::string& value) NEKO_NOEXCEPT {
        bittorrent::detail::write_string_to_url(mBuffer, value);
        return true;
    }
    inline bool saveValue(const char* value) NEKO_NOEXCEPT {
        bittorrent::detail::write_string_to_url(mBuffer, value);
        return true;
    }
    inline bool saveValue(const std::string_view value) NEKO_NOEXCEPT {
        bittorrent::detail::write_string_to_url(mBuffer, value);
        return true;
    }
    template <typename T>
    inline bool saveValue(const NameValuePair<T>& value) NEKO_NOEXCEPT {
        if constexpr (traits::is_optional<T>::value) {
            if (value.value.has_value()) {
                if (mBuffer.size() > 0) mBuffer.push_back('&');
                bittorrent::detail::write_string_to_url(mBuffer, {value.name, value.nameLen});
                mBuffer.push_back('=');
                return (*this)(value.value.value());
            } else {
                return true;
            }
        } else {
            if (mBuffer.size() > 0) mBuffer.push_back('&');
            bittorrent::detail::write_string_to_url(mBuffer, {value.name, value.nameLen});
            mBuffer.push_back('=');
            return (*this)(value.value);
        }
    }
    bool startArray(const std::size_t) NEKO_NOEXCEPT { return true; }
    bool endArray() NEKO_NOEXCEPT { return true; }
    bool startObject(const std::size_t) NEKO_NOEXCEPT { return true; }
    bool endObject() NEKO_NOEXCEPT { return true; }
    bool end() NEKO_NOEXCEPT { return true; }

private:
    ParametersOutputSerializer& operator=(const ParametersOutputSerializer&) = delete;
    ParametersOutputSerializer& operator=(ParametersOutputSerializer&&)      = delete;

private:
    BufferType& mBuffer;
};

class ParametersInputSerializer : public detail::InputSerializer<ParametersInputSerializer> {
public:
    using BufferType = std::vector<char>;

public:
    inline ParametersInputSerializer(const std::vector<char>& buf) NEKO_NOEXCEPT
        : InputSerializer<ParametersInputSerializer>(this) {}
    inline ParametersInputSerializer(const char* buf, std::size_t size) NEKO_NOEXCEPT
        : InputSerializer<ParametersInputSerializer>(this) {}
    inline operator bool() const NEKO_NOEXCEPT { return false; }
    inline std::string name() NEKO_NOEXCEPT { return {}; }

    template <typename T>
    inline bool loadValue(T&& value) NEKO_NOEXCEPT {
        return false;
    }

private:
    ParametersInputSerializer& operator=(const ParametersInputSerializer&) = delete;
    ParametersInputSerializer& operator=(ParametersInputSerializer&&)      = delete;
};

struct ParametersSerializer {
    using OutputSerializer = ParametersOutputSerializer;
    using InputSerializer  = ParametersInputSerializer;
};

NEKO_END_NAMESPACE