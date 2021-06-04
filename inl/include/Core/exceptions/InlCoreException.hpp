#ifndef INLCOREEXCEPTION_HPP_
#define INLCOREEXCEPTION_HPP_

#include <exception>
#include <string>

namespace inl {
namespace core {

    class InlCoreException : public std::exception {
    public:
        explicit InlCoreException()
            : InlCoreException("Generic exception")
        {
        }

        explicit InlCoreException(const std::string& message)
            : msg_(message)
        {
        }

        virtual ~InlCoreException() noexcept { }

        virtual const char* what() const noexcept
        {
            return (msg_.c_str());
        }

    protected:
        std::string msg_;

    private:
    };

}
}

#endif /* !INLCOREEXCEPTION_HPP_ */
