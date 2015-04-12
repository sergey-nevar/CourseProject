#include "regElement.h"

RegElement::RegElement(void)
{
}


RegElement::~RegElement(void)
{
}

RegElement& RegElement::operator=(RegElement& element){
	regPath = element.regPath;
	defaultValue = element.defaultValue;
	dataItems = element.dataItems;
	return *this;
}