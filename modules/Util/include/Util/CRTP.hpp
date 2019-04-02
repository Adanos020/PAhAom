#pragma once


namespace util
{

template<class T, template<typename> class crtpType>
class CRTP
{
        friend crtpType<T>;

public:

        auto super()       -> T& { return static_cast<T&>(*this); }
        auto super() const -> T& { return static_cast<const T&>(*this); }

private:

        CRTP() {}
};

}