#pragma once

#include <exception>
#include <string>

namespace ConfigExceptions {

    class ConfigFileNotFound : public std::exception {
    private:
        std::string message_ = "Invalid configuration path - file not found!";
    public:
        const char* what() const noexcept override {
            return message_.c_str();
        }
    };

    class NeedsConfiguration : public std::exception {
    private:
        std::string message_ = "'settings_' member must be configured!";
    public:
        const char* what() const noexcept override {
            return message_.c_str();
        }
    };

} // ConfigExceptions

namespace RequestExceptions {

    class IncorrectCityName : public std::exception {
    private:
        std::string message_ = "City with such name not found! Input : ";
        std::string city_name_;
    public:
        const char* what() const noexcept override {
            std::string message = message_ + city_name_;
            return message.c_str();
        }

        IncorrectCityName(const std::string& name) : city_name_(name) {};
    };

    class BadRequest : public std::exception {
    private:
        std::string message_ = "Bad connection or invalid data in request! Provided error message: ";
        std::string request_error_message_;
    public:
        const char* what() const noexcept override {
            std::string message = message_ + request_error_message_;
            return message.c_str();
        }

        BadRequest(const std::string& request_error_mes) : request_error_message_(request_error_mes){}
    };

}
