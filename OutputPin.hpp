#pragma once

class OutputPin
{
public:
	explicit OutputPin() = default;
	virtual ~OutputPin() = default;
	virtual void set(char value) = 0;
};
