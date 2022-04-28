#pragma once


namespace pintool
{
namespace time
{

class timer
{
public:
    using ticks_type = long long int;

    timer();

    ticks_type ticks() const;
    ticks_type frequency() const;
    ticks_type elapsed() const;

private:
    ticks_type start_timestamp;
};

} // namespace time
} // namespace pintool