#pragma once


namespace util
{

template<class T, template<typename> class crtpType>
class CRTP
{
        friend crtpType<T>;

public:

        T& super()       { return static_cast<T&>(*this); }
        T& super() const { return static_cast<const T&>(*this); }

private:

        CRTP() {}
};

}