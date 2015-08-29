#include "PlatformPrecomp.h"
#include "XMLMenuEntity.h"

XMLMenuEntity::XMLMenuEntity()
	: m_type( EXMT_NONE ), m_typeStr( "" )
{
}

XMLMenuEntity::XMLMenuEntity( const XMLMenuEntity &entity )
{
	operator = ( entity );
}

XMLMenuEntity& XMLMenuEntity::operator = ( const XMLMenuEntity &entity )
{
	if( this == &entity )
	{
		return *this;
	}

	m_type = entity.m_type;
	m_typeStr = entity.m_typeStr;

	return *this;
}

XMLMenuEntity::~XMLMenuEntity()
{
}