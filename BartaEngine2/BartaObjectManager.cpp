#include "BartaObjectManager.h"

Barta::BartaObjectManager::~BartaObjectManager(){
	auto i = this->objectList.begin();
	while( i != this->objectList.end() ){
		auto objectPtr = ( *i );
		delete objectPtr;

		i++;
	}
}

void Barta::BartaObjectManager::addNewObject( BartaObjectInterface* const newObject ){
	this->objectList.push_back( newObject );
}

Barta::ObjectManagerInterface::ObjectList Barta::BartaObjectManager::getList() const{
	return this->objectList;
}

void Barta::BartaObjectManager::reduceDeleted(){
	auto newList = ObjectList();
	auto i = this->objectList.begin();
	while( i != this->objectList.end() ){
		if( ( *i )->isToBeDeleted() ){
			auto objectPtr = ( *i );
			delete objectPtr;
		}
		else{
			newList.push_back( *i );
		}
	
		i++;
	}

	this->objectList = newList;
}
