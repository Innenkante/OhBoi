#include "stdafx.h"
#include "Resource.h"
std::map<int, Resource> Resource::resources;

Resource::Resource(void * pointerToResource)
{
	resourcePointer = pointerToResource;
}

int Resource::AddResource(Resource resource)
{
	int index = resources.size() + 1;
	resources.insert(std::pair<int, Resource>(index, resource));

	return index;
}

void Resource::RemoveResource(int index)
{
	resources[index].Clear();

	resources.erase(index);
}

int Resource::GetCurrentIndex()
{
	return resources.size();
}

void Resource::Clear()
{
	delete[] resourcePointer;
}
