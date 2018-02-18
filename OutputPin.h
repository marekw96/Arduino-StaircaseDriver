#ifndef OutputPin_H
#define OutputPin_H

class OutputPin
{
public:
	explicit OutputPin() = default;
	virtual ~OutputPin() = default;
	virtual void set(char value) = 0;
};

#endif