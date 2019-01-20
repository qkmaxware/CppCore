#ifndef _SYSTEM_HPP
#define _SYSTEM_HPP

#include <iostream>
#include <string>
#include <limits>
#include <cstdint>
#include <memory>
#include <cuchar>

#include "System.Os.hpp"

//Based on:
//https://docs.microsoft.com/en-us/dotnet/api/system?view=netframework-4.7.2

namespace System {

//System sized
/**
 * Unsigned system-sized integer
 */
using uint = unsigned int;
/**
 * Unsigned system-sized long integer
 */
using ulong = unsigned long int;
//Signed integers of specific sizes
#ifdef INT8_MAX
    /**
     * Signed 8 bit integer
     */
	using int8 = std::int_least8_t; 
#endif
#ifdef INT16_MAX
    /**
     * Signed 16 bit integer
     */
	using int16 = std::int_least16_t;
#endif
#ifdef INT32_MAX
    /**
     * Signed 32 bit integer
     */
	using int32 = std::int_least32_t;
#endif
#ifdef INT64_MAX
    /**
     * Signed 64 bit integer
     */
	using int64 = std::int_least32_t;
#endif
//Unsigned integers of specific sizes
#ifdef UINT8_MAX
    /**
     * Unsigned 8 bit integer
     */
	using uint8 = std::uint_least8_t;
#endif
#ifdef UINT16_MAX
    /**
     * Unsigned 16 bit integer
     */
	using uint16 = std::uint_least16_t;
#endif
#ifdef UINT32_MAX
    /**
     * Unsigned 32 bit integer
     */
	using uint32 = std::uint_least32_t;
#endif
#ifdef UINT64_MAX
    /**
     * Unsigned 64 bit integer
     */
	using uint64 = std::uint_least64_t;
#endif

/**
 * 8 bit character type
 */
using char8 = char;

/**
 * 16 bit character type
 */
using char16 = char16_t;

/**
 * 32 bit character type
 */
using char32 = char32_t;

/**
 * Root object class. All classes extend from this one. 
 */
class Object {
	public:
        /**
         * Create an empty object
         */
        Object();
        /**
         * Compare if two objects are equal 
         */
		virtual bool Equals (const Object& other);
        /**
         * Get a hash code that represents this object. By default this is the same as the memory address pointer. 
         */
		virtual std::uintptr_t GetHashCode() const;
        /**
         * Convert this object to a string representation 
         */
		virtual std::string ToString() const;
        /**
         * Print the string representation of this object to the given stream 
         */
		virtual void ToString(std::ostream& stream) const;
};

/**
 * Default operator to print an object to an output stream 
 */
std::ostream& operator << (std::ostream& stream, const Object& ref);

/**
 * Class representing all objects that can be thrown.  
 */
class Throwable : public Object, public std::exception {
    private:
        /**
         * The string message for this throwable 
         */
        const std::string message;
        /**
         * The cause which resulted in this object being thrown 
         */
        std::unique_ptr<Throwable> cause;

    public:
        /**
         * Create a new throwable with the given message and no root cause 
         */
        Throwable(std::string& message);
        /**
         * Create a new throwable with the given message and root cause 
         */
        Throwable(std::string& message, std::unique_ptr<Throwable>& cause);

        /**
         * Get the message for this throwable 
         */
        const std::string& GetMessage() const;
        /**
         * Get the cause of this throwable 
         */
        const Throwable& GetCause() const;
        /**
         * Check if this throwable was caused by another event
         */
        bool HasCause() const;

        /**
         * Print a trace of this throwable and it's cause
         */
        virtual void PrintTrace(std::ostream& stream) const ;
        virtual std::string ToString() const;
        virtual const char * what ();
};

class Exception : public Throwable { 
    public:
        Exception(std::string& message);
        Exception(std::string& message, std::unique_ptr<Throwable>& cause);
        
};

}

#endif