#include "System.hpp"

namespace System {

Object::Object() {}

bool Object::Equals (const Object& other) {
    return this == &other;
};

std::uintptr_t Object::GetHashCode() const {
    return reinterpret_cast<std::uintptr_t>(this);
}

std::string Object::ToString() const {
    return std::string("Object@").append(std::to_string(Object::GetHashCode()));
}

void Object::ToString(std::ostream& stream) const {
    stream << ToString();
}

std::ostream& operator << (std::ostream& stream, const Object& ref) {
    stream << ref.ToString();
    return stream;
}

Throwable::Throwable(std::string& message) : Object(), std::exception(), message(message), cause(nullptr) {}

Throwable::Throwable(std::string& message, std::unique_ptr<Throwable>& cause) : Object(), std::exception(), message(message), cause(std::move(cause)) {}

const std::string& Throwable::GetMessage() const {
    return message;
}

const Throwable& Throwable::GetCause() const {
    if(cause){
        return *cause;
    } else {
        return *this;
    }
}

bool Throwable::HasCause() const {
    if(cause)
        return true;
    else
        return false;
}

void Throwable::PrintTrace(std::ostream& stream) const {
    stream << GetMessage();
    if(HasCause()){
        stream << System::Environment::NewLine;
        GetCause().PrintTrace(stream);
    }
}

std::string Throwable::ToString() const {
    return message;
}

const char* Throwable::what () {
    return message.c_str();
}

Exception::Exception(std::string& message) : Throwable(message) {}

Exception::Exception(std::string& message, std::unique_ptr<Throwable>& cause) : Throwable(message, cause) {}

}