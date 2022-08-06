#include "Element.h"
#include "GameActor.h"

Element::Element(GameActor* owner_, int priority_ /* = 100*/)
	: owner(owner_), priority(priority_)
{
	owner->AddElement(this);
}