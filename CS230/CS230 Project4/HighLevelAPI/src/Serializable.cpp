#include "stdafx.h"
#include "Serializable.h"

void Serializable::Deserialize(Parser & parser)
{
}

void Serializable::Serialize(Parser & parser) const
{
}

Serializable::Serializable()
{
}

Serializable::~Serializable()
{
}

Serializable::Serializable(const Serializable & other)
{
}

Serializable & Serializable::operator=(const Serializable & other)
{
	return *this;
}
