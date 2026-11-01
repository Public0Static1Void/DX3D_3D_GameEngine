#include "base.h"
using namespace dx3d;

dx3d::Base::Base(const BaseDesc& desc) : m_Logger(desc.logger)
{
}

dx3d::Base::~Base()
{
}

Logger& dx3d::Base::getLogger() noexcept
{
	return m_Logger;
}
