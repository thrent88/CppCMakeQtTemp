#ifndef EX_STACKBACK_H
#define EX_STACKBACK_H

#include <cpptrace/formatting.hpp>
#include <cpptrace/from_current.hpp>
#include <stdexcept>

#define PrintStackBack()                                      \
    cpptrace::formatter{}                                     \
        .header("Stack trace:")                               \
        .addresses(cpptrace::formatter::address_mode::object) \
        .print(cpptrace::from_current_exception())

#define StringStackBack()                                     \
    cpptrace::formatter{}                                     \
        .header("Stack trace:")                               \
        .addresses(cpptrace::formatter::address_mode::object) \
        .format(cpptrace::from_current_exception())

#define THROW_EXCEPTION(msg) \
    throw std::runtime_error(msg)

#endif  // EX_STACKBACK_H
