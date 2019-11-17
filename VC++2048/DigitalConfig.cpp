#include "DigitalConfig.h"
DigitalConfig::DigitalConfig()
{
}

DigitalConfig::~DigitalConfig()
{
	DeleteObject(this->digitalBk);
}