#include "stdafx.h"
#include "Serializable.h"



Serializable::Serializable()
{
}

Serializable::Serializable(const Serializable & other)
{
}

Serializable::~Serializable()
{
}

void Serializable::Deserialize(Parser & parser)
{
}

void Serializable::Serialize(Parser & parser) const
{
}

Serializable & Serializable::operator=(const Serializable & other)
{
	// TODO: insert return statement here
}
